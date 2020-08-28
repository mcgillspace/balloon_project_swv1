/*
 * cc_tx_init.h
 *
 *  Created on: Aug 27, 2020
 *      Author: joebe
 */

#ifndef __CC_TX_INIT_H_
#define __CC_TX_INIT_H_

#include "cc_definitions.h"
#include "cc111x_UART.h"
#include <stdint.h>

void
tx_manualCalibration ();
void
tx_registerConfig ();
void
tx_cw_registerConfig ();

#endif
