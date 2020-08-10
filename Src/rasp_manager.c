/*
 * rasp_manager.c
 *
 *  Created on: 10 Aug 2020
 *      Author: david
 */

#include "stm32l1xx_hal.h"
#include "rasp_manager.h"
#include "stm32l1xx.h"
#include <stdio.h>

extern I2C_HandleTypeDef hi2c1;

void cam_init(){
	camTick0 = HAL_GetTick();
	IDS_flag=0;
	PI_flag=0;
	DUO_flag=0;
}

void cam_action(){
	camTick1 = HAL_GetTick();
	int tickDif = camTick1-camTick0;
	if(tickDif>IDS_wait && IDS_flag==0){
		raspbCamCom(IDSAlone);
		IDS_flag=1;
	}
	else if(tickDif>PI_wait && PI_flag==0){
		raspbCamCom(PIAlone);
		PI_flag=1;
	}
	else if(tickDif>DUO_wait && DUO_flag==0){
		raspbCamCom(IDS_PI);
		DUO_flag=1;
	}
	else if(tickDif>CYCLE_wait){
		cam_init();
	}
}

void raspbCamCom(int camset){
	switch(camset){
	case 0:
		if (HAL_I2C_Slave_Transmit(&hi2c1, &IDSAlone, 1, 10000) != HAL_OK)
		{
		   	HAL_I2C_Slave_Transmit(&hi2c1, &ErrorBuffer, 1, 10000);
		}
		break;
	case 1:
		if (HAL_I2C_Slave_Transmit(&hi2c1, &PIAlone, 1, 10000) != HAL_OK)
		{
		   	HAL_I2C_Slave_Transmit(&hi2c1, &ErrorBuffer, 1, 10000);
		}
		break;
	case 2:
		if (HAL_I2C_Slave_Transmit(&hi2c1, &IDS_PI, 1, 10000) != HAL_OK)
		{
		   	HAL_I2C_Slave_Transmit(&hi2c1, &ErrorBuffer, 1, 10000);
		}
		break;
	default:
		break;
	}
}

