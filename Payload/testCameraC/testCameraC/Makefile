main: cameraLibrary.o pch.o main.o
	@g++ -o main main.o cameraLibrary.o pch.o
	# "pch.h" is only for Visual Studio

cameraLibrary.o: cameraLibrary.cpp cameraSettings.h pch.h 
		@g++ -c cameraLibrary.cpp

cameraSettings.o: cameraSettings.cpp pch.h
		@g++ -c cameraSettings.cpp

