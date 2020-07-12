// testCameraC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>

#include <uEye.h>
#include <uEye_tools.h>
#include <conio.h>
#include <tchar.h>


#define CONSOLEDISPCLASS    "ConsoleDispClass"
#define CONSOLEDISPWINDOW   "ConsoleDispWindow"

using namespace std;

BOOL CreateDisplayWindow();
LRESULT WINAPI ConsoleDispWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HIDS hCam = 0;          // 0 for the next available Camera. 1-254 to access a specific camera by ID
HWND hWndDisplay;
ATOM atom;
SENSORINFO sInfo;

char* pcImageMemory;
int MaxImageSizeX, MaxImageSizeY;
int DisplayWidth, DisplayHeight;
int main()
{
	DisplayWidth = 1280;
	DisplayHeight = 960;

	int nRet = 0;
	MSG msg;
	RECT rc;

	// windows function to create a display window
	CreateDisplayWindow();

	// starts the driver and establishes the connection to the camera
	nRet = is_InitCamera(&hCam, hWndDisplay);
	if (nRet != IS_SUCCESS)
	{
		cout << "ERROR, something is wrong with the USB connection of the camera" << endl;
		cout << "Terminating program..." << endl << endl;
		return 0;
		
	}
	else
	{
		cout << "Camera initialisation was successful!" << endl << endl;
	}

	// you can query information about the sensor type of the camera
	nRet = is_GetSensorInfo(hCam, &sInfo);
	if (nRet == IS_SUCCESS)
	{
		cout << "Camera model: \t\t" << sInfo.strSensorName << endl;
		cout << "Image width: \t" << sInfo.nMaxWidth << endl;
		cout << "Image height: \t" << sInfo.nMaxHeight << endl << endl << endl << endl;
	}

	//Updating the variables 
	MaxImageSizeX = sInfo.nMaxWidth;
	MaxImageSizeY = sInfo.nMaxHeight;
	DisplayWidth = MaxImageSizeX;
	DisplayHeight = MaxImageSizeY;


	///*
	// Displaying a picture of a size below 1280x960 (to get the original image size please put the code block in brackets)
	int n = 1;
	do {
		DisplayWidth = MaxImageSizeX / n;
		n++;
	} while (DisplayWidth >= 1280);
	DisplayHeight = MaxImageSizeY / (n - 1);
	///*/


	int nColorMode;
	int nBitsPerPixel;

	//I put all the options for generalization. The camera used in our purposes is MONOCHROME
	if (sInfo.nColorMode == IS_COLORMODE_BAYER)
	{
		// for color camera models use RGB24 mode
		nColorMode = IS_CM_BGR8_PACKED;
		nBitsPerPixel = 24;
	}
	else if (sInfo.nColorMode == IS_COLORMODE_CBYCRY)
	{
		// for CBYCRY camera models use RGB32 mode
		nColorMode = IS_CM_BGRA8_PACKED;
		nBitsPerPixel = 32;
	}
	else
	{
		// for monochrome camera models use Y8 mode
		nColorMode = IS_CM_MONO8;
		nBitsPerPixel = 8;
	}
	// Sets the color mode to be used when image data are saved or displayed by the graphics card
	is_SetColorMode(hCam, nColorMode);


	// Allocates an image memory for an image, activates it and sets the way in which the images will be displayed on the screen
	int nMemoryId;
	is_AllocImageMem(hCam, MaxImageSizeX, MaxImageSizeY, nBitsPerPixel, &pcImageMemory, &nMemoryId);
	is_SetImageMem(hCam, pcImageMemory, nMemoryId);
	is_SetDisplayMode(hCam, IS_SET_DM_DIB);

	// Configuration of the display window
	SetWindowPos(hWndDisplay, NULL, 0, 0, DisplayWidth, DisplayHeight, SWP_NOMOVE | SWP_NOZORDER);
	GetClientRect(hWndDisplay, &rc);
	SetWindowPos(hWndDisplay, NULL, 0, 0, 2 * DisplayWidth - (rc.right - rc.left), 2 * DisplayHeight - (rc.bottom - rc.top), SWP_NOMOVE | SWP_NOZORDER);
	ShowWindow(hWndDisplay, SW_SHOW);

	// Acquires a single image from the camera
	is_FreezeVideo(hCam, IS_WAIT);

	// Output an image from an image memory in the specified window
	int nRenderMode = IS_RENDER_FIT_TO_WINDOW;
	is_RenderBitmap(hCam, nMemoryId, hWndDisplay, nRenderMode);

	// Dialog with the user
	cout << "Hello, in the following you see a recorded frame of the camera." << endl << endl;
	cout << "To SAVE it please press: \t\t S" << endl;
	cout << "To REFRESH it please press: \t\t R" << endl;
	cout << "And to QUIT the programm please press: \t Q" << endl << endl;
	cout << "HINT: try to hold R. You will get a simple live modus" << endl << endl << endl << endl;

	// Awaits input from user (Save, Refresh, Quit)
	while (1)
	{
		if (_kbhit())
		{
			//If the User presses S, it saves the image by prompting the user to save in in a location 
			int key = _getch();
			if ((key == 's') || (key == 'S'))
			{
				IMAGE_FILE_PARAMS ImageFileParams;
				ImageFileParams.pwchFileName = NULL;
				ImageFileParams.pnImageID = NULL;
				ImageFileParams.ppcImageMem = NULL;
				ImageFileParams.nQuality = 100;
				ImageFileParams.nFileType = IS_IMG_BMP;
				is_ImageFile(hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
			}

			//If the User presses R, it takes another photo 
			if ((key == 'r') || (key == 'R'))
			{
				is_FreezeVideo(hCam, IS_WAIT);
				is_RenderBitmap(hCam, nMemoryId, hWndDisplay, nRenderMode);
			}

			//If the User presses Q, it will quit the program 
			if ((key == 'q') || (key == 'Q'))
				break;
		}
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		DispatchMessage(&msg);
	}

	// Releases an image memory that was allocated. This is necessary in order to avoid pill-ups in the memory 
	nRet = is_FreeImageMem(hCam, pcImageMemory, nMemoryId);
	if (nRet == IS_SUCCESS)
	{
		cout << "The allocated memory has been successfully released!" << endl;
	}
	else
	{
		cout << "ERROR, something happened while trying to release the image memory QQ" << endl;
	}

	// Disables the hCam camera handle and releases the data structures and memory areas taken up by the uEye camera
	nRet = is_ExitCamera(hCam);
	if (nRet == IS_SUCCESS)
	{
		cout << "The camera has been successfully logged off!" << endl << endl;
	}
	else
	{
		cout << "The camera does not want to let you go" << endl << endl; 
	}



	system("pause");
	return 0;
}


//Helper method Functions 
BOOL CreateDisplayWindow()
{
	WNDCLASSEX wcx;
	HMODULE hInstance = GetModuleHandle(NULL);
	if (GetClassInfoEx(hInstance, _T(CONSOLEDISPCLASS), &wcx) == 0)
	{
		// Fill in the window class structure with parameters that describe the main window.
		wcx.cbSize = sizeof(wcx);                 // size of structure
		wcx.style = CS_HREDRAW | CS_NOCLOSE | CS_SAVEBITS | CS_VREDRAW | WS_OVERLAPPED;
		wcx.lpfnWndProc = ConsoleDispWndProc;     // points to window procedure
		wcx.cbClsExtra = 0;                       // no extra class memory
		wcx.cbWndExtra = 0;                       // no extra window memory
		wcx.hInstance = hInstance;                // handle to instance
		wcx.hIcon = NULL;                         // no icon
		wcx.hCursor = NULL;                       // no cursor
		wcx.lpszMenuName = NULL;                  // name of menu resource
		wcx.lpszClassName = _T(CONSOLEDISPCLASS); // name of window class
		wcx.hIconSm = NULL;                       // small class icon
		wcx.hbrBackground = NULL;

		// Register the window class.
		atom = RegisterClassEx(&wcx);

		if (atom != NULL)
		{
			// create our display window
			hWndDisplay = CreateWindow(_T(CONSOLEDISPCLASS), // name of window class
				L"SimpleSingleGrab",        // title-bar string
				WS_OVERLAPPEDWINDOW,        // top-level window
				CW_USEDEFAULT,              // default horizontal position
				CW_USEDEFAULT,              // default vertical position
				DisplayWidth,               // default width
				DisplayHeight,              // default height
				(HWND)NULL,                 // no owner window
				(HMENU)NULL,                // use class menu
				hInstance,                  // handle to application instance
				(LPVOID)NULL);              // no window-creation data

			if (!hWndDisplay)
			{
				DWORD a = GetLastError();
				LPVOID lpMsgBuf;
				FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_IGNORE_INSERTS, NULL, a, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR)&lpMsgBuf, 0, NULL);

				// Free the buffer.
				LocalFree(lpMsgBuf);
				::UnregisterClass(_T(CONSOLEDISPCLASS), hInstance);
				atom = NULL;
			}
		}
	}
	return (atom != NULL);
}

LRESULT WINAPI ConsoleDispWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rc;

	switch (msg)
	{
	case WM_CREATE:
		// Initialize the window.
		return 0;

	case WM_ERASEBKGND:
		if (GetUpdateRect(hwnd, &rc, FALSE))
		{
			HDC hdc = BeginPaint(hwnd, &ps);
			FillRect(hdc, &rc, (HBRUSH)(COLOR_WINDOW + 1));
			EndPaint(hwnd, &ps);
		}
		return 1;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
