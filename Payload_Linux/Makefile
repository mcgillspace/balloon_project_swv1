main: cameraLibrary.o main.o 
	@g++ -o main main.o cameraLibrary.o -lueye_api

cameraLibrary.o: cameraLibrary.cpp cameraSettings.h  
		@g++ -c cameraLibrary.cpp -lueye_api

cameraSettings.o: cameraSettings.cpp
		@g++ -c cameraSettings.cpp -lueye_api

