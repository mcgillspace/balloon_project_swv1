/*
 * gps.c
 *
 *  Created on: 25 Jul 2020
 *      Author: David Castonguay
 *
 *	Written for use on HAB.  gps.c is strictly a file that
 *	is used for purposes on high altitude projects and not satellites.
 *	Parsing code taken from UPSAT (Interrupt, logic and fields)
 *
 *
 */
#include "gps.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx.h"
#include "HAB_Error.h"
#include "time_manager.h"
#include "cc112x_spi.h"
#include "status.h"
#include "ax25.h"
#include "tx_manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef hspi2;

static uint8_t spi_buf[AX25_PREAMBLE_LEN
		       + AX25_POSTAMBLE_LEN
		       + AX25_MAX_FRAME_LEN + AX25_MAX_ADDR_LEN];

void init_gps_uart() {
    /* Set up UART4 for GPS */
	vsi_tick1 = HAL_GetTick();
	vsi_flag =0;
    memset(gps_sentence, 0, NMEA_MAX_LEN);
    HAL_UART_Receive_IT(&huart2, gps_buffer, NMEA_MAX_LEN);

}


void reset_gps_flag() {
    gps_flag = 0;
}


void UART_GPS_Receive_IT(UART_HandleTypeDef *huart) {
    uint8_t c;

    c = (uint8_t) (huart->Instance->DR & (uint8_t) 0x00FFU);
    if (huart->RxXferSize == huart->RxXferCount && c == '$') {
        *huart->pRxBuffPtr++ = c;
        huart->RxXferCount--;
        //start timeout
    } else if (c == '$') {
        huart->RxXferCount = huart->RxXferSize;
        *huart->pRxBuffPtr++ = c;
        huart->RxXferCount--;
        //error
        //event log
        //reset buffers & pointers
        //start timeout
    } else if (c == 0xa) {
        *huart->pRxBuffPtr++ = c;
        huart->RxXferCount--;
        *huart->pRxBuffPtr++ = 0;
        gps_flag = 1;
        huart->pRxBuffPtr = &gps_buffer;
        memset(gps_sentence, 0, NMEA_MAX_LEN);
        for (uint8_t i = 0; i < NMEA_MAX_LEN; i++) {
            gps_sentence[i] = gps_buffer[i];
        }
        huart->RxXferCount = huart->RxXferSize;
    } else if (huart->RxXferSize > huart->RxXferCount) {
        *huart->pRxBuffPtr++ = c;
        huart->RxXferCount--;
    }
    /* Errror */
    if (huart->RxXferCount == 0U) {
        //huart->pRxBuffPtr = &gps;
        huart->RxXferCount = huart->RxXferSize;
    }

}

int init_gps(struct time_utc gps_utc, _gps_state *gps_state_value) {
	int error_status_value;

    init_gps_uart();
    /* Set RTC alarm to open GPS because the time isn't set from OBC */
    //HAL_SetAlarm_GPS(gps_utc.hour, GPS_ALARM_ON_INIT, gps_utc.sec);
    gps_state_value->status = GPS_OFF;
    error_status_value = 0;
    reset_gps_flag();

    return error_status_value;
}

