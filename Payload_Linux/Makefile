all: stm32_I2C main

stm32_I2C: stm32_I2C.cpp
	@g++ -o stm32_I2C stm32_I2C.cpp -lwiringPi


main: IDS_Code/cameraLibrary.o IDS_Code/main.o
	@g++ -o main IDS_Code/main.o IDS_Code/cameraLibrary.o -lueye_api

cameraLibrary.o: IDS_Code/cameraLibrary.cpp cameraSettings.h
		@g++ -c IDS_Code/cameraLibrary.cpp -lueye_api

cameraSettings.o: IDS_Code/cameraSettings.cpp
		@g++ -c IDS_Code/cameraSettings.cpp -lueye_api

