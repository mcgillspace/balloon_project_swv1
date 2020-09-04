/*
 * upsat-comms-software: Communication Subsystem Software for UPSat satellite
 *
 *  Copyright (C) 2016, Libre Space Foundation <http://librespacefoundation.org/>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tx_manager.h"
#include "ax25.h"
#include "cc112x_spi.h"
#include "cc_tx_init.h"
#include "status.h"
//#include "cw.h"

static uint8_t tmp_buf[AX25_PREAMBLE_LEN + AX25_POSTAMBLE_LEN
		       + AX25_MAX_FRAME_LEN + AX25_MAX_ADDR_LEN];
//static cw_pulse_t cw_buf[AX25_MAX_FRAME_LEN * 10];


typedef enum {
    LD_STATE_FREE           = 1,//!< LD_STATE_FREE No large data activity
    LD_STATE_RECEIVING      = 2,//!< LD_STATE_RECEIVING the large data FSM receives data
    LD_STATE_TRANSMITING    = 3,//!< LD_STATE_TRANSMITING the large data FSM transmits data
    LD_STATE_TRANSMIT_FIN   = 4,//!< LD_STATE_TRANSMIT_FIN the large data TX finished. The engine just waits for possible lost frame requests from the ground
    LD_STATE_RECV_OK        = 5,//!< LD_STATE_RECV_OK the large data FSM successfully received the last frame
    LAST_STATE              = 6 //!< LAST_STATE
}LD_states;

struct _ld_status {
    LD_states state;        		/**< Service state machine, state variable*/
    //TC_TM_app_id app_id;    		/**< Destination app id */
    uint8_t ld_num;         		/**< Sequence number of last fragmented packet stored */
    uint32_t timeout;       		/**< Time of last large data action */
    uint32_t started;                   /**< Time that the large data transfer started */

    uint8_t buf[MAX_PKT_EXT_DATA]; 	/**< Buffer that holds the sequential fragmented packets */
    uint16_t rx_size;         		/**< The number of bytes stored already in the buffer */
    uint8_t rx_lid;         /**/
    uint8_t tx_lid;         /**/
    uint8_t tx_pkt;         /**/
    uint16_t tx_size;         /**/
};

struct _ld_status LD_status = { .state = LD_STATE_FREE,
                                .ld_num = 0,
                                .timeout = 0,
                                .started = 0 } ;

void
large_data_init ()
{
  LD_status.state = LD_STATE_FREE;
  LD_status.ld_num = 0;
  LD_status.timeout = 0;
  LD_status.started = 0;
}


void
comms_init ()
{

  static uint8_t cc_id_tx;

  /* fetch TX ID */
  cc_tx_rd_reg (0x2F8F, &cc_id_tx);

  /* Configure TX CC1120 */
  tx_registerConfig ();


  HAL_Delay (10);
  cc_tx_rd_reg (0x2f8F, &cc_id_tx);

  /* Calibrate TX */
  tx_manualCalibration ();
  cc_tx_rd_reg (0x2f8F, &cc_id_tx);

  //uint8_t freq2;
  //cc_tx_rd_reg(FREQ0,&freq2);

  /* Initialize the TX and RX routines */
  //rx_init();
  //cw_init();

  large_data_init();

  /*Initialize the COMMS statistics mechanism */
  //comms_rf_stats_init(&comms_stats);

  /* Initialize the CC1120 in RX mode */
 // cc_rx_cmd(SRX);

  //pkt_pool_INIT ();

  //comms_wod_init();
  //comms_ex_wod_init();

  /* Initialize all the time counters */
  //stats_tick = HAL_GetTick();
  //rx_fifo_tick = stats_tick;
  //set_cmd_and_ctrl_period(0);
}

/**
 * This routine sends the data using the AX.25 encapsulation
 * @param in the input buffer containing the raw data
 * @param len the length of the input buffer
 * @param dev_rx_buffer a buffer that will hold the SPI resulting bytes
 * @param is_wod set to true if the frame is WOD
 * @param timeout_ms the timeout in milliseconds
 * @return the number of bytes sent or appropriate error code
 */
int32_t
tx_data(const uint8_t *in, size_t len, uint8_t *dev_rx_buffer, uint8_t is_wod,
	size_t timeout_ms)
{
  int32_t ret = 0;
  /* This routine can not handle large payloads */
  if(len == 0) {
    return COMMS_STATUS_NO_DATA;
  }

  if(len > AX25_MAX_FRAME_LEN) {
    return COMMS_STATUS_BUFFER_OVERFLOW;
  }

  /* Prepare the AX.25 frame */
  ret = ax25_send(tmp_buf, in, len, is_wod);
  if(ret < 1){
    return COMMS_STATUS_NO_DATA;
  }

  /* Issue the frame at the CC1120 */
  ret = cc_tx_data_continuous(in, len, dev_rx_buffer, timeout_ms); //TODO: change in to tmp_buf and ret
  if(ret < 1){
    return ret;
  }
  return len;
}



/**
 * Sends data over the air using CW
 * @param in the input data
 * @param len the length of the input data
 * @return the number of the bytes sent or an appropriate negative error code
 */
//int32_t
//tx_data_cw (const uint8_t *in, size_t len)
//{
//  int32_t ret = 0;
//  size_t symbols_num;
//  /* This routine can not handle large payloads */
//  if (len == 0) {
//    return COMMS_STATUS_NO_DATA;
//  }
//
//  if (len > AX25_MAX_FRAME_LEN) {
//    return COMMS_STATUS_BUFFER_OVERFLOW;
//  }
//
//  ret = cw_encode(cw_buf, &symbols_num, in, len);
//  if(ret != CW_OK){
//    return COMMS_STATUS_INVALID_FRAME;
//  }
//
//  ret = cc_tx_cw(cw_buf, symbols_num);
//  if(ret != CW_OK) {
//    return COMMS_STATUS_INVALID_FRAME;
//  }
//  return len;
//}

