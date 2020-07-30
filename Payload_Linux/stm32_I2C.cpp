#include <iostream>
#include <thread>
#include <chrono>
#include <wiringPiI2C.h>

// define the address of the device
#define DEVICE_ID 0x53

// define the registers
#define REG_POWER_CTL   0x2D
#define REG_DATA_X_LOW  0x32
#define REG_DATA_X_HIGH 0x33
#define REG_DATA_Y_LOW  0x34
#define REG_DATA_Y_HIGH 0x35
#define REG_DATA_Z_LOW  0x36
#define REG_DATA_Z_HIGH 0x37

int main (int argc, char *argv[]){
	// setting up the I2C communication
	int fd = wiringPiI2CSetup(DEVICE_ID);
	
	// if the set up does not work, give message
	if fd == (-1){
		std::cout << "Failed to init I2C communication. \n";
		return -1;
	}
	std::cout << "I2C communication successful. \n";
	std::cout << "Init result: " << fd << endl;

	// writing to a register
	// the 4th bit of an 8 bit register
	int result = wiringPiI2CWriteReg8(fd, REG_POWER_CTL, 0b00001000);

	// if that did not work
	if (result == -1){
		cout << "Error with writing to register.";
	}
	
	return 0;

}
