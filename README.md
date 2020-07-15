
# High Altitude Balloon Project: Mission Anseris

Welcome to the software collection for our HAB! 

<p align="left">
  <img width="250" height="250" src="https://github.com/mcgillspace/balloon_project_swv1/blob/master/Anseris_1_logo.png">
</p>



----- **ABOUT FILES** -----

*camera_sw_structure* contains a preliminary skeleton of the software for the on board camera. We are using the IDS UI-3241LE-M-GL. More details about the camera can be found [here.](https://en.ids-imaging.com/download-details/AB00430.html) We are also using a Raspberry Pi.

All of the files found in *Payload/testCameraC/testCameraC/* pertain to the the function of the IDS camera.

*main.cpp* is where the code is run. First, the path name is set and we initialize the camera. If unsuccessful, it terminates. Next, the trigger mode is set, and then the capture mode is chosen. This feature allows for the camera to take one single photo, a burst of photos, or a video.

*cameraLibrary.cpp* contains the bulk of the code necessary to perform the tasks we want. The following is an outline of the functions used in this file:
* *captureSingle()* takes in the camera object and the folder name, where an image will be saved. It also has optional arguments for displaying and saving an image after taking a picture.  
* *captureBurst()* takes in the same inputs as the previous function, as well as the number of photos in the burst.
* *captureVideo()* takes in the camera object, the folder name and the frame rate. This is will take a video for a hardcoded time for now and will save the video in the specified folder name in an AVI format. 

*cameraLibrary.h* is a header file that includes the functions used in *cameraLibrary.cpp*. 

*cameraSettings.h* is where the camera ID is set, as well as other various attributes. This file also contains many useful libraries.

*testCameraC.sln* is the solution file made by Microsoft Visual Studio.

*Makefile* will run the files for us when ready.

The files found in *Payload_Linux* are used for the Raspberry Pi.

----- **CONTACT INFORMATION** -----

If you have questions regarding this project, feel free to reach out [on our website.](https://www.mcgillspace.com/#!/contact)


