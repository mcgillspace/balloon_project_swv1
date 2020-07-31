#include <iostream>
#include <sstream>
#include<stdio.h>
#include<stddef.h>
#include <ueye.h>
//#include <libueye_api.so>
#include <curses.h>
#include <wchar.h>
#include <ctime>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include "cameraSettings.h"

using namespace std;

int MaxImageSizeX, MaxImageSizeY;
int DisplayWidth, DisplayHeight;
int nMemoryId;
char* pcImageMemory;


tm* timeAndDate()
{
	//To extract the current time (hours, minutes and seconds)
	time_t curr_time;
	struct tm *timeinfo;
	time(&curr_time);
	timeinfo = localtime(&curr_time);
	return timeinfo;
}


//Function to parse the pathing and name the image according to the time taken
wchar_t* pathParsing(const char * foldername)
{
	char time_string[80];
	//Gets the current time as a tm object
	tm *timeinfo = timeAndDate();

	//Naming the image file or video file
	strftime(time_string, 80, "/Image_%I_%M_%S.bmp", timeinfo);
	const char *filename = (const char*)time_string;

	//Appending the filename to the foldername 
	std::string fullPath = foldername;
	fullPath += filename;
	const char *fullPathForReal = fullPath.c_str();

	//Converting strings type to wchar_t* accepted by the IDS functions
	cout << fullPathForReal << endl;
	size_t newsize = strlen(fullPathForReal) + 1;
	wchar_t *wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs(wcstring, fullPathForReal,newsize);

	return wcstring;
}