_HAB_state update_gps(_gps_state *gps_state_value) {

	//hab_error_status error_status_value = ERROR_OK;
    //uint8_t gps_flash[7] = { 0 };

//    if (gps_state_value->status == GPS_UNLOCK
//    		|| gps_state_value->status == GPS_RESET) {
//    	/* Reset GPS, to try again */
//    	if (gps_state_value->reset_flag == true) {
//    		adcs_pwr_switch(SWITCH_OFF, GPS);
//    		HAL_Delay(100);
//    		adcs_pwr_switch(SWITCH_ON, GPS);
//    		gps_state_value->reset_flag = false;
//    	}
    	/* Get the GPS sentences and if is valid put in gps_state struct */
    get_gps_sentences();
    	/* Check if the gps_struct is valid and update the time and TLE */
    	if (gps_state_value->num_sat >= 3
				&& gps_state_value->p_gps_ecef.LON.D != 0
				&& gps_state_value->p_gps_ecef.LAT.D != 0
				&& gps_state_value->p_gps_ecef.ALT != 0) {


    		gps_set_seconds(gps_state_value);
    		//printf("%d",vsi_flag);

    		if(vsi_flag==0) {
    			old_alt=gps_state_value->p_gps_ecef.ALT;
    			avg_alt=0;
    			vsi_tick0 = HAL_GetTick();
    		}
    		if(vsi_flag>=1){
    			avg_alt = avg_alt*vsi_flag;
    			avg_alt += (gps_state_value->p_gps_ecef.ALT-old_alt);
    			avg_alt/=(vsi_flag+1);
    			old_alt=gps_state_value->p_gps_ecef.ALT;
    		}
    		if(vsi_flag==3){
    			vsi_flag=-1;
    			vsi_tick1 = HAL_GetTick();
    			gps2vsi(gps_state_value);
    			prepare_gps_pkt(gps_state_value);
    		}

    		vsi_flag++;


    		/* Update time and set ADCS RTC */
			//hab_time.gps_sec = gps_state_value->sec;
			//gps2utc(&hab_time);


			//set_time_UTC(hab_time.utc);
            /* Update time of OBC */
            //time_management_force_time_update(OBC_APP_ID);
            /* Calculate new TLE */
//            tle_epoch(&hab_time);
//            temp_tle = calculate_tle(gps_state_value->p_gps_ecef,
//                    gps_state_value->v_gps_ecef, hab_time.tle_epoch);
//            if (update_tle(&upsat_tle, temp_tle) == TLE_NORMAL) {
//                if (flash_write_tle(&upsat_tle) == FLASH_ERROR) {
//                    error_status_value = ERROR_FLASH;
//                }
//            } else {
//                error_status_value = ERROR_TLE;
//            }
            /* Set GPS alarm to hit in 5 hours */
            //adcs_pwr_switch(SWITCH_OFF, GPS);
//            get_time_UTC(&hab_time.utc);
//            gps_state_value->status = HAL_SetAlarm_GPS_ON(hab_time.utc);
//            if (gps_state_value->status == GPS_ERROR_FLASH) {
//                error_status_value = ERROR_FLASH;
//                gps_state_value->status = GPS_OFF;
//            }
            /* Write to flash GPS lock time to recover after reset */
//            gps_flash[0] = gps_state.num_sat;
//            cnv16_8(gps_state.week, &gps_flash[1]);
//            cnv32_8((uint32_t) gps_state.sec, &gps_flash[3]);
//            if (flash_erase_block4K(GPS_LOCK_BASE_ADDRESS) == FLASH_NORMAL) {
//                flash_write_page(gps_flash, sizeof(gps_flash),
//                GPS_LOCK_BASE_ADDRESS);
//            } else {
//                error_status_value = ERROR_FLASH;
//            }
            /* Initialize again GPS state */
            gps_state_value->p_gps_ecef.LON.D = 0;
            gps_state_value->p_gps_ecef.LON.M = 0;
            gps_state_value->p_gps_ecef.LON.NSEW = 0;
            gps_state_value->p_gps_ecef.LAT.D = 0;
            gps_state_value->p_gps_ecef.LAT.M = 0;
            gps_state_value->p_gps_ecef.LAT.NSEW = 0;
            gps_state_value->p_gps_ecef.ALT = 0;
            gps_state_value->sog_gps = 0;
            gps_state_value->sec = 0;
            gps_state_value->utc_time = 0;
            gps_state_value->num_sat = 0;
        }
//    } else if (gps_state_value->status == GPS_OFF) {
//        adcs_pwr_switch(SWITCH_OFF, GPS);
//        error_status_value = ERROR_OK;
//    } else if (gps_state_value->status == GPS_ERROR_FLASH) {
//        error_status_value = ERROR_FLASH;
//        gps_state_value->status = GPS_OFF;
//    }
    	//}
    return HAB_OK;
}

