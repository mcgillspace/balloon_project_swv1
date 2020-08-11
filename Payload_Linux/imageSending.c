#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <wand/MagicWand.h>
#include "imageProcessing.h"
#include "IDS_Code/cameraSettings.h"

static int init();

static int init(){
	config_t params;
	params.width=WIDTH;
	params.height=HEIGHT;
	params.format="JPG";
	params.depth=NBITS;
}


//Tiles an image (from filename)
static MagickWand ***tile_file_image(const config_t *config, const char *filename){
	//Initialize the wands
	MagickWand *wand;
	MagickWand ***wands;
	
	//Start the handle
	image_init();
	
	//Reads the file into the wand
	wand = image_read_file(&params, filename);
	wands = image_tiles(wand, IMAGE_DIVS);

	return wands;
}

//Transfers the tiles through I2C using the utils.c methods (in progress)
static int transfer_tiles(MagickWand **wands, const config_t *config){



}
