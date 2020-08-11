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
	char *device = I2C_DEFAULT;
	i2c_stm_init_params_t params = { I2C_MODE, I2C_BITS, I2C_MAX_HZ};
	
	int result;
	int i,j;
	i2c_stm_block_t block;
	i2c_stm_packet_t packet;
	
	size_t size, mod;
	size_t k, blocks;
	uint16_t blocks_data;
	uint8_t resp;
	unsigned char *blob;
	

	//Initializing I2C 
	fd = spi_init(device, &params);
	if (fd ==-1){
		return -1;
	}
	

	//Writing each tile to I2C
	for (i=0; i <IMAGE_DIVS; i++){
		for (j=0; j<IMAGE_DIVS;j++){
			blob = image_get_blob(wands[i][j], &size);
			if (blob == NULL)
				return -1;
			mod = size % STM_BLOCK_SIZE;
			block.tile = (uint8_t) (j+ i*IMAGE_DIVS);
			blocks = ((size-1)/STM_BLOCK_SIZE)+1;
			for (k=0; k <=blocks;k++){
				block.index = (uint16_t) k;
				switch (k) {
				case 0:
					blocks_data = htons((uint16_t) blocks);
					block.data= (uint8_t *) &blocks_data;
					block.data_size = sizeof(blocks_data);
					break;
				case 1:
					block.data = blob;
				default:
					if (k==blocks && mod)
						block.data_size = mod;
					else 
						block.data_size = STM_BLOCK_SIZE;
					break;
				}
				do {
					usleep(STM_BLOCK_USLEEP);
					packet = i2c_stm_packet(&block);
					if (i2c_transfer(fd, packet.buf, (uint32_t) packet.size) == -1)
						return -1;
					resp = packet.buf[0];
					free(packet.buf);
				} while (resp != STM_BLOCK_ACK);
					block.data += STM_BLOCK_SIZE;
			}
		 	MagickRelinquishMemory(blob);
		}
	}
	close(fd);
	return 0;
}

}
