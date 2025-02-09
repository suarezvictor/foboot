//--------------------------------------------------------------------------------
// Auto-generated by Migen (b1b2b29) & LiteX (4f82a36a) on 2022-03-24 16:11:28
//--------------------------------------------------------------------------------
#include <generated/soc.h>
#ifndef __GENERATED_CSR_H
#define __GENERATED_CSR_H
#include <stdint.h>
#include <system.h>
#ifndef CSR_ACCESSORS_DEFINED
#include <hw/common.h>
#endif /* ! CSR_ACCESSORS_DEFINED */
#ifndef CSR_BASE
#define CSR_BASE 0xe0000000L
#endif

/* ctrl */
#define CSR_CTRL_BASE (CSR_BASE + 0x0L)
#define CSR_CTRL_RESET_ADDR (CSR_BASE + 0x0L)
#define CSR_CTRL_RESET_SIZE 1
static inline uint8_t ctrl_reset_read(void) {
	return csr_read_simple(CSR_BASE + 0x0L);
}
static inline void ctrl_reset_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x0L);
}
#define CSR_CTRL_SCRATCH_ADDR (CSR_BASE + 0x4L)
#define CSR_CTRL_SCRATCH_SIZE 4
static inline uint32_t ctrl_scratch_read(void) {
	uint32_t r = csr_read_simple(CSR_BASE + 0x4L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x8L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0xcL);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x10L);
	return r;
}
static inline void ctrl_scratch_write(uint32_t v) {
	csr_write_simple(v >> 24, CSR_BASE + 0x4L);
	csr_write_simple(v >> 16, CSR_BASE + 0x8L);
	csr_write_simple(v >> 8, CSR_BASE + 0xcL);
	csr_write_simple(v, CSR_BASE + 0x10L);
}
#define CSR_CTRL_BUS_ERRORS_ADDR (CSR_BASE + 0x14L)
#define CSR_CTRL_BUS_ERRORS_SIZE 4
static inline uint32_t ctrl_bus_errors_read(void) {
	uint32_t r = csr_read_simple(CSR_BASE + 0x14L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x18L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x1cL);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x20L);
	return r;
}

/* uart_phy */
#define CSR_UART_PHY_BASE (CSR_BASE + 0x1000L)
#define CSR_UART_PHY_TUNING_WORD_ADDR (CSR_BASE + 0x1000L)
#define CSR_UART_PHY_TUNING_WORD_SIZE 4
static inline uint32_t uart_phy_tuning_word_read(void) {
	uint32_t r = csr_read_simple(CSR_BASE + 0x1000L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x1004L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x1008L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x100cL);
	return r;
}
static inline void uart_phy_tuning_word_write(uint32_t v) {
	csr_write_simple(v >> 24, CSR_BASE + 0x1000L);
	csr_write_simple(v >> 16, CSR_BASE + 0x1004L);
	csr_write_simple(v >> 8, CSR_BASE + 0x1008L);
	csr_write_simple(v, CSR_BASE + 0x100cL);
}

/* uart */
#define CSR_UART_BASE (CSR_BASE + 0x1800L)
#define CSR_UART_RXTX_ADDR (CSR_BASE + 0x1800L)
#define CSR_UART_RXTX_SIZE 1
static inline uint8_t uart_rxtx_read(void) {
	return csr_read_simple(CSR_BASE + 0x1800L);
}
static inline void uart_rxtx_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x1800L);
}
#define CSR_UART_TXFULL_ADDR (CSR_BASE + 0x1804L)
#define CSR_UART_TXFULL_SIZE 1
static inline uint8_t uart_txfull_read(void) {
	return csr_read_simple(CSR_BASE + 0x1804L);
}
#define CSR_UART_RXEMPTY_ADDR (CSR_BASE + 0x1808L)
#define CSR_UART_RXEMPTY_SIZE 1
static inline uint8_t uart_rxempty_read(void) {
	return csr_read_simple(CSR_BASE + 0x1808L);
}
#define CSR_UART_EV_STATUS_ADDR (CSR_BASE + 0x180cL)
#define CSR_UART_EV_STATUS_SIZE 1
static inline uint8_t uart_ev_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x180cL);
}
static inline void uart_ev_status_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x180cL);
}
#define CSR_UART_EV_PENDING_ADDR (CSR_BASE + 0x1810L)
#define CSR_UART_EV_PENDING_SIZE 1
static inline uint8_t uart_ev_pending_read(void) {
	return csr_read_simple(CSR_BASE + 0x1810L);
}
static inline void uart_ev_pending_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x1810L);
}
#define CSR_UART_EV_ENABLE_ADDR (CSR_BASE + 0x1814L)
#define CSR_UART_EV_ENABLE_SIZE 1
static inline uint8_t uart_ev_enable_read(void) {
	return csr_read_simple(CSR_BASE + 0x1814L);
}
static inline void uart_ev_enable_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x1814L);
}

