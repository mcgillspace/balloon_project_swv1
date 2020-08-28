/*
 * cc_tx_init.h
 *
 *  Created on: Aug 27, 2020
 *      Author: joebe
 */

#ifndef __CC_TX_INIT_H_
#define __CC_TX_INIT_H_

#include "cc_definitions.h"
#include "cc111x_spi.h"
#include <stdint.h>

void
tx_manualCalibration ();
void
tx_registerConfig ();
void
tx_cw_registerConfig ();

#endif

#endif /* APPLICATION_USER_CORE_CC_TX_INIT_H_ */
