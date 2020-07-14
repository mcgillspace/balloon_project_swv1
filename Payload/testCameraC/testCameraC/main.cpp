#include "pch.h"
#include <iostream>
#include <sstream>

#include <uEye.h>
#include <uEye_tools.h>
#include <conio.h>
#include <tchar.h>
#include "cameraLibrary.h"

using namespace std;

int main()
{
	//Need to make this inputted by the raspberry Pi 4 
	
	wchar_t path[100] = _T("C:\\Users\\joebe\\Desktop\\image.jpg");

	//This is for testing purposes; code will print out statements if it either 
	//succeeds or fails a task.
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
		return 1;
	}
	else
	{
		if (verbose) 
		{
			cout << "Set the camera to trigger mode" << endl;
		}
		nRet = captureSingle(hCam,path);
		if (nRet == 1 && verbose == TRUE)
		{
			cout << "Program ran successfully" << endl;
		}
		else
		{
			if (verbose)
			{
				cout << "Something went wrong" << endl;
			}
			return 1;
		}
	}
	return 0;
}
