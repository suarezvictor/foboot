#!/usr/bin/env python3
"""
/media/vsuarez/elocaldata/SCRATCH/foboot/hw$ time ./foboot-bitstream.py --no-cpu --revision hacker

[ 2612.507116] usb 5-2.1: new full-speed USB device number 8 using xhci_hcd
[ 2612.712806] usb 5-2.1: New USB device found, idVendor=1209, idProduct=5bf0, bcdDevice= 1.01
[ 2612.712817] usb 5-2.1: New USB device strings: Mfr=1, Product=2, SerialNumber=0
[ 2612.712821] usb 5-2.1: Product: Fomu Bridge
[ 2612.712823] usb 5-2.1: Manufacturer: Foosn
"""

# This variable defines all the external programs that this module
# relies on.  lxbuildenv reads this variable in order to ensure
# the build will finish without exiting due to missing third-party
# programs.
LX_DEPENDENCIES = ["riscv", "vivado"]

# Import lxbuildenv to integrate the deps/ directory
import lxbuildenv

# Disable pylint's E1101, which breaks completely on migen
#pylint:disable=E1101

#from migen import *
from migen import Module, Signal, Instance, ClockDomain, If
from migen.fhdl.specials import TSTriple
from migen.fhdl.decorators import ClockDomainsRenamer
from migen.genlib.cdc import AsyncResetSynchronizer

from litex.build.lattice.platform import LatticePlatform
from litex.build.generic_platform import Pins, Subsignal
from litex.soc.integration.doc import AutoDoc, ModuleDoc
from litex.soc.integration.soc_core import SoCCore
from litex.soc.cores.cpu import CPUNone
from litex.soc.integration.builder import Builder
from litex.soc.interconnect import wishbone

from litex.soc.cores import up5kspram, spi_flash

from valentyusb.usbcore import io as usbio
from valentyusb.usbcore.cpu import epmem, unififo, epfifo, dummyusb, eptri
from valentyusb.usbcore.endpoint import EndpointType

import litex.soc.doc as lxsocdoc
import spibone

import argparse
import os

from rtl.version import Version
from rtl.romgen import RandomFirmwareROM, FirmwareROM
from rtl.fomutouch import TouchPads
from rtl.sbled import SBLED
from rtl.messible import Messible

class _CRG(Module, AutoDoc):
    def __init__(self, platform, sys_clk_freq=12e6, with_rst=True):
        from litex.soc.cores.clock import S7PLL
        self.rst = Signal()
        self.clock_domains.cd_sys       = ClockDomain()
        pll = S7PLL(speedgrade=-1)
        self.submodules.pll = pll
        rst    = ~platform.request("cpu_reset") if with_rst else 0
        self.comb += pll.reset.eq(rst)
        pll.register_clkin(platform.request("clk100"), 100e6)
        pll.create_clkout(self.cd_sys,       sys_clk_freq)
        self.clock_domains.cd_usb_12       = ClockDomain(reset_less=False) #TODO: check
        pll.create_clkout(self.cd_usb_12, 12e6, margin=1e-3)
        self.clock_domains.cd_usb_48       = ClockDomain(reset_less=False) #TODO: check
        pll.create_clkout(self.cd_usb_48, 48e6, margin=1e-3)
            
        platform.add_false_path_constraints(self.cd_sys.clk, pll.clkin) # Ignore sys_clk to pll.clkin path created by SoC's rst.


