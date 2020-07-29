#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
	// defining address of raspberry pi
	int addr = 0x8;

	// finding the bus on the raspberry pi
	int file;
	char *filename = "/dev/i2c-1";
	if ((file = open(filename, O_RDWR)) < 0) {
		perror("Failed to open I2C bus");
		exit(1);
	}
	char buf[10] = {0};
	buf[0] = addr;
	if (write(file, buf, 1) != 1){
		// if it fails, give message
		printf("Failed to write to the I2C bus. \n");
		printf("\n\n");
	}
}

