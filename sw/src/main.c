#include <stdio.h>
#include <irq.h>
//#include <printf.h>
#include <uart.h>
#include <usb.h>
#include <time.h>
#include <rgb.h>
#include <spi.h>
#include <generated/csr.h>

struct ff_spi *spi;

__attribute__((section(".sram")))
void isr(void)
{
    unsigned int irqs;

    irqs = irq_pending() & irq_getmask();

    if (irqs & (1 << USB_INTERRUPT))
        usb_isr();
}

__attribute__((section(".sram")))
static void init(void)
{
    irq_setmask(0);
    irq_setie(1);
#if 0//def CSR_UART_BASE
    uart_init();
#else
    usb_init();
#endif
/*
    time_init();
    rgb_init();*/
}

__attribute__((section(".sram")))
void reboot(void) { for(;;); }

__attribute__((section(".sram")))
int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    init();
#if 0//def CSR_UART_BASE    
    while(1)
    {
      uart_write('A');
      uart_write('B');
    }
#else
    usb_connect();
    while (1)
    {
        usb_poll();
    }
#endif
    return 0;
}

#warning SW main
