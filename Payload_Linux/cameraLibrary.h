#include <iostream>
#include <sstream>

#include "uEye.h"
#include "uEye_tools.h"
#include <curses.h>

HIDS initialize(int nRet);
int captureSingle(HIDS hCam, const char *foldername=NULL, bool saveMode = TRUE, bool displayMode=TRUE,bool videoMode=FALSE);
int captureBurst(HIDS hCam, const char *foldername, int BurstSize);
int captureVideo(HIDS hCam, const char *foldername,double frameRate);
BOOL verb();


