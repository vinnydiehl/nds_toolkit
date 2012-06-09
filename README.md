# NDS Hacking Kit

Welcome to the development branch of the NDS Hacking Kit!

The code is in the ```src``` directory. Check ```CHANGELOG.md``` for the latest development status and hack away.

## Build Instructions

Running one of these will install all of the needed build tools for this application, depending on your distro:

    sudo apt-get install build-essential libwxgtk2.8-dev

[](/blank)

    sudo yum install gcc gcc-c++ wxGTK

If you're using Pacman/Portage/whatever, you know enough to be able to find G++ and wxWidgets on your own.

The NDS Hacking Kit is written in C++ using wxWidgets 2.8.12. If your compiler is having trouble finding the wxWidgets library and you know that you have it installed, check that there is output for the following commands:

    wx-config --cxxflags
    wx-config --libs

Run ```make``` to build the program, or ```make rebuild``` to completely rebuild the program and all object files.

```make clean``` will delete all object files while leaving the application intact, and ```make delete``` or ```make erase``` will completely delete all build artifacts, including the compiled application.

