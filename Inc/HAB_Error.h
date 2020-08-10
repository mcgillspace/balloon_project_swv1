/*
 * HAB_Error.h
 *
 *  Created on: 25 Jul 2020
 *      Author: david
 */

#ifndef HAB_ERROR_H_
#define HAB_ERROR_H_



typedef enum {
	HAB_OK    = 0,
	HAB_ERROR = 1
} _HAB_state;

typedef enum {
    ERROR_OK = 0,
    ERROR_SGP4,
    ERROR_TLE,
    ERROR_TIME,
    ERROR_SENSOR,
    ERROR_ACTUATOR,
    ERROR_FLASH,
    ERROR_GPS,
    ERROR_HAL_INIT,
    ERROR_UNRESOLVED

} hab_error_status;


#endif /* HAB_ERROR_H_ */
