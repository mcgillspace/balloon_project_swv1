/*
 * time_manager.h
 *
 *  Created on: 25 Jul 2020
 *      Author: david
 */
#include "stm32l1xx_hal.h"
#ifndef TIME_MANAGER_H_
#define TIME_MANAGER_H_

#define JULIAN_GPS_TIME 2444244.5                           // Julian Date of GPS starting date
#define LEAP_SECOND     17

RTC_HandleTypeDef hrtc;

struct time_utc {
    uint8_t weekday;
    uint8_t day;
    uint8_t month;
    uint8_t year;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
};

typedef struct {
    int HAB_start_utc;
    int HAB_start_sec;
} seconds_keeping;

typedef struct {
    uint8_t set_time;
    struct time_utc utc;
    double decyear; // Decimal year, for IGRF
    double jd; // Julian days from 1st Jan 1900, for SGP4
    double gps_sec; // Time in sec of "gps_week" week
    uint16_t gps_week; // Number of weeks from GPS starting date
} time_keeping_hab;

time_keeping_hab hab_time;
seconds_keeping hab_sec;
void HAL_sys_setTime(uint8_t hours, uint8_t mins, uint8_t sec);

void gps2utc(time_keeping_hab *t);
void get_time_UTC(struct time_utc *utc);

void gps_setStart_seconds();

#endif /* TIME_MANAGER_H_ */
