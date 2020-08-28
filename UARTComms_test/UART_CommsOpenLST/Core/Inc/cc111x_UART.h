/*
 * cc111x_UART.h
 *
 *  Created on: Aug 27, 2020
 *      Author: joebe
 */

#ifndef __CC111X_UART_H_
#define __CC111X_UART_H_
#include <stdint.h>
#include "stm32f4xx_hal_conf.h"
#include "cc_definitions.h"
#include "cc_commands.h"
#include "config.h"
#include "scrambler.h"
//#include "cw.h"

#define CC_EXT_ADD 0x2F00
#define CC_DMA_ADD 0x3E00

uint8_t
cc_tx_rd_reg (uint16_t addr, uint8_t *data);
uint8_t
cc_tx_wr_reg (uint16_t addr, uint8_t data);
HAL_StatusTypeDef
cc_tx_spi_write_fifo(const uint8_t *data, uint8_t *spi_rx_data, size_t len);
int32_t
cc_tx_data_continuous (const uint8_t *data, size_t size, uint8_t *rec_data,
		       size_t timeout_ms);
//int32_t
//cc_tx_cw(const cw_pulse_t *in, size_t len);
uint8_t
cc_tx_cmd (uint8_t CMDStrobe);
//
//HAL_StatusTypeDef
//cc_rx_spi_read_fifo(uint8_t *out, size_t len);
//HAL_StatusTypeDef
//cc_rx_spi_write_fifo(uint8_t *data, uint8_t *spi_rx_data, size_t len);
//uint8_t
//cc_rx_rd_reg (uint16_t addr, uint8_t *data);
//uint8_t
//cc_rx_wr_reg (uint16_t addr, uint8_t data);
//int32_t
//cc_rx_data_packet (uint8_t *out, size_t len, size_t timeout_ms);
//uint8_t
//cc_rx_cmd (uint8_t CMDStrobe);
//
//uint8_t
//cc_rx_check_fifo_status();



#endif /* APPLICATION_USER_CORE_CC111X_UART_H_ */