class BaseSoC(SoCCore, AutoDoc):
    """Fomu Bootloader and Base SoC

    Fomu is an FPGA that fits in your USB port.  This reference manual
    documents the basic SoC that runs the bootloader, and that can be
    reused to run your own RISC-V programs.

    This reference manual only describes a particular version of the SoC.
    The register sets described here are guaranteed to be available
    with a given ``major version``, but are not guaranteed to be available on
    any other version.  Naturally, you are free to create your own SoC
    that does not provide these hardware blocks. To see what the version of the
    bitstream you're running, check the ``VERSION`` registers.
    """

    SoCCore.csr_map = {
        "ctrl":           0,  # provided by default (optional)
        "crg":            1,  # user
        "uart_phy":       2,  # provided by default (optional)
        "uart":           3,  # provided by default (optional)
        "identifier_mem": 4,  # provided by default (optional)
        "timer0":         5,  # provided by default (optional)
        "cpu_or_bridge":  8,
        "usb":            9,
        "picorvspi":      10,
        "touch":          11,
        "reboot":         12,
        "rgb":            13,
        "version":        14,
        "lxspi":          15,
        "messible":       16,
    }

    SoCCore.mem_map = {
        "rom":              0x00000000,  # (default shadow @0x80000000)
        "sram":             0x10000000,  # (default shadow @0xa0000000)
        "spiflash":         0x20000000,  # (default shadow @0xa0000000)
        "main_ram":         0x40000000,  # (default shadow @0xc0000000)
        "csr":              0xe0000000,  # (default shadow @0xe0000000)
        "vexriscv_debug":   0xf00f0000,
    }

    interrupt_map = {
        "timer0": 2,
        "usb": 3,
    }
    interrupt_map.update(SoCCore.interrupt_map)

    def __init__(self, platform, boot_source="rand",
                 debug=None, bios_file=None,
                 use_dsp=False, placer="heap", output_dir="build",
                 pnr_seed=0,
                 warmboot_offsets=None,
                 **kwargs):
        # Disable integrated RAM as we'll add it later
        self.integrated_sram_size = 0

        self.output_dir = output_dir

        clk_freq = int(12e6)
        self.submodules.crg = _CRG(platform)

        SoCCore.__init__(self, platform, clk_freq, integrated_sram_size=0x2000, with_uart=True, **kwargs)

        usb_debug = False
        if debug is not None:
            if debug == "uart":
                from litex.soc.cores.uart import UARTWishboneBridge
                self.submodules.uart_bridge = UARTWishboneBridge(platform.request("serial"), clk_freq, baudrate=115200)
                self.add_wb_master(self.uart_bridge.wishbone)
            elif debug == "usb":
                usb_debug = True
            elif debug == "spi":
                import spibone
                # Add SPI Wishbone bridge
                debug_device = [
                    ("spidebug", 0,
                        Subsignal("mosi", Pins("dbg:0")),
                        Subsignal("miso", Pins("dbg:1")),
                        Subsignal("clk",  Pins("dbg:2")),
                        Subsignal("cs_n", Pins("dbg:3")),
                    )
                ]
                platform.add_extension(debug_device)
                spi_pads = platform.request("spidebug")
                self.submodules.spibone = ClockDomainsRenamer("usb_12")(spibone.SpiWishboneBridge(spi_pads, wires=4))
                self.add_wb_master(self.spibone.wishbone)
            if hasattr(self, "cpu") and not isinstance(self.cpu, CPUNone):
                self.cpu.use_external_variant("rtl/VexRiscv_Fomu_Debug.v")
                os.path.join(output_dir, "gateware")
                self.register_mem("vexriscv_debug", 0xf00f0000, self.cpu.debug_bus, 0x100)
        else:
            if hasattr(self, "cpu") and not isinstance(self.cpu, CPUNone):
                self.cpu.use_external_variant("rtl/VexRiscv_Fomu.v")

        # Add a Messible for device->host communications
        self.submodules.messible = Messible()

        if boot_source == "rand":
            kwargs['cpu_reset_address'] = 0
            bios_size = 0x2000
            self.submodules.random_rom = RandomFirmwareROM(bios_size)
            self.add_constant("ROM_DISABLE", 1)
            self.register_rom(self.random_rom.bus, bios_size)
        elif boot_source == "bios":
            kwargs['cpu_reset_address'] = 0
            if hasattr(self, "cpu") and not isinstance(self.cpu, CPUNone):
                if bios_file is None:
                    self.integrated_rom_size = bios_size = 0x2000
                    self.submodules.rom = wishbone.SRAM(bios_size, read_only=True, init=[])
                    self.register_rom(self.rom.bus, bios_size)
                else:
                    bios_size = 0x2000
                    self.submodules.firmware_rom = FirmwareROM(bios_size, bios_file)
                    self.add_constant("ROM_DISABLE", 1)
                    self.register_rom(self.firmware_rom.bus, bios_size)

        elif boot_source == "spi":
            kwargs['cpu_reset_address'] = 0
            self.integrated_rom_size = bios_size = 0x2000
            gateware_size = 0x1a000
            self.flash_boot_address = self.mem_map["spiflash"] + gateware_size
            self.submodules.rom = wishbone.SRAM(bios_size, read_only=True, init=[])
            self.register_rom(self.rom.bus, bios_size)
        else:
            raise ValueError("unrecognized boot_source: {}".format(boot_source))


        # Add USB pads, as well as the appropriate USB controller.  If no CPU is
        # present, use the DummyUsb controller.
        usb_pads = platform.request("usb")
        usb_iobuf = usbio.IoBuf(usb_pads.d_p, usb_pads.d_n, usb_pads.pullup)
        if hasattr(self, "cpu") and not isinstance(self.cpu, CPUNone):
            self.submodules.usb = eptri.TriEndpointInterface(usb_iobuf, debug=usb_debug)
        else:
            self.submodules.usb = dummyusb.DummyUsb(usb_iobuf, debug=usb_debug)

        if usb_debug:
            self.add_wb_master(self.usb.debug_bridge.wishbone)
        # For the EVT board, ensure the pulldown pin is tristated as an input
        if hasattr(usb_pads, "pulldown"):
            pulldown = TSTriple()
            self.specials += pulldown.get_tristate(usb_pads.pulldown)
            self.comb += pulldown.oe.eq(0)

        # Allow the user to connect the CPU
        # RESET line to a register that can be modified, to allow for
        # us to debug programs even during reset.

        #if hasattr(self, "cpu") and not isinstance(self.cpu, CPUNone):
        #    self.cpu.cpu_params.update(
        #        i_externalResetVector=self.reboot.addr.storage,
        #	    )


    def copy_memory_file(self, src):
        import os
        from shutil import copyfile
        if not os.path.exists(self.output_dir):
            os.mkdir(self.output_dir)
        if not os.path.exists(os.path.join(self.output_dir, "gateware")):
            os.mkdir(os.path.join(self.output_dir, "gateware"))
        copyfile(os.path.join("rtl", src), os.path.join(self.output_dir, "gateware", src))

