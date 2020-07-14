
# High Altitude Balloon Project: Mission Anseris

Welcome to the software collection for our HAB! 

----- **ABOUT FILES** -----

*camera_sw_structure* contains a preliminary skeleton of the software for the on board camera. We are using the IDS UI-3241LE-M-GL. More details about the camera can be found [here.](https://en.ids-imaging.com/download-details/AB00430.html)

All of the files found in *Payload/testCameraC/testCameraC/* pertain to the the function of the IDS camera.

*main.cpp* is where the code is run. First, the path name is set and we initialize the camera. If unsuccessful, it terminates. Next, the trigger mode is set, and then the capture mode is chosen. This feature allows for the camera to take one single photo, a burst of photos, or a video.

*cameraLibrary.cpp* contains the bulk of the code necessary to perform the tasks we want. The following is an outline of the functions used in this file:
* *captureSingle()* takes in the camera ID and the file name. 
* *captureBurst()* takes in the same inputs as the previous function, as well as the number of photos in the burst.
* *captureVideo()* 

*cameraLibrary.h* is a header file that includes the functions used in *cameraLibrary.cpp*. 

*cameraSettings.h* is where the camera ID is set, as well as other various attributes. This file also contains many useful libraries.

*testCameraC.sln* is the solution file made by Microsoft Visual Studio.


----- **CONTACT INFORMATION** -----

If you have questions regarding this project, feel free to reach out [on our website.](https://www.mcgillspace.com/#!/contact)


