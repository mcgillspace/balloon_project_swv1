//Include the camera packages 
#include<stdio.h>

//Packages required for the camera functions
#include"uEye.h"
#include"uEye_tools.h"
#include<uEye_api.lib>
#include<uEye_tools.lib>
#include<uEye_tools.dll>
#include<uEye_Api.dll>
#include"ueye.h"
#include<libueye_api.so>

//Need to define global header values corresponding to the handle to the camera, photo size, color mode...
//Before taking a photo or anything, we can set the camera parameters below
//Test out the best configuration and settings for the camera for our purposes
//A simple algorithm when called, to take a single frame screenshot with the model UI-3241LE-M-GL

//1) Open the camera and get device handle using the is_InitCamera() function
//2) Get some useful information about the camera using is_GetSensorInfo()
//3) Set the color mode and AOI (size of image) with is_SetColorMode() and is_AOI() respectively 
//4) Allocation of memory 
	//a) Define a buffer size for the memory 
	//b) Allocate the user memory: 
		//UserMem = GlobalAlloc(GPTR, BUfferSize)
	//c) Get pointer to the user memory
		//pUserMem = (char*) GlobalLock(UserMem)
	//d) Activate user memory for the uEye API. User memory pointer must be passed
		//is_SetAllocatedImageMem() 
//5) Trigger:
	//a) is_FreezeVideo() to acquire a single image 
	//b) If we want to display, it would be is_RenderBitmap() 
//6) Release the memory allocated  
//7) Send photo info back to STM32 with I2C protocol, and then to SD card
//We can make multiple library files and then have a main function at the end that does everything 

//One of those files should be definitely responsible for using inputs and outputs for the I2C bus

//TO READ: how to read I2C from bus as an input and do stuff with it
	//Here are a few functions to help out
		//is_SetExternalTrigger
		//is_IO() (not too sure about what this function does)

//GENERAL NOTES 
//We can read and write I2C with both is_ReadI2C() and is_WriteI2C(). There is also an optional function that 
//activates the I2C stop bit (is_DeviceFeature()) 

//To save an image, we can use the is_ImageFile() function in the format of either a BMP, JPEG or PNG

//There should also be a file responsible if we want to change the mode, frame, color sets, anything 
//related to the specs of the camera. There is a whole flowchart associated to doing just that

//If we want, for some reason, to access the camera memory