/* timer0 */
#define CSR_TIMER0_BASE (CSR_BASE + 0x2800L)
#define CSR_TIMER0_LOAD_ADDR (CSR_BASE + 0x2800L)
#define CSR_TIMER0_LOAD_SIZE 4
static inline uint32_t timer0_load_read(void) {
	uint32_t r = csr_read_simple(CSR_BASE + 0x2800L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x2804L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x2808L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x280cL);
	return r;
}
static inline void timer0_load_write(uint32_t v) {
	csr_write_simple(v >> 24, CSR_BASE + 0x2800L);
	csr_write_simple(v >> 16, CSR_BASE + 0x2804L);
	csr_write_simple(v >> 8, CSR_BASE + 0x2808L);
	csr_write_simple(v, CSR_BASE + 0x280cL);
}
#define CSR_TIMER0_RELOAD_ADDR (CSR_BASE + 0x2810L)
#define CSR_TIMER0_RELOAD_SIZE 4
static inline uint32_t timer0_reload_read(void) {
	uint32_t r = csr_read_simple(CSR_BASE + 0x2810L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x2814L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x2818L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x281cL);
	return r;
}
static inline void timer0_reload_write(uint32_t v) {
	csr_write_simple(v >> 24, CSR_BASE + 0x2810L);
	csr_write_simple(v >> 16, CSR_BASE + 0x2814L);
	csr_write_simple(v >> 8, CSR_BASE + 0x2818L);
	csr_write_simple(v, CSR_BASE + 0x281cL);
}
#define CSR_TIMER0_EN_ADDR (CSR_BASE + 0x2820L)
#define CSR_TIMER0_EN_SIZE 1
static inline uint8_t timer0_en_read(void) {
	return csr_read_simple(CSR_BASE + 0x2820L);
}
static inline void timer0_en_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x2820L);
}
#define CSR_TIMER0_UPDATE_VALUE_ADDR (CSR_BASE + 0x2824L)
#define CSR_TIMER0_UPDATE_VALUE_SIZE 1
static inline uint8_t timer0_update_value_read(void) {
	return csr_read_simple(CSR_BASE + 0x2824L);
}
static inline void timer0_update_value_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x2824L);
}
#define CSR_TIMER0_VALUE_ADDR (CSR_BASE + 0x2828L)
#define CSR_TIMER0_VALUE_SIZE 4
static inline uint32_t timer0_value_read(void) {
	uint32_t r = csr_read_simple(CSR_BASE + 0x2828L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x282cL);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x2830L);
	r <<= 8;
	r |= csr_read_simple(CSR_BASE + 0x2834L);
	return r;
}
#define CSR_TIMER0_EV_STATUS_ADDR (CSR_BASE + 0x2838L)
#define CSR_TIMER0_EV_STATUS_SIZE 1
static inline uint8_t timer0_ev_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x2838L);
}
static inline void timer0_ev_status_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x2838L);
}
#define CSR_TIMER0_EV_PENDING_ADDR (CSR_BASE + 0x283cL)
#define CSR_TIMER0_EV_PENDING_SIZE 1
static inline uint8_t timer0_ev_pending_read(void) {
	return csr_read_simple(CSR_BASE + 0x283cL);
}
static inline void timer0_ev_pending_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x283cL);
}
#define CSR_TIMER0_EV_ENABLE_ADDR (CSR_BASE + 0x2840L)
#define CSR_TIMER0_EV_ENABLE_SIZE 1
static inline uint8_t timer0_ev_enable_read(void) {
	return csr_read_simple(CSR_BASE + 0x2840L);
}
static inline void timer0_ev_enable_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x2840L);
}

