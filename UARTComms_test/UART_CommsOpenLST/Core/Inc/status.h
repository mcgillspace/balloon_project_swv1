/*
 * status.h
 *
 *  Created on: Aug 27, 2020
 *      Author: joebe
 */

#ifndef __STATUS_H_
#define __STATUS_H_


enum {
  COMMS_STATUS_DMA_ERROR = -9,
  COMMS_STATUS_RF_OFF = -8,
  COMMS_STATUS_RF_SWITCH_CMD = -7,
  COMMS_STATUS_RXFIFO_ERROR = -6,
  COMMS_STATUS_INVALID_FRAME = -5,
  COMMS_STATUS_TIMEOUT = -4,
  COMMS_STATUS_NO_DATA = -3,
  COMMS_STATUS_BUFFER_OVERFLOW = -2,
  COMMS_STATUS_BUFFER_UNDERFLOW = -1,
  COMMS_STATUS_OK = 0,
};

#endif /* APPLICATION_USER_CORE_STATUS_H_ */
