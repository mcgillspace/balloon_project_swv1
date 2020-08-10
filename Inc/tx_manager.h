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

#ifndef INC_TX_MANAGER_H_
#define INC_TX_MANAGER_H_

#include <stdint.h>
#include <stdlib.h>


#define MAX_PKT_LEN         210 /*ECSS_HEADER_SIZE + ECSS_DATA_HEADER_SIZE + MAX_PKT_DATA + ECSS_CRC_SIZE*/

#define MAX_PKT_DATA        198
#define TC_MAX_PKT_SIZE     210
#define TC_MIN_PKT_SIZE     11 //12  /*ECSS_HEADER_SIZE + ECSS_DATA_HEADER_SIZE + ECSS_CRC_SIZE*/

#define MAX_PKT_EXT_DATA    2051
#define TC_MAX_PKT_EXT_SIZE 2063

int32_t
tx_data(const uint8_t *in, size_t len, uint8_t *dev_rx_buffer, uint8_t is_wod,
	size_t timeout_ms);


void comms_init();

#endif /* INC_TX_MANAGER_H_ */
