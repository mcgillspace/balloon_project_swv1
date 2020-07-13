#include "pch.h"
#include <iostream>
#include <sstream>

#include <uEye.h>
#include <uEye_tools.h>
#include <conio.h>
#include <tchar.h>

HIDS hCam = 0;          // 0 for the next available Camera. 1-254 to access a specific camera by ID
HWND hWndDisplay;
ATOM atom;
SENSORINFO sInfo;
BOOL verbose = TRUE;