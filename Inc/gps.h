/*
 * gps.h
 *
 *  Created on: 24 Jul 2020
 *      Author: David Castonguay
 */
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "HAB_Error.h"
#include "time_manager.h"

#ifndef GPS_H_
#define GPS_H_

#define KNOTS_2_MPS 0.51444

#define UART_BUF_SIZE 2063 /*(MAX_PKT_DATA*2)*/
#define MAX_PKT_SIZE  2063

#define DL_PKT_SIZE 49

#define NMEA_MAX_FIELD_SIZE 15
#define NMEA_MAX_FIELDS     22
#define NMEA_HEADER         0
#define NMEA_HEADER_SIZE    6
#define NMEA_MAX_LEN        80
#define NMEA_NUM_SENTENCES  8

#define NMEA_GSA_3DFIX      2

#define NMEA_GPS_TIME       1
#define NMEA_GPS_WEEK       2

#define NMEA_LSP_X_WGS      3
#define NMEA_LSP_Y_WGS      4
#define NMEA_LSP_Z_WGS      5

#define NMEA_LSV_VX_WGS     3
#define NMEA_LSV_VY_WGS     4
#define NMEA_LSV_VZ_WGS     5

#define NMEA_GGA_TIME       1
#define NMEA_GGA_NUM_SAT    7
#define NMEA_GGA_LAT        2
#define NMEA_GGA_NS         3
#define NMEA_GGA_LON        4
#define NMEA_GGA_EW         5
#define NMEA_GGA_ALT        9

#define NMEA_RMC_SOG 		7

typedef enum {
    GPS_ERROR_FLASH = 0,
    GPS_OFF,
    GPS_UNLOCK,
    GPS_RESET
} _gps_status;

typedef struct {
    int D;
    double M;
    char NSEW;
} DDM;

typedef struct {
	DDM LON;
	DDM LAT;
    double ALT;
} coords_t;

typedef struct {
    double x;
    double y;
    double z;
} xyz_t;

typedef struct {
    coords_t p_gps_ecef; // in COORDS
    double sog_gps; // in km/h
    double vsi_gps; //vertical speed indicator
    float cctemp_gps;
    int utc_time;
    int first_receive_flag;
    double sec; //time since depploy
    uint8_t num_sat;
    _gps_status status;
    uint8_t reset_flag;
} _gps_state;

struct uart_data {
    uint8_t uart_buf[UART_BUF_SIZE];
    uint8_t uart_unpkt_buf[UART_BUF_SIZE];
    uint8_t deframed_buf[MAX_PKT_SIZE];
    uint8_t uart_pkted_buf[UART_BUF_SIZE];
    uint8_t framed_buf[UART_BUF_SIZE];
    uint16_t uart_size;
    uint32_t last_com_time;
    uint32_t init_time;
};



uint8_t gps_sentence[NMEA_MAX_LEN];  //should be static?
uint8_t gps_parser[NMEA_MAX_FIELDS][NMEA_MAX_FIELD_SIZE];//should be static?
uint8_t gps_flag;
uint8_t vsi_flag;
static double vsi_tick0;
static double vsi_tick1;
double old_alt;
double avg_alt;

_gps_state gps_state;


void gps_set_seconds(_gps_state *state);
double knots2mps(double sog);
void HAL_GPS_UART_IRQHandler(UART_HandleTypeDef *huart);
void gps2vsi(_gps_state *state);
int init_gps(struct time_utc gps_utc, _gps_state *gps_state_value);
void UART_GPS_Receive_IT(UART_HandleTypeDef *huart);
void reset_gps_flag();
void prepare_gps_pkt(_gps_state *state);
_HAB_state update_gps();
void get_gps_sentences();
int gps_parse_logic(const uint8_t (*res)[NMEA_MAX_FIELDS],
        _gps_state *state);
_HAB_state gps_parse_fields(uint8_t *buf, const uint8_t size,
        uint8_t (*res)[NMEA_MAX_FIELDS]);
uint8_t gps_buffer[NMEA_MAX_LEN];





#endif /* GPS_H_ */
