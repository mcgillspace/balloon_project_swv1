#include <iostream>
#include <sstream>

#include <ueye.h>

#include <curses.h>
#include "cameraLibrary.h"

using namespace std;

int main(int args, char *argv[])
{
	//The input to the main function is going to be: 1) path folder to save the image in. 
	//2) mode number (0 being capture a single frame, 1 being capture a burst of frames, 2 being capture a video)
	//3) burst size
	
	//To troubleshoot, code would print out some statements
	BOOL verbose = verb();
	int nRet = 0;

	//Camera Initialization
	HIDS hCam = initialize(nRet);

	//Catches the case if the camera initialization has failed 
	if (hCam == NULL)
	{
		return 0;
	}
	
	//Selecting which mode to run the camera with 
	int nMode;
	nMode = IS_SET_TRIGGER_SOFTWARE;

	//Sets the trigger mode.
	nRet = is_SetExternalTrigger(hCam, nMode);
	if (nRet != IS_SUCCESS)
	{
		if (verbose) 
		{
			cout << "Camera has failed to switch to trigger mode" << endl << endl;
			cout << "Terminating Program..." << endl;
		}
		return 0;
	}
	if (verbose) 
	{
			cout << "Set the camera to trigger mode" << endl;
	}
	//This will be replaced by the SD path in the raspberry Pi. For testing, change 
	//this to the folder where you want the images and videos to be saved at. 
	const char *foldername="/home/alarm/Desktop";

	//The mode in which the camera will be activated in. 
	int mode = (int) argv[1];
	mode = 1;
	if (mode == 0)
	{
		nRet = captureSingle(hCam, foldername);
	}
	else if (mode==1)
	{
		nRet = captureBurst(hCam, foldername, 30);

	}
	//else
	//{
	//	nRet = captureVideo(hCam,foldername,30); //NOT FINISHED YET 
	//}
	
	return 1;
}
