all: stm32_I2C main

stm32_I2C: stm32_I2C.cpp 
	@g++ -o stm32_I2C stm32_I2C.cpp -lwiringPi 


main: cameraLibrary.o main.o 
	@g++ -o main main.o cameraLibrary.o -lueye_api

cameraLibrary.o: cameraLibrary.cpp cameraSettings.h  
		@g++ -c cameraLibrary.cpp -lueye_api

cameraSettings.o: cameraSettings.cpp
		@g++ -c cameraSettings.cpp -lueye_api

