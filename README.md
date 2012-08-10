# NDS Toolkit

This version of the NDS Toolkit is a port of Demonic722's C#.NET tool. The
original is located at:

 * [Release thread on GameHacking](http://gamehacking.org/vb/threads/6610-NDS-Hacking-Kit)
 * [GitHub repository](https://github.com/Demonic722/NDS-Toolkit)

I love this tool, but unfortunately, .NET is a nasty dependency that isn't
supported on... well, any operating system that isn't Windows. I made this
cross-platform port primarily for Linux/Mac users that wanted to use the tool,
and C++ hackers that wanted to improve the tool.

If you want to help develop on this code, feel free! If any contributions are
made to this tool that give it features that Demonic722's version does not
have, I will work to implement that feature in his version as well.

The code is in the ```src``` directory. If you are a user of this program,
follow the build instructions below to get it installed on your computer. If
you would like to develop, well, here's the code! I only ask that you style
your code to look consistent with the other code in this project, and do not
ask for your code to be pulled into the central, trunk, or release branches.

## Build Instructions

### Setup

Running one of these will install all of the needed build tools for this
application, depending on your distro:

    sudo apt-get install build-essential libwxgtk2.8

[](/blank)

    sudo yum groupinstall 'Development Tools'
    sudo yum install wxGTK

If you're using Pacman/Portage/whatever, you know enough to be able to find GCC
and wxWidgets on your own.

The NDS Toolkit is written in C++ using wxWidgets 2.8.12 (and is known to
build successfully on 2.9.3). If your compiler is having trouble finding the
wxWidgets library and you know that you have it installed, check that there is
output for the following commands:

    wx-config --cxxflags
    wx-config --libs

### Full Build

Run ```make``` to fully build the program, or ```make rebuild``` to completely
rebuild the program and all object files.

Other options:

```make debug``` fully builds the program with debugging symbols and options,
and disables optimization.

```make rebuild-dbg``` rebuilds the program in the debug configuration.

```make clean``` deletes all object files while leaving the application intact.

```make delete``` or ```make erase``` will completely delete all build
artifacts, including the compiled application.

```make distclean``` will reset the build configuration to default, but retains
your ```.ndsconfig``` if you have one.

```make run``` will run the already built executable. You can also use the
commands ```make build-run```, ```make debug-run```, ```make rebuild-run```,
and ```make rebuild-dbg-run```; they will work as you expect them to.

### Incremental Builds

Running ```make -f linker.mk``` at the top of the source tree will build only
the executable. There is a Makefile in each of the subdirectories as well;
running ```make``` in those subdirectories will build only the object files in
that directory (and recurse into their own subdirectories, if applicable). All
of the targets of the main Makefile (except for ```delete```, ```erase```, and
```distclean```) are available to these Makefiles as well.

### Build Configuration

To customize your build, create a file named ```.ndsconfig``` to hold your
build options. List the build options in this file, line by line. Lines that
are not valid build options will be ignored, but begin comments with # for the
sake of consistency. The current build options allow you to choose which
pages are to be compiled:

```
add_options --add-button-activator-generator
add_options --add-pointer-searcher
add_options --add-code-porter
add_options --add-code-compressor
add_options --add-code-beautifier
```

As of now, the only way to use the Code Beautifier page is to enable it as a
build option. The page is disabled in the default configuration.

To apply your selected options to be used next build, run ```./configure```. If
there is no ```.ndsconfig``` or if the file is blank, by default all pages
will be built and included in the application.

