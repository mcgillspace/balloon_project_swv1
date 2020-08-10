/*
 * rasp_manager.h
 *
 *  Created on: 10 Aug 2020
 *      Author: david
 */

#ifndef RASP_MANAGER_H_
#define RASP_MANAGER_H_

#define IDS_WAIT 20000;
#define PI_WAIT 40000;
#define DUO_WAIT 60000;
#define CYCLE_RESET_WAIT 100000;

uint8_t IDSAlone =0 ;
uint8_t ErrorBuffer = 9;
uint8_t PIAlone = 1;
uint8_t IDS_PI = 2;

int IDS_wait = IDS_WAIT;
int	PI_wait = PI_WAIT;
int DUO_wait = DUO_WAIT;
int CYCLE_wait = CYCLE_RESET_WAIT;

uint8_t IDS_flag;
uint8_t PI_flag;
uint8_t DUO_flag;

int camTick0;
int camTick1;

void cam_init();
void raspbCamCom(int camset);
void cam_action();


#endif /* RASP_MANAGER_H_ */
