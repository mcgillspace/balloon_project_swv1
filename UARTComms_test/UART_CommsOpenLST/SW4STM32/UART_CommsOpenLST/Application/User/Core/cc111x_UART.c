/*
 * cc111x_UART.c
 *
 *  Created on: Aug 27, 2020
 *      Author: joebe
 */
#include "cc111x_UART.h"
#include "cc1110_config.h"
#include "utils.h"
//#include "log.h"
#include "status.h"
#include "scrambler.h"
#include "cc_tx_init.h"
//#include "sysview.h"
#include <string.h>

#undef __FILE_ID__
#define __FILE_ID__ 26

//extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
//extern UART_HandleTypeDef huart5;
volatile extern uint8_t tx_thr_flag;
volatile extern uint8_t tx_fin_flag;
//volatile extern uint8_t rx_sync_flag;
//volatile extern uint8_t rx_finished_flag;
//volatile extern uint8_t rx_thr_flag;

static uint8_t tx_frag_buf[2 + CC1120_TX_FIFO_SIZE];


/**
 * Delay for \p us microseconds.
 * NOTE: This delay function is not so accurate!!!
 * @param us how many microseconds to delay the execution
 */
static inline void
delay_us (uint32_t us)
{
  volatile uint32_t cycles = (SystemCoreClock / 1000000L) * us;
  volatile uint32_t start = 0;
  do {
    start++;
  }
  while (start < cycles);
}

/**
 * Reads a register from the TX CC1120
 * @param addr the desired register address
 * @param data memory to store the value of the register
 * @return the first byte of the SPI buffer. Can be used for error checking
 */
uint8_t
cc_tx_rd_reg (uint16_t addr, uint8_t *data)
{
  uint8_t temp_TxBuffer[4] = { 0, 0, 0, 0 };
  uint8_t temp_RxBuffer[4] = { 0, 0, 0, 0 };
  uint8_t len = 0;


  if (addr >= CC_EXT_ADD) {
      len = 3;

      temp_TxBuffer[0] = 0xAF;
      temp_TxBuffer[1] = (uint8_t) (0x00FF & addr);
      temp_TxBuffer[2] = 0;
    }
  else {
    len = 2;
    /* bit masked for read function */
    addr |= 0x0080;
    temp_TxBuffer[0] = (uint8_t) (0x00FF & addr);
    temp_TxBuffer[1] = 0;
  }
  //CSn pin
  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  //SEND THROUGH UART
  delay_us(4);
  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

  *data = temp_RxBuffer[len - 1];

  return temp_RxBuffer[0];
}

/**
 * Writes a value to a register of the TX CC1120
 * @param addr the address of the register
 * @param data the data to be written
 * @return the first byte of the SPI buffer. Can be used for error checking
 */
uint8_t
cc_tx_wr_reg (uint16_t addr, uint8_t data)
{

  uint8_t aTxBuffer[4];
  uint8_t aRxBuffer[4] = { 0, 0, 0, 0 };
  uint8_t len = 0;

  if (addr >= CC_EXT_ADD) {
    len = 3;

    aTxBuffer[0] = 0x2F;
    aTxBuffer[1] = (uint8_t) (0x00FF & addr);
    aTxBuffer[2] = data;
  }
  else {
    len = 2;

    aTxBuffer[0] = (uint8_t) (0x00FF & addr);
    aTxBuffer[1] = data;
  }
  //CSn of tx
  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
  //SEND THROUGH UART
  HAL_GPIO_WritePin (GPIOB, GPIO_PIN_12, GPIO_PIN_SET);

  return aRxBuffer[0];
}
