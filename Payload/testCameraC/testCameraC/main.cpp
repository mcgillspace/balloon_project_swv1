#include "pch.h"
#include <iostream>
#include <sstream>

#include <uEye.h>
#include <uEye_tools.h>
#include <conio.h>
#include <tchar.h>
#include "cameraLibrary.h"

using namespace std;

int main(int args, char *argv[])
{
	wchar_t path[100] = _T("C:\\Users\\joebe\\Desktop\\image.jpg");
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
	
	MSG msg;

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
	
	int mode = (int) argv[1];
	if (mode == 0)
	{
		nRet = captureSingle(hCam, path);
	}
	else if (mode==1)
	{
		nRet = captureBurst(hCam, path, (int)argv[2]);

	}
	else
	{
		nRet = captureVideo(hCam,path); //NOT FINISHED YET 
	}
	
	return 1;
}
