#include <iostream>
#include <sstream>

#include <ueye.h>
#include <curses.h>

HIDS hCam = 0;          // 0 for the next available Camera. 1-254 to access a specific camera by ID
SENSORINFO sInfo;
BOOL verbose = TRUE;
INT HEIGHT = 1280
INT WIDTH = 960
INT NBITS = 8           //8 bit monochrome (color depth)
