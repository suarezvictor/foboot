REBOOT
======

Register Listing for REBOOT
---------------------------

+------------------------------------+----------------------------------+
| Register                           | Address                          |
+====================================+==================================+
| :ref:`REBOOT_CTRL <REBOOT_CTRL>`   | :ref:`0xe0006000 <REBOOT_CTRL>`  |
+------------------------------------+----------------------------------+
| :ref:`REBOOT_ADDR3 <REBOOT_ADDR3>` | :ref:`0xe0006004 <REBOOT_ADDR3>` |
+------------------------------------+----------------------------------+
| :ref:`REBOOT_ADDR2 <REBOOT_ADDR2>` | :ref:`0xe0006008 <REBOOT_ADDR2>` |
+------------------------------------+----------------------------------+
| :ref:`REBOOT_ADDR1 <REBOOT_ADDR1>` | :ref:`0xe000600c <REBOOT_ADDR1>` |
+------------------------------------+----------------------------------+
| :ref:`REBOOT_ADDR0 <REBOOT_ADDR0>` | :ref:`0xe0006010 <REBOOT_ADDR0>` |
+------------------------------------+----------------------------------+

REBOOT_CTRL
^^^^^^^^^^^

`Address: 0xe0006000 + 0x0 = 0xe0006000`

    Provides support for rebooting the FPGA.  You can select which of the four
    images to reboot to, just be sure to OR the image number with ``0xac``.  For
    example, to reboot to the bootloader (image 0), write ``0xac``` to this
    register.

    .. wavedrom::
        :caption: REBOOT_CTRL

        {
            "reg": [
                {"name": "image",  "bits": 2},
                {"name": "key",  "bits": 6}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


+-------+-------+---------------------------------------------------------------------------------+
| Field | Name  | Description                                                                     |
+=======+=======+=================================================================================+
| [1:0] | IMAGE | Which image to reboot to.  ``SB_WARMBOOT`` supports four images that are        |
|       |       | configured at FPGA startup.  The bootloader is image 0, so set these bits to 0  |
|       |       | to reboot back into the bootloader.                                             |
+-------+-------+---------------------------------------------------------------------------------+
| [7:2] | KEY   | A reboot key used to prevent accidental reboots when writing to random areas of |
|       |       | memory.  To initiate a reboot, set this to ``0b101011``.                        |
+-------+-------+---------------------------------------------------------------------------------+

REBOOT_ADDR3
^^^^^^^^^^^^

`Address: 0xe0006000 + 0x4 = 0xe0006004`

    Bits 24-31 of `REBOOT_ADDR`. This sets the reset vector for the VexRiscv.  This
    address will be used whenever the CPU is reset, for example through a debug
    bridge.  You should update this address whenever you load a new program, to
    enable the debugger to run ``mon reset``

    .. wavedrom::
        :caption: REBOOT_ADDR3

        {
            "reg": [
                {"name": "addr[31:24]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


REBOOT_ADDR2
^^^^^^^^^^^^

`Address: 0xe0006000 + 0x8 = 0xe0006008`

    Bits 16-23 of `REBOOT_ADDR`.

    .. wavedrom::
        :caption: REBOOT_ADDR2

        {
            "reg": [
                {"name": "addr[23:16]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


REBOOT_ADDR1
^^^^^^^^^^^^

`Address: 0xe0006000 + 0xc = 0xe000600c`

    Bits 8-15 of `REBOOT_ADDR`.

    .. wavedrom::
        :caption: REBOOT_ADDR1

        {
            "reg": [
                {"name": "addr[15:8]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


REBOOT_ADDR0
^^^^^^^^^^^^

`Address: 0xe0006000 + 0x10 = 0xe0006010`

    Bits 0-7 of `REBOOT_ADDR`.

    .. wavedrom::
        :caption: REBOOT_ADDR0

        {
            "reg": [
                {"name": "addr[7:0]", "bits": 8}
            ], "config": {"hspace": 400, "bits": 8, "lanes": 1 }, "options": {"hspace": 400, "bits": 8, "lanes": 1}
        }