void prepare_gps_pkt(_gps_state *state){

	//transfer coordinates from DDM to DD
	double DDlat = state->p_gps_ecef.LAT.D + (state->p_gps_ecef.LAT.M/60);
	double DDlon = state->p_gps_ecef.LON.D + (state->p_gps_ecef.LON.M/60);

	uint8_t full_pkt [DL_PKT_SIZE*2] = {'0'};
	memset(full_pkt, 0, DL_PKT_SIZE*2);
	static uint8_t rec_data [DL_PKT_SIZE];
	static uint8_t lat_pkt [9];
	static uint8_t lon_pkt [9];
	static uint8_t utc_pkt [6];
	static uint8_t alt_pkt [7];
	static uint8_t sog_pkt [4];
	static uint8_t vsi_pkt [4];
	snprintf(lat_pkt, 9, "%.5f", DDlat);
	lat_pkt[8] = state->p_gps_ecef.LAT.NSEW;
	snprintf(lon_pkt, 9,"%.5f", DDlon);
	lon_pkt[8] = state->p_gps_ecef.LON.NSEW;
	snprintf(utc_pkt, 7,"%d", state->utc_time);
	snprintf(alt_pkt, 8,"%f", state->p_gps_ecef.ALT);
	snprintf(sog_pkt, 5,"%f", state->sog_gps);
	snprintf(vsi_pkt, 5,"%f", state->vsi_gps);

	int *address[5] = {&lat_pkt,&lon_pkt,&alt_pkt,&vsi_pkt,&sog_pkt};
	strncpy(full_pkt, utc_pkt, 6);
	strcat(full_pkt, ",");
//	for(int i = 0; i<5;i++){
//		strcat(full_pkt, address[i]);
//		strcat(full_pkt, ",");
//	}
	strcat(full_pkt, lat_pkt);
	strcat(full_pkt, ",");
	strcat(full_pkt, lon_pkt);
	strcat(full_pkt, ",");
	strcat(full_pkt, alt_pkt);
	strcat(full_pkt, ",");
	strncat(full_pkt, vsi_pkt,4);  //I have now clue why strcat stops working here, had to reside to strncat
	strcat(full_pkt, ",");
	strncat(full_pkt, sog_pkt,4);  //Same magical error here

	//cc_tx_data_continuous (full_pkt, DL_PKT_SIZE, rec_data,10);

	memset(spi_buf, 0, sizeof(spi_buf));
	strncat(full_pkt, full_pkt,DL_PKT_SIZE);
	tx_data(full_pkt,DL_PKT_SIZE*2,spi_buf,0,4000);


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

void HAL_GPS_UART_IRQHandler(UART_HandleTypeDef *huart) {
		uint32_t gps_uart_tmp1, gps_uart_tmp2;

		gps_uart_tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE);
		gps_uart_tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_RXNE);
		/* UART in mode Receiver ---------------------------------------------------*/
		if ((gps_uart_tmp1 != RESET) && (gps_uart_tmp2 != RESET)) {
			UART_GPS_Receive_IT(huart);
		}
	}

void gps2vsi(_gps_state *state){
	double s1= vsi_tick1/1000;
	double s0= vsi_tick0/1000;
	double dt = (s1-s0)/10;
	double dA = avg_alt;

	state->vsi_gps = dA/dt;


}

void gps_set_seconds(_gps_state *state){
	int time_utc = state->utc_time;
	int time_tok[6];
	for(int i=0;i<6;i++)
	{
		time_tok[i] = time_utc%10;
		time_utc /= 10;
	}
	int sec = time_tok[0]+time_tok[1]*10;
	int min = time_tok[2]+time_tok[3]*10;
	int hr = time_tok[4]+time_tok[5]*10;

	int total_sec = sec + min*60 +hr*60*60;
	state->sec = total_sec - hab_sec.HAB_start_sec;

	HAL_sys_setTime(hr,min,sec);

}

void get_gps_sentences() {
    /* Get 16 sentences for GPS to parse */
    for (uint8_t i = 0; i < 2 * NMEA_NUM_SENTENCES; i++) {
        if (/*get_gps_flag()*/ gps_flag == 1) {
            reset_gps_flag();
            gps_parse_fields(&gps_sentence, NMEA_MAX_LEN, gps_parser);
            gps_parse_logic(&gps_parser, &gps_state);
            //SYSVIEW_PRINT("%s", gps_sentence);
        }
    }
}

