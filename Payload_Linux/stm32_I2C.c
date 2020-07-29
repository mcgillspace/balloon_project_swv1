#include <stdio.h>
#include <stdlib.h>
#include <glib/gprintf.h>
#include <errno.h>
#include <string.h>
#include <i2c/smbus.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

// defining address of raspberry pi
int addr = 0x8;

// finding the bus on the raspberry pi
int file;
char *filename = "/dev/i2c-1";
if ((file = open(filename, O_RDWR)) < 0) {
	perror("Failed to open I2C bus");
	exit(1);
}

buf[0] = addr;
if (write(file, buf, 1) != 1){
	// if it fails, give message
	printf("Failed to write to the I2C bus. \n");
	buffer = g_strerror(errno);
	printf(buffer);
	printf("\n\n");
}

