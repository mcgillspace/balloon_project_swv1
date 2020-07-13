#include "pch.h"
#include <iostream>
#include <sstream>

#include <uEye.h>
#include <uEye_tools.h>
#include <conio.h>
#include <tchar.h>
#include "testCameraC.h"

using namespace std;

int main()
{
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
	if (verbose)
	{
		cout << "Please Select mode:" << endl;
		cout << "Press S for Sotware mode" << endl;
		cout << "Press H for Hardware mode" << endl;
	}
	// Awaits input from user (Either hardware or software trigger input)
	while (1)
	{
		if (_kbhit())
		{
			//If the User presses S, the mode will be switched to software trigger mode 
			int key = _getch();
			if ((key == 's') || (key == 'S'))
			{
				nMode = IS_SET_TRIGGER_SOFTWARE;
				break;
			}

			//If the User presses H, the mode will be switched to hardware trigger mode (rising edge)
			if ((key == 'h') || (key == 'H'))
			{
				nMode = IS_SET_TRIGGER_LO_HI;
				break;
			}
		}
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		DispatchMessage(&msg);
	}
	//Sets the trigger mode.
	//TO DO: need to do something special if it is hardware triggered!
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
		nRet = capture(hCam);
		if (nRet == 1)
		{
			if (verbose) 
			{
				cout << "Program ran successfully" << endl;
			}
		}
		else
		{
			if (verbose)
			{
				cout << "Whoops, something went wrong" << endl;
			}
			return 1;
		}
	}
	return 0;
}