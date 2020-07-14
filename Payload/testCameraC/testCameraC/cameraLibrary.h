#include "pch.h"
#include <iostream>
#include <sstream>

#include <uEye.h>
#include <uEye_tools.h>
#include <conio.h>
#include <tchar.h>

HIDS initialize(int nRet);
int captureSingle(HIDS hCam, const char *foldername);
int captureBurst(HIDS hCam, const char *foldername, int BurstSize);
int captureVideo(HIDS hCam, wchar_t* filename);
BOOL verb();