/* usb */
#define CSR_USB_BASE (CSR_BASE + 0x4800L)
#define CSR_USB_PULLUP_OUT_ADDR (CSR_BASE + 0x4800L)
#define CSR_USB_PULLUP_OUT_SIZE 1
static inline uint8_t usb_pullup_out_read(void) {
	return csr_read_simple(CSR_BASE + 0x4800L);
}
static inline void usb_pullup_out_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4800L);
}
#define CSR_USB_ADDRESS_ADDR (CSR_BASE + 0x4804L)
#define CSR_USB_ADDRESS_SIZE 1
static inline uint8_t usb_address_read(void) {
	return csr_read_simple(CSR_BASE + 0x4804L);
}
static inline void usb_address_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4804L);
}
#define CSR_USB_ADDRESS_ADDR_OFFSET 0
#define CSR_USB_ADDRESS_ADDR_SIZE 7
#define CSR_USB_NEXT_EV_ADDR (CSR_BASE + 0x4808L)
#define CSR_USB_NEXT_EV_SIZE 1
static inline uint8_t usb_next_ev_read(void) {
	return csr_read_simple(CSR_BASE + 0x4808L);
}
#define CSR_USB_NEXT_EV_IN_OFFSET 0
#define CSR_USB_NEXT_EV_IN_SIZE 1
#define CSR_USB_NEXT_EV_OUT_OFFSET 1
#define CSR_USB_NEXT_EV_OUT_SIZE 1
#define CSR_USB_NEXT_EV_SETUP_OFFSET 2
#define CSR_USB_NEXT_EV_SETUP_SIZE 1
#define CSR_USB_NEXT_EV_RESET_OFFSET 3
#define CSR_USB_NEXT_EV_RESET_SIZE 1
#define CSR_USB_SETUP_DATA_ADDR (CSR_BASE + 0x480cL)
#define CSR_USB_SETUP_DATA_SIZE 1
static inline uint8_t usb_setup_data_read(void) {
	return csr_read_simple(CSR_BASE + 0x480cL);
}
#define CSR_USB_SETUP_DATA_DATA_OFFSET 0
#define CSR_USB_SETUP_DATA_DATA_SIZE 8
#define CSR_USB_SETUP_CTRL_ADDR (CSR_BASE + 0x4810L)
#define CSR_USB_SETUP_CTRL_SIZE 1
static inline uint8_t usb_setup_ctrl_read(void) {
	return csr_read_simple(CSR_BASE + 0x4810L);
}
static inline void usb_setup_ctrl_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4810L);
}
#define CSR_USB_SETUP_CTRL_RESET_OFFSET 5
#define CSR_USB_SETUP_CTRL_RESET_SIZE 1
#define CSR_USB_SETUP_STATUS_ADDR (CSR_BASE + 0x4814L)
#define CSR_USB_SETUP_STATUS_SIZE 1
static inline uint8_t usb_setup_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x4814L);
}
#define CSR_USB_SETUP_STATUS_EPNO_OFFSET 0
#define CSR_USB_SETUP_STATUS_EPNO_SIZE 4
#define CSR_USB_SETUP_STATUS_HAVE_OFFSET 4
#define CSR_USB_SETUP_STATUS_HAVE_SIZE 1
#define CSR_USB_SETUP_STATUS_PEND_OFFSET 5
#define CSR_USB_SETUP_STATUS_PEND_SIZE 1
#define CSR_USB_SETUP_STATUS_IS_IN_OFFSET 6
#define CSR_USB_SETUP_STATUS_IS_IN_SIZE 1
#define CSR_USB_SETUP_STATUS_DATA_OFFSET 7
#define CSR_USB_SETUP_STATUS_DATA_SIZE 1
#define CSR_USB_SETUP_EV_STATUS_ADDR (CSR_BASE + 0x4818L)
#define CSR_USB_SETUP_EV_STATUS_SIZE 1
static inline uint8_t usb_setup_ev_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x4818L);
}
static inline void usb_setup_ev_status_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4818L);
}
#define CSR_USB_SETUP_EV_PENDING_ADDR (CSR_BASE + 0x481cL)
#define CSR_USB_SETUP_EV_PENDING_SIZE 1
static inline uint8_t usb_setup_ev_pending_read(void) {
	return csr_read_simple(CSR_BASE + 0x481cL);
}
static inline void usb_setup_ev_pending_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x481cL);
}
#define CSR_USB_SETUP_EV_ENABLE_ADDR (CSR_BASE + 0x4820L)
#define CSR_USB_SETUP_EV_ENABLE_SIZE 1
static inline uint8_t usb_setup_ev_enable_read(void) {
	return csr_read_simple(CSR_BASE + 0x4820L);
}
static inline void usb_setup_ev_enable_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4820L);
}
#define CSR_USB_IN_DATA_ADDR (CSR_BASE + 0x4824L)
#define CSR_USB_IN_DATA_SIZE 1
static inline uint8_t usb_in_data_read(void) {
	return csr_read_simple(CSR_BASE + 0x4824L);
}
static inline void usb_in_data_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4824L);
}
#define CSR_USB_IN_DATA_DATA_OFFSET 0
#define CSR_USB_IN_DATA_DATA_SIZE 8
#define CSR_USB_IN_CTRL_ADDR (CSR_BASE + 0x4828L)
#define CSR_USB_IN_CTRL_SIZE 1
static inline uint8_t usb_in_ctrl_read(void) {
	return csr_read_simple(CSR_BASE + 0x4828L);
}
static inline void usb_in_ctrl_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4828L);
}
#define CSR_USB_IN_CTRL_EPNO_OFFSET 0
#define CSR_USB_IN_CTRL_EPNO_SIZE 4
#define CSR_USB_IN_CTRL_RESET_OFFSET 5
#define CSR_USB_IN_CTRL_RESET_SIZE 1
#define CSR_USB_IN_CTRL_STALL_OFFSET 6
#define CSR_USB_IN_CTRL_STALL_SIZE 1
#define CSR_USB_IN_STATUS_ADDR (CSR_BASE + 0x482cL)
#define CSR_USB_IN_STATUS_SIZE 1
static inline uint8_t usb_in_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x482cL);
}
#define CSR_USB_IN_STATUS_IDLE_OFFSET 0
#define CSR_USB_IN_STATUS_IDLE_SIZE 1
#define CSR_USB_IN_STATUS_HAVE_OFFSET 4
#define CSR_USB_IN_STATUS_HAVE_SIZE 1
#define CSR_USB_IN_STATUS_PEND_OFFSET 5
#define CSR_USB_IN_STATUS_PEND_SIZE 1
#define CSR_USB_IN_EV_STATUS_ADDR (CSR_BASE + 0x4830L)
#define CSR_USB_IN_EV_STATUS_SIZE 1
static inline uint8_t usb_in_ev_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x4830L);
}
static inline void usb_in_ev_status_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4830L);
}
#define CSR_USB_IN_EV_PENDING_ADDR (CSR_BASE + 0x4834L)
#define CSR_USB_IN_EV_PENDING_SIZE 1
static inline uint8_t usb_in_ev_pending_read(void) {
	return csr_read_simple(CSR_BASE + 0x4834L);
}
static inline void usb_in_ev_pending_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4834L);
}
#define CSR_USB_IN_EV_ENABLE_ADDR (CSR_BASE + 0x4838L)
#define CSR_USB_IN_EV_ENABLE_SIZE 1
static inline uint8_t usb_in_ev_enable_read(void) {
	return csr_read_simple(CSR_BASE + 0x4838L);
}
static inline void usb_in_ev_enable_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4838L);
}
#define CSR_USB_OUT_DATA_ADDR (CSR_BASE + 0x483cL)
#define CSR_USB_OUT_DATA_SIZE 1
static inline uint8_t usb_out_data_read(void) {
	return csr_read_simple(CSR_BASE + 0x483cL);
}
#define CSR_USB_OUT_DATA_DATA_OFFSET 0
#define CSR_USB_OUT_DATA_DATA_SIZE 8
#define CSR_USB_OUT_CTRL_ADDR (CSR_BASE + 0x4840L)
#define CSR_USB_OUT_CTRL_SIZE 1
static inline uint8_t usb_out_ctrl_read(void) {
	return csr_read_simple(CSR_BASE + 0x4840L);
}
static inline void usb_out_ctrl_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4840L);
}
#define CSR_USB_OUT_CTRL_EPNO_OFFSET 0
#define CSR_USB_OUT_CTRL_EPNO_SIZE 4
#define CSR_USB_OUT_CTRL_ENABLE_OFFSET 4
#define CSR_USB_OUT_CTRL_ENABLE_SIZE 1
#define CSR_USB_OUT_CTRL_RESET_OFFSET 5
#define CSR_USB_OUT_CTRL_RESET_SIZE 1
#define CSR_USB_OUT_CTRL_STALL_OFFSET 6
#define CSR_USB_OUT_CTRL_STALL_SIZE 1
#define CSR_USB_OUT_STATUS_ADDR (CSR_BASE + 0x4844L)
#define CSR_USB_OUT_STATUS_SIZE 1
static inline uint8_t usb_out_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x4844L);
}
#define CSR_USB_OUT_STATUS_EPNO_OFFSET 0
#define CSR_USB_OUT_STATUS_EPNO_SIZE 4
#define CSR_USB_OUT_STATUS_HAVE_OFFSET 4
#define CSR_USB_OUT_STATUS_HAVE_SIZE 1
#define CSR_USB_OUT_STATUS_PEND_OFFSET 5
#define CSR_USB_OUT_STATUS_PEND_SIZE 1
#define CSR_USB_OUT_EV_STATUS_ADDR (CSR_BASE + 0x4848L)
#define CSR_USB_OUT_EV_STATUS_SIZE 1
static inline uint8_t usb_out_ev_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x4848L);
}
static inline void usb_out_ev_status_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4848L);
}
#define CSR_USB_OUT_EV_PENDING_ADDR (CSR_BASE + 0x484cL)
#define CSR_USB_OUT_EV_PENDING_SIZE 1
static inline uint8_t usb_out_ev_pending_read(void) {
	return csr_read_simple(CSR_BASE + 0x484cL);
}
static inline void usb_out_ev_pending_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x484cL);
}
#define CSR_USB_OUT_EV_ENABLE_ADDR (CSR_BASE + 0x4850L)
#define CSR_USB_OUT_EV_ENABLE_SIZE 1
static inline uint8_t usb_out_ev_enable_read(void) {
	return csr_read_simple(CSR_BASE + 0x4850L);
}
static inline void usb_out_ev_enable_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x4850L);
}