int captureSingle(HIDS hCam, const char *foldername=NULL,bool saveMode=TRUE,bool displayMode=TRUE, bool videoMode=FALSE)
{
	DisplayWidth = 1280;
	DisplayHeight = 960;
	
	int nRet = 0;

	
	// you can query information about the sensor type of the camera
	nRet = is_GetSensorInfo(hCam, &sInfo);
	if (nRet == IS_SUCCESS)
	{
		if (verbose==TRUE && displayMode==TRUE)
		{
			cout << "Camera model: \t\t" << sInfo.strSensorName << endl;
			cout << "Image width: \t" << sInfo.nMaxWidth << endl;
			cout << "Image height: \t" << sInfo.nMaxHeight << endl << endl << endl << endl;

		}
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
	is_AllocImageMem(hCam, MaxImageSizeX, MaxImageSizeY, nBitsPerPixel, &pcImageMemory, &nMemoryId);
	is_SetImageMem(hCam, pcImageMemory, nMemoryId);
	
	// Acquires a single image from the camera
	is_FreezeVideo(hCam, IS_WAIT);

	//If we want to save the image
	if (saveMode == TRUE) 
	{
		IMAGE_FILE_PARAMS ImageFileParams;

		//Saves an image in the specified path
		wchar_t *path = pathParsing(foldername);
		ImageFileParams.pwchFileName = path;
		ImageFileParams.pnImageID = NULL;
		ImageFileParams.ppcImageMem = NULL;
		ImageFileParams.nQuality = 100;
		ImageFileParams.nFileType = IS_IMG_BMP;

		is_ImageFile(hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams, sizeof(ImageFileParams));
	}
	//If we are not taking a video, we can safely release the image memory. If we are taking 
	//a video, then we still need that memory to add it to the AVI frame.
	if (videoMode == FALSE) {
		// Releases an image memory that was allocated. This is necessary in order to avoid pill-ups in the memory 
		nRet = is_FreeImageMem(hCam, pcImageMemory, nMemoryId);
		// Disables the hCam camera handle and releases the data structures and memory areas taken up by the uEye camera
		nRet = is_ExitCamera(hCam);
		system("pause");
	}

	return 1;
}

// Function to take burst of photos; requires the number of desired photos
//TO DO: pause the loop for a few milliseconds

int captureBurst(HIDS hCam, const char *foldername, int BurstSize)
{
	int nRet;
	// Take single photos, updating n each time 
	char time_string[80];
	//Gets the current time as a tm object
	tm *timeinfo = timeAndDate();

	//Naming the folder in which the burst images are going to be located
	strftime(time_string, 80, "/IDS_camera/Burst_%I_%M_%S", timeinfo);

	const char *folderName = (const char*)time_string;

	//Appending the burst folder name to the target folder
	std::string fullPath = foldername;
	fullPath += folderName;
	const char *fullPathForReal = fullPath.c_str();
	int status = 0;

	//Converting strings type to wchar_t* accepted by the CreateDirectory function
	size_t newsize = strlen(fullPathForReal) + 1;
	wchar_t *wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs(wcstring, fullPathForReal, newsize);

	//Creating a directory in the Desktop
	int check = mkdir(fullPathForReal,0777); 
	if (!check) {
		cout << "I created something" << endl;
	}
	for (int i = 0; i < BurstSize; i++)
	{
		int n = captureSingle(hCam, fullPathForReal,TRUE,FALSE,TRUE);
		// Releases an image memory that was allocated. This is necessary in order to avoid pill-ups in the memory 
		nRet = is_FreeImageMem(hCam, pcImageMemory, nMemoryId);
		// Disables the hCam camera handle and releases the data structures and memory areas taken up by the uEye camera

		// If a single capture failed, terminate the program
		if (n == 0)
		{
			return 0;
		}
		// Update user on the number of photos taken 
		if (i == BurstSize && verbose == TRUE)
		{
			cout << "A burst of the indicated size has been taken." << endl;
		}
		else if (verbose==TRUE)
		{
			cout << "Number of photos taken: \t\t" << i+1 << "\n" << endl;
		}
		//This method only works for windows. Need an equivalent for linux 
		usleep(1000000);

	}
	nRet = is_ExitCamera(hCam);
	return 1;
}

//int captureVideo(HIDS hCam, const char *foldername, double frameRate)
//Need to use AVI tools for this
//{
//	DisplayWidth = 1280;
//	DisplayHeight = 960;
//
//	int nRet = 0;
//	INT pnAviID = 0;
//
//	//Initializing the AVI engine
//	nRet = isavi_InitAVI(&pnAviID, hCam);
//	if (nRet == IS_AVI_NO_ERR && verbose==TRUE)
//	{
//		cout << "Initialized AVI file" << endl;
//	}
//
//	//Setting the image size
//	nRet = isavi_SetImageSize(pnAviID, IS_AVI_CM_Y8, DisplayWidth, DisplayHeight, 0, 0, 0);
//	
//	char time_string[80];
//	//Gets the current time as a tm object
//	tm *timeinfo = timeAndDate();
//
//	//Naming the image file or video file
//	strftime(time_string, 80, "\\Video_%I_%M_%S.avi", timeinfo);
//	const char *filename = (const char*)time_string;
//
//	//Appending the filename to the foldername 
//	std::string fullPath = foldername;
//	fullPath += filename;
//	const char *fullPathForReal = fullPath.c_str();
//
//	//Setting an AVI file
//	nRet = isavi_OpenAVI(pnAviID, fullPathForReal);
//
//	//Setting the frames per second
//	nRet = isavi_SetFrameRate(pnAviID, frameRate);
//
//	//Starting the recording of the camera
//	nRet = isavi_StartAVI(pnAviID);
//
//	//Checking if procedure is working so far or not
//	if (nRet == IS_AVI_NO_ERR)
//	{
//		if (verbose == TRUE)
//		{
//			cout << "Camera Starting recording!" << endl;
//		}
//	}
//	else if (nRet == IS_AVI_ERR_INVALID_FILE) 
//	{
//		if (verbose == TRUE)
//		{
//			cout << "Camera recording failed" << endl;
//			cout << "Terminating program..." << endl;
//		}
//		return 1;
//	}
//	
//	cout << "Camera is recoding live! I will stop when S is pressed" << endl;
//	cout << "Capturing frames" << endl;
//	while (1)
//	{
//		//Captures an image using captureSingle() and adds it as a frame in the avi file
//		captureSingle(hCam, NULL, FALSE, FALSE, TRUE);
//		nRet = isavi_AddFrame(pnAviID, pcImageMemory);
//		//Releases the image memory 
//		nRet = is_FreeImageMem(hCam, pcImageMemory, nMemoryId);
//		
//		//This will be replaced later on when implemented in the raspberry pi
//		if (_kbhit())
//		{
//			//If the User presses enter, the mode will be switched to software trigger mode 
//			int key = _getch();
//			if ((key == 'S'))
//			{
//				break;
//			}
//
//		}
//		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
//		DispatchMessage(&msg);
//	}
//
//	//Closing the file
//	nRet = isavi_StopAVI(pnAviID);
//	nRet = isavi_CloseAVI(pnAviID);
//	nRet = isavi_ExitAVI(pnAviID);
//	if (nRet == IS_AVI_NO_ERR && verbose == TRUE)
//	{
//		cout << "Camera stopped the recording" << endl;
//	}
//	
//	// Disables the hCam camera handle and releases the data structures and memory areas taken up by the uEye camera
//	nRet = is_ExitCamera(hCam);
//	
//	return 0;
//}
//

//Helper method to initialize the camera. If connection is successful it returns the hCam object. Else 
//if it fails, it returns NULL

HIDS initialize(int nRet) {
	// starts the driver and establishes the connection to the camera
	nRet = is_InitCamera(&hCam, NULL);
	if (nRet != IS_SUCCESS)
	{
		if (verbose)
		{
			cout << "ERROR, something is wrong with the USB connection of the camera" << endl;
			cout << "Terminating program..." << endl << endl;
		}
		return NULL;

	}
	else
	{
		cout << "Camera initialisation was successful!" << endl << endl;
		return hCam;
	}
}

BOOL verb()
{
	return verbose;
}