def make_multiboot_header(filename, boot_offsets=[160]):
    """
    ICE40 allows you to program the SB_WARMBOOT state machine by adding the following
    values to the bitstream, before any given image:

    [7e aa 99 7e]       Sync Header
    [92 00 k0]          Boot mode (k = 1 for cold boot, 0 for warmboot)
    [44 03 o1 o2 o3]    Boot address
    [82 00 00]          Bank offset
    [01 08]             Reboot
    [...]               Padding (up to 32 bytes)

    Note that in ICE40, the second nybble indicates the number of remaining bytes
    (with the exception of the sync header).

    The above construct is repeated five times:

    INITIAL_BOOT        The image loaded at first boot
    BOOT_S00            The first image for SB_WARMBOOT
    BOOT_S01            The second image for SB_WARMBOOT
    BOOT_S10            The third image for SB_WARMBOOT
    BOOT_S11            The fourth image for SB_WARMBOOT
    """
    while len(boot_offsets) < 5:
        boot_offsets.append(boot_offsets[0])

    with open(filename, 'wb') as output:
        for offset in boot_offsets:
            # Sync Header
            output.write(bytes([0x7e, 0xaa, 0x99, 0x7e]))

            # Boot mode
            output.write(bytes([0x92, 0x00, 0x00]))

            # Boot address
            output.write(bytes([0x44, 0x03,
                    (offset >> 16) & 0xff,
                    (offset >> 8)  & 0xff,
                    (offset >> 0)  & 0xff]))

            # Bank offset
            output.write(bytes([0x82, 0x00, 0x00]))

            # Reboot command
            output.write(bytes([0x01, 0x08]))

            for x in range(17, 32):
                output.write(bytes([0]))

