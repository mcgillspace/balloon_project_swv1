#include <iostream>
#include <sstream>

#include <ueye.h>

#include <curses.h>
#include "cameraLibrary.h"

using namespace std;

int main(int args, char *argv[])
{
	//2) mode number (0 being capture a single frame, 1 being capture a burst of frames, 2 being capture a video)
	//3) burst size
	
	//To troubleshoot, code would print out some statements
	BOOL verbose = verb();
	int nRet = 0;

	//Camera Initialization
	HIDS hCam = initialize(nRet);

	//Catches the case if the camera initialization has failed 
	if (hCam == 0)
	{
		exit(1);
		return 1;
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
		exit(1);
		return 1;
	}
	if (verbose) 
	{
			cout << "Set the camera to trigger mode" << endl;
	}
	//This will be replaced by the SD path in the raspberry Pi. For testing, change 
	//this to the folder where you want the images and videos to be saved at. 
	const char *foldername="/home/alarm/Desktop";

	//The mode in which the camera will be activated in. 
	int mode = atoi(argv[1]);
	cout << mode <<endl;
	if (mode == 0)
	{
		nRet = captureSingle(hCam, foldername,TRUE,FALSE,FALSE);
	}
	else if (mode==1)
	{
		nRet = captureBurst(hCam, foldername, atoi(argv[2]));

	}
	//else
	//{
	//	nRet = captureVideo(hCam,foldername,30); //NOT FINISHED YET 
	//}
	
	return 0;
}
