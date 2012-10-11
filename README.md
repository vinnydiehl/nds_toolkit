# NDS Toolkit [![Build Status](https://secure.travis-ci.org/gbchaosmaster/nds-toolkit.png)](http://travis-ci.org/gbchaosmaster/nds-toolkit)

 * [Web Page](http://www.gbchaosmaster.tk/projects/nds_toolkit)
 * [GameHacking Release Thread](http://gamehacking.org/vb/threads/6772-NDS-Toolkit-Cross-Platform)

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
have, I will work to implement that feature in his version as well. See the
[Contributing](#contributing) section below if you're new at this. If you're
familiar with GitHub and know what you're doing, then have at it! The NDS
Toolkit uses the
[git-flow](http://nvie.com/posts/a-successful-git-branching-model/) branching
model.

The code is in the ```src``` directory. If you are a user of this program,
follow the install instructions immediately below to get it installed on your
computer.

## Installation

*Note: See the [Setup](#setup) section below if you don't have a C++ compiler
and wxWidgets installed- if you don't know, you probably need to install one or
both of them.*

The NDS Toolkit can be installed with the conventional
```./configure && make && sudo make install```, ran from the ```src```
directory. Note that the ```./configure``` step is unnecessary if you have not
set up a ```.ndsconfig``` and wish to build with the default settings (see
the [Build Configuration](#build-configuration) section below).

## Build Instructions

### Setup

Running one of these will install all of the needed build tools for this
application, depending on your distro...

Debian:

```Shell
sudo apt-get install build-essential libwxgtk2.8
```

Red Hat:

```Shell
sudo yum groupinstall 'Development Tools'
sudo yum install wxGTK
# OR run them both at once:
sudo yum groupinstall 'Development Tools' && sudo yum install wxGTK
```

Gentoo:

```Shell
su -c 'emerge wxGTK'
```

Arch:

```Shell
su -c 'pacman -S wxgtk'
```

The NDS Toolkit is written in C++ using wxWidgets 2.8.12 (and is known to
build successfully on 2.9.3). If your compiler is having trouble finding the
wxWidgets library and you know that you have it installed, check that there is
output for the following commands:

```Shell
wx-config --cxxflags
wx-config --libs
```

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

```make install``` and ```make uninstall``` will install/uninstall
the NDS Toolkit. These commands will need to be run as root.

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

To apply your selected options to be used next build, run ```./configure```. If
there is no ```.ndsconfig``` or if the file is blank, by default all pages
will be built and included in the application.

## Contributing

All developers are welcome to contribute to the code for NDS Toolkit. All that
I ask is that you follow the coding style of the existing codebase, and keep
line length under 80 characters.

The branching model for the repository is
[git-flow](http://nvie.com/posts/a-successful-git-branching-model/). Check it
out if you haven't heard of it and take a look at
[this](https://github.com/nvie/gitflow)- it gives some handy commands for using
this workflow. To set up the extensions with this project, run
```git flow init``` in the repository after cloning it and keep all of the
defaults.

To get working on the NDS Toolkit:

 1. Fork this project
([click here to fork](https://github.com/gbchaosmaster/nds-toolkit/fork_select))
 2. On your system, where ever you want to put the directory with the code:
    ```git clone git@github.com:<YOUR-GITHUB-USERNAME>/nds-toolkit.git```
 3. Go into your newly cloned directory: ```cd nds-toolkit```
 4. Add the maintainer's repository to your repo:
```git remote add upstream https://github.com/gbchaosmaster/nds-toolkit.git```
 5. Create a feature branch for you to work in:
    ```git checkout -b feature/###-name-of-branch```

    Or, if using the git-flow extensions:
    ```git flow feature start ###-name-of-branch```

    The optional ```###``` is for the issue number, if you have created an
    issue on the issue tracker to correspond with your changes.
 6. Write your code, making regular commits (see [below](#commits) for
    details)
 7. *time passes, maintainer repo is being updated in the mean time*
 8. Switch to the development branch and pull down the latest changes:
```git checkout develop && git fetch upstream && git rebase upstream/develop```
 9. Switch back to your working branch and rebase those changes:
     ```git checkout feature/###-name-of-branch && git rebase develop```
 10. Repeat 6-9 as necessary.
 11. When your code is finished, **make sure the test suite runs**. No pull
     requests with failing tests (or tests modified to work around changes that
     you made, unless you had a good reason to do so that is mentioned in your
     commit/pull request) will be accepted. See the
     [test documentation](develop/tests#readme) for more information.
 12. Push the code to your forked repository:
     ```git push origin feature/###-name-of-branch```
 13. Send a pull request to the maintainer- make sure that the ```develop```
     branch is selected for your request to be pulled into.

### Commits

To add changes to the staging area (the list of changes that will be
committed), use ```git add <file or directory>``` to add a file or directory
and all of the changes within. ```git add .``` will add all of the changes from
the current directory on down. Use ```git status``` to view the staged changes,
and ```git commit``` when you're ready to type your message.

All commits should focus one one solid unit of change, and each should have a
good message describing the commit. It should follow the following format:

```
A short description, 50 characters or less

Note the lack of punctuation at the end of the short description.
Anyway, this part, separated from the short description by a blank
line, should be written in normal prose and wrapped at 72 characters.

 * You can include bulleted lists.
 * Just use asterisks, like this.

 1. Numbered lists are also possible.
 2. Just indent these lists with one space. If it gets lengthy and you
    need to wrap the line, keep it neatly indented like so.

If you want to include a code sample, indent it with 4 spaces like so:

    #include <stdio.h>
    int main(void)
    {
        printf("Hello World!\n");
        return 0;
    }
```
