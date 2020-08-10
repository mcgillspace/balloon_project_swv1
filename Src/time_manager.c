/*
 * time_manager.c
 *
 *  Created on: 25 Jul 2020
 *      Author: David Castonguay
 */
#include "time_manager.h"

time_keeping_hab hab_time = { .set_time = 0, .utc.year = 0, .utc.month = 0,
                                .utc.day = 0, .utc.hour = 0, .utc.min = 0,
                                .utc.sec = 0, .utc.weekday = 0,
                                .decyear = 0.0, .jd = 0.0, .gps_sec = 0.0,
                                .gps_sec = 0.0, .gps_week = 0.0 };
seconds_keeping hab_sec = { .HAB_start_utc=0, .HAB_start_sec = 0 };

void gps2utc(time_keeping_hab *t) {

    double tmp_hour, tmp_min, UT = 0;
    volatile uint32_t iJD, L, N, tmp_year, tmp_month, tmp_day = 0;

    t->jd = (t->gps_week + (t->gps_sec - LEAP_SECOND) / 604800.0)
            * 7.0 + JULIAN_GPS_TIME;

    iJD = (uint32_t) (t->jd + 0.5);
    L = t->jd + 68569;

    N = (4 * L / 146097);
    L = (L - (146097 * N + 3) / 4);
    tmp_year = (4000 * (L + 1) / 1461001);
    L = (L - 1461 * tmp_year / 4 + 31);
    tmp_month = (80 * L / 2447);
    tmp_day = (L - 2447 * tmp_month / 80);
    L = (tmp_month / 11);
    tmp_month = (tmp_month + 2 - 12 * L);
    tmp_year = 100 * (N - 49) + tmp_year + L;

    t->utc.year = (uint8_t) (tmp_year - 2000);
    t->utc.month = (uint8_t) tmp_month;
    t->utc.day = (uint8_t) tmp_day;
    t->utc.weekday = hab_time.utc.weekday;

    UT = (t->jd - iJD + 0.5) * 24;
    tmp_hour = UT;
    t->utc.hour = (uint8_t) tmp_hour;
    tmp_min = (tmp_hour - t->utc.hour) * 60;
    t->utc.min = (uint8_t) tmp_min;
    t->utc.sec = (uint8_t) ((tmp_min - t->utc.min) * 60);

}

void HAL_sys_setTime(uint8_t hours, uint8_t mins, uint8_t sec) {

  RTC_TimeTypeDef sTime;

  sTime.Hours = hours;
  sTime.Minutes = mins;
  sTime.Seconds = sec;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);


}

void HAL_sys_getTime(uint8_t *hours, uint8_t *mins, uint8_t *sec) {

  RTC_TimeTypeDef sTime;

  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

   *hours = sTime.Hours;
   *mins = sTime.Minutes;
   *sec = sTime.Seconds;
}

void HAL_sys_setDate(uint8_t weekday, uint8_t mon, uint8_t date, uint8_t year) {

  RTC_DateTypeDef sDate;

  sDate.WeekDay = weekday;
  sDate.Month = mon;
  sDate.Date = date;
  sDate.Year = year;

  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

}

void HAL_sys_getDate(uint8_t *weekday, uint8_t *mon, uint8_t *date, uint8_t *year) {

  RTC_DateTypeDef sDate;

  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

  *mon = sDate.Month;
  *date = sDate.Date;
  *year = sDate.Year;
  *weekday = sDate.WeekDay;

}

uint32_t HAL_sys_GetTick() {
	return HAL_GetTick();
}

void get_time_UTC(struct time_utc *utc){

    HAL_sys_getTime(&utc->hour, &utc->min, &utc->sec);
    HAL_sys_getDate(&utc->weekday, &utc->month, &utc->day, &utc->year);
}
void set_time_UTC(struct time_utc utc){

    HAL_sys_setTime(utc.hour, utc.min, utc.sec);
    HAL_sys_setDate(utc.weekday, utc.month, utc.day, utc.year);
}


void gps_setStart_seconds(){
	int utc = hab_sec.HAB_start_utc;
	int time_tok[6];
	for(int i=0;i<6;i++)
	{
		time_tok[i] = utc%10;
		utc /= 10;
	}
	int sec = time_tok[0]+time_tok[1]*10;
	int min = time_tok[2]+time_tok[3]*10;
	int hr = time_tok[4]+time_tok[5]*10;

	int total_sec = sec + min*60 +hr*60*60;
	hab_sec.HAB_start_sec = total_sec;


}