/* messible */
#define CSR_MESSIBLE_BASE (CSR_BASE + 0x8000L)
#define CSR_MESSIBLE_IN_ADDR (CSR_BASE + 0x8000L)
#define CSR_MESSIBLE_IN_SIZE 1
static inline uint8_t messible_in_read(void) {
	return csr_read_simple(CSR_BASE + 0x8000L);
}
static inline void messible_in_write(uint8_t v) {
	csr_write_simple(v, CSR_BASE + 0x8000L);
}
#define CSR_MESSIBLE_OUT_ADDR (CSR_BASE + 0x8004L)
#define CSR_MESSIBLE_OUT_SIZE 1
static inline uint8_t messible_out_read(void) {
	return csr_read_simple(CSR_BASE + 0x8004L);
}
#define CSR_MESSIBLE_STATUS_ADDR (CSR_BASE + 0x8008L)
#define CSR_MESSIBLE_STATUS_SIZE 1
static inline uint8_t messible_status_read(void) {
	return csr_read_simple(CSR_BASE + 0x8008L);
}
#define CSR_MESSIBLE_STATUS_FULL_OFFSET 0
#define CSR_MESSIBLE_STATUS_FULL_SIZE 1
#define CSR_MESSIBLE_STATUS_HAVE_OFFSET 1
#define CSR_MESSIBLE_STATUS_HAVE_SIZE 1

#endif