def main():
    parser = argparse.ArgumentParser(
        description="Build Fomu Main Gateware")
    parser.add_argument(
        "--boot-source", choices=["spi", "rand", "bios"], default="bios",
        help="where to have the CPU obtain its executable code from"
    )
    parser.add_argument(
        "--document-only", default=False, action="store_true",
        help="Don't build gateware or software, only build documentation"
    )
    parser.add_argument(
        "--revision", choices=["evt", "dvt", "pvt", "hacker"], required=True,
        help="build foboot for a particular hardware revision"
    )
    parser.add_argument(
        "--bios", help="use specified file as a BIOS, rather than building one"
    )
    parser.add_argument(
        "--with-debug", help="enable debug support", choices=["usb", "uart", "spi", None]
    )
    parser.add_argument(
        "--with-dsp", help="use dsp inference in yosys (not all yosys builds have -dsp)", action="store_true"
    )
    parser.add_argument(
        "--no-cpu", help="disable cpu generation for debugging purposes", action="store_true"
    )
    parser.add_argument(
        "--placer", choices=["sa", "heap"], default="heap", help="which placer to use in nextpnr"
    )
    parser.add_argument(
        "--seed", default=0, help="seed to use in nextpnr"
    )
    parser.add_argument(
        "--export-random-rom-file", help="Generate a random ROM file and save it to a file"
    )
    args = parser.parse_args()

    output_dir = 'build'

    if args.export_random_rom_file is not None:
        size = 0x2000
        def xorshift32(x):
            x = x ^ (x << 13) & 0xffffffff
            x = x ^ (x >> 17) & 0xffffffff
            x = x ^ (x << 5)  & 0xffffffff
            return x & 0xffffffff

        def get_rand(x):
            out = 0
            for i in range(32):
                x = xorshift32(x)
                if (x & 1) == 1:
                    out = out | (1 << i)
            return out & 0xffffffff
        seed = 1
        with open(args.export_random_rom_file, "w", newline="\n") as output:
            for d in range(int(size / 4)):
                seed = get_rand(seed)
                print("{:08x}".format(seed), file=output)
        return 0

    compile_software = False
    if (args.boot_source == "bios" or args.boot_source == "spi") and args.bios is None:
        compile_software = True

    cpu_type = "vexriscv"
    cpu_variant = "minimal"
    if args.with_debug:
        cpu_variant = cpu_variant + "+debug"

    if args.no_cpu:
        cpu_type = None
        cpu_variant = None

    compile_gateware = True
    if args.document_only:
        compile_gateware = False
        compile_software = False

    warmboot_offsets = [
        160,
        160,
        157696,
        262144,
        262144 + 32768,
    ]

    os.environ["LITEX"] = "1" # Give our Makefile something to look for
    from litex_boards.platforms import arty as board
    from litex.build.generic_platform import IOStandard, Subsignal
    board._io += [
        ("usb", 0,
            Subsignal("d_p", Pins("pmoda:0")),
            Subsignal("d_n", Pins("pmoda:1")),
            Subsignal("pullup", Pins("pmoda:2")),
            IOStandard("LVCMOS33")
        ),
    ]

    platform = board.Platform() #Platform(revision=args.revision)
    soc = BaseSoC(platform, cpu_type=cpu_type, cpu_variant=cpu_variant,
                            debug=args.with_debug, boot_source=args.boot_source,
                            bios_file=args.bios,
                            use_dsp=args.with_dsp, placer=args.placer,
                            pnr_seed=int(args.seed),
                            output_dir=output_dir,
                            warmboot_offsets=warmboot_offsets[1:])
    builder = Builder(soc, output_dir=output_dir, csr_csv="build/csr.csv", csr_svd="build/soc.svd",
                      compile_software=compile_software, compile_gateware=compile_gateware)
    if compile_software:
        builder.software_packages = [
            ("bios", os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "sw")))
        ]
    vns = builder.build(build_name="top")
    soc.do_exit(vns)
    lxsocdoc.generate_docs(soc, "build/documentation/", project_name="Fomu Bootloader", author="Sean Cross")

    if not args.document_only:
        make_multiboot_header(os.path.join(output_dir, "gateware", "multiboot-header.bin"),
                            warmboot_offsets)

        with open(os.path.join(output_dir, 'gateware', 'multiboot-header.bin'), 'rb') as multiboot_header_file:
            multiboot_header = multiboot_header_file.read()
            with open(os.path.join(output_dir, 'gateware', 'top.bin'), 'rb') as top_file:
                top = top_file.read()
                with open(os.path.join(output_dir, 'gateware', 'top-multiboot.bin'), 'wb') as top_multiboot_file:
                    top_multiboot_file.write(multiboot_header)
                    top_multiboot_file.write(top)

        print(
    """Foboot build complete.  Output files:
        {}/gateware/top.bin             Bitstream file.  Load this onto the FPGA for testing.
        {}/gateware/top-multiboot.bin   Multiboot-enabled bitstream file.  Flash this onto FPGA ROM.
        {}/gateware/top.v               Source Verilog file.  Useful for debugging issues.
        {}/software/include/generated/  Directory with header files for API access.
        {}/software/bios/bios.elf       ELF file for debugging bios.
    """.format(output_dir, output_dir, output_dir, output_dir, output_dir))

if __name__ == "__main__":
    main()