_HAB_state gps_parse_fields(uint8_t *buf, const uint8_t size,
        uint8_t (*res)[NMEA_MAX_FIELDS]) {

    uint8_t gps_crc = 0;
    uint8_t field = 0;
    uint8_t cnt = 0;

//    if (!C_ASSERT(size <= NMEA_MAX_LEN) == 1) {
//        return HAB_ERROR;
//    }

    for (uint8_t i = 0; i < size; i++) {

        gps_crc = gps_crc ^ buf[i];

        if (buf[i] == ',') {

            res[field++][cnt] = 0;
            cnt = 0;

        } else if (buf[i] == '*') {

            res[field][cnt] = 0;

            uint8_t res_crc = strtol(&buf[i + 1], &buf[i + 2], 16);
            if (gps_crc != res_crc) {
                return HAB_ERROR; //increase CRC
            } else {
                return HAB_OK;
            }

        } else {
            res[field][cnt++] = buf[i];
        }

//        if (!C_ASSERT(field < NMEA_MAX_FIELDS) == 1) {
//            return HAB_ERROR;
//        }
//        if (!C_ASSERT(cnt < NMEA_MAX_FIELD_SIZE) == 1) {
//            return HAB_ERROR;
//        }
    }

    return HAB_OK;
}

int gps_parse_logic(const uint8_t (*res)[NMEA_MAX_FIELDS],
        _gps_state *state) {

    /*
     $GPGSA,M,3,31,32,22,24,19,11,17,14,20,,,,1.6,0.9,1.3*3E

     GSA Satellite status
     M Auto selection of 2D or 3D fix (M = manual)
     3 3D fix - values include: 1 = No Fix
     2 = 2D Fix
     3 = 3D Fix
     31,32... PRNs of satellites used for Fix (space for 12)
     1.6 Position Dilution of Precision (PDOP)
     0.9 Horizontal Dilution of Precision (HDOP)
     1.3 Vertical Dilution of Precision (VDOP)
     *3e The checksum data, always begin with *
     */

//    if (strncmp("$GPGSA", &res[NMEA_HEADER][0], NMEA_HEADER_SIZE) == 0) {
//        state->d3fix = strtol(&res[NMEA_GSA_3DFIX][0],
//                &res[NMEA_GSA_3DFIX][NMEA_MAX_FIELD_SIZE], 10);
//    }
//    /*
//     LSP – LEO Satellite Position – The piNAV SENTENCE
//     $PSLSP,193772.0585851,780,3963889.204,1001383.917,4879428.991,5,4.5*72
//     LEO satellite position
//     GPS time [s]
//     GPS week
//     X position referenced to WGS-84 [m]
//     Y position referenced to WGS-84 [m]
//     Z position referenced to WGS-84 [m]
//     Number of satellites used for PVT
//     Position Dilution of Precision (PDOP)
//     The checksum data, always begin with *
//     */
//
//    else if (strncmp("$PSLSP", &res[NMEA_HEADER][0], NMEA_HEADER_SIZE) == 0) {
//        state->sec = strtod(&res[NMEA_GPS_TIME][0],
//                &res[NMEA_GPS_TIME][NMEA_MAX_FIELD_SIZE]);
//        state->week = strtol(&res[NMEA_GPS_WEEK][0],
//                &res[NMEA_GPS_WEEK][NMEA_MAX_FIELD_SIZE], 10);
//        state->p_gps_ecef.LON = (strtod(&res[NMEA_LSP_X_WGS][0],
//                &res[NMEA_LSP_X_WGS][NMEA_MAX_FIELD_SIZE])) / 1000;
//        state->p_gps_ecef.LAT = (strtod(&res[NMEA_LSP_Y_WGS][0],
//                &res[NMEA_LSP_Y_WGS][NMEA_MAX_FIELD_SIZE])) / 1000;
//        state->p_gps_ecef.ALT = (strtod(&res[NMEA_LSP_Z_WGS][0],
//                &res[NMEA_LSP_Z_WGS][NMEA_MAX_FIELD_SIZE])) / 1000;
//    }
//
//    /*
//     LSV – LEO Satellite Velocity – The piNAV SENTENCE
//     $PSLSV,193772.0585851,780,0.051,0.017,0.034,5,4.5*7B
//     LEO satellite velocity
//     GPS time [s] to which the rising edge of the Valid Position Pulse (VPP) was calculated
//     GPS week
//     v X velocity referenced to WGS-84 [m/s]
//     v Y velocity referenced to WGS-84 [m/s]
//     v Z velocity referenced to WGS-84 [m/s]
//     Number of satellites used for PVT
//     Position Dilution of Precision (PDOP)
//     The checksum data, always begin with *
//     */
//
//    else if (strncmp("$PSLSV", &res[NMEA_HEADER][0], NMEA_HEADER_SIZE) == 0) {
//        state->v_gps_ecef.x = (strtod(&res[NMEA_LSV_VX_WGS][0],
//                &res[NMEA_LSV_VX_WGS][NMEA_MAX_FIELD_SIZE])) / 1000;
//        state->v_gps_ecef.y = (strtod(&res[NMEA_LSV_VY_WGS][0],
//                &res[NMEA_LSV_VY_WGS][NMEA_MAX_FIELD_SIZE])) / 1000;
//        state->v_gps_ecef.z = (strtod(&res[NMEA_LSV_VZ_WGS][0],
//                &res[NMEA_LSV_VZ_WGS][NMEA_MAX_FIELD_SIZE])) / 1000;
//    }
//
//    /*
//     GGA - Fix Data - The NMEA SENTENCE
//     $GNGGA,172120.384,5219.0671,N,05117.0926,E,1,9,0.9,371262.1,M,0,M,,,*54
//     Global Positioning System Fix Data
//     Fix taken at 17:21:20.384 UTC
//     Latitude 52 deg 19.0671' N
//     Longitude 51 deg 17.0926' E
//     Fix quality:
//     0 = Invalid
//     1 = GPS Fix (SPS)
//     Number of satellites being tracked
//     Horizontal Dilution of Precision (HDOP)
//     Altitude, meters, above WGS84 ellipsoid 1
//     Height of the Geoid (mean sea level) above WGS84 ellipsoid
//     Time in seconds since last DGPS update
//     DGPS station ID number
//     The checksum data, always begin with *
//     */

	if(strncmp("$GNRMC", &res[NMEA_HEADER][0], NMEA_HEADER_SIZE) == 0) {

	            state->sog_gps = knots2mps(strtod(&res[NMEA_RMC_SOG][0],
	                                            &res[NMEA_RMC_SOG][NMEA_MAX_FIELD_SIZE]));
	        }
	else if(strncmp("$GNGGA", &res[NMEA_HEADER][0], NMEA_HEADER_SIZE) == 0) {

        state->utc_time = strtof(&res[NMEA_GGA_TIME][0],
                &res[NMEA_GGA_TIME][NMEA_MAX_FIELD_SIZE]);
        if(state->first_receive_flag == 0){
        	//log the first ever received utc time as start of flight
        	hab_sec.HAB_start_utc = state->utc_time;
        	state->first_receive_flag = 1;
        	gps_setStart_seconds();
        }
        state->num_sat = strtof(&res[NMEA_GGA_NUM_SAT][0],
                &res[NMEA_GGA_NUM_SAT][NMEA_MAX_FIELD_SIZE]);
        double lon = strtod(&res[NMEA_GGA_LON][0],
        				&res[NMEA_GGA_LON][NMEA_MAX_FIELD_SIZE]);
        double lat = strtod(&res[NMEA_GGA_LAT][0],
                		&res[NMEA_GGA_LAT][NMEA_MAX_FIELD_SIZE]);
        state->p_gps_ecef.LON.NSEW = res[NMEA_GGA_EW][0];
        state->p_gps_ecef.LAT.NSEW = res[NMEA_GGA_NS][0];
        state->p_gps_ecef.LON.D = ((int)lon/100);
        state->p_gps_ecef.LON.M = lon - state->p_gps_ecef.LON.D*100;
        state->p_gps_ecef.LAT.D = ((int)lat/100);
        state->p_gps_ecef.LAT.M = lat - state->p_gps_ecef.LAT.D*100;
        state->p_gps_ecef.ALT = strtod(&res[NMEA_GGA_ALT][0],
                                        &res[NMEA_GGA_ALT][NMEA_MAX_FIELD_SIZE]);
    }


    return 0;

}

double knots2mps(double sog){
	return sog/KNOTS_2_MPS;
}


