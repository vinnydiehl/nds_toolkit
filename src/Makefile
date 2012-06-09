# NDS Hacking Kit - A suite of tools for hacking Nintendo video games.
# Copyright (C) 2012 Vinny Diehl
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

# @file Makefile - Contains instructions for building the application.
#
# make
# Builds application.
#
# make debug
# Builds application with debugging symbols and DEBUG defined.
#
# make rebuild
# Rebuilds the application, including all object files.
#
# make rebuild-dbg
# Rebuilds the application, including all object files, to the debug target.
#
# make clean
# Deletes the object files.
#
# make erase
# make delete
# Deletes the build directory and all files within.

# Root Source Directory
ROOT = .

# Output Name
NAME = NDSHackingKit
ALTNAME = ndshackingkit

# Source Directories
INCDIR = $(ROOT)/include
FRMDIR = $(ROOT)/frames

# wxWidgets Options
WXCFLAGS = `wx-config --cxxflags`
WXLDFLAGS = `wx-config --libs`

# Output Directories
BUILDROOT = $(ROOT)/build
BINDIR = $(BUILDROOT)/bin
OBJDIR = $(BUILDROOT)/obj
INSTALL = /usr/bin

# Output Files
EXE = $(BINDIR)/$(NAME)
OBJ = Program.o frmMain.o MenuBar.o pgButtonActivatorGenerator.o \
      pgCodePorter.o pgPointerSearcher.o pgCodeCompressor.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

# Compiler
CXX = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -c -o $@ $(WXCFLAGS) -I$(INCDIR)
LDFLAGS = -Wall $(WXLDFLAGS) -I$(INCDIR)
MAKE = make
MAKETGT =

.PHONY: all debug configure clean rebuild rebuild-dbg erase delete

all: CFLAGS += -O2
all: LDFLAGS += -O2
all: configure
all: $(EXE)

debug: CFLAGS += $(DEBUG)
debug: LDFLAGS += $(DEBUG)
debug: MAKETGT += debug
debug: configure
debug: $(EXE)

configure:
	mkdir -p $(BINDIR) $(OBJDIR)

$(EXE): $(OPATHS)
	$(CXX) $(OPATHS) $(LDFLAGS) -o $@

### Object Builds

# app

$(OBJDIR)/Program.o:
	$(MAKE) -C app $(MAKETGT)

# frames

$(OBJDIR)/frmMain.o:
	$(MAKE) -C frames $(MAKETGT)

# base

$(OBJDIR)/MenuBar.o:
	$(MAKE) -C base $(MAKETGT)

# pages

$(OBJDIR)/pgButtonActivatorGenerator.o:
	$(MAKE) -C pages $(MAKETGT)

$(OBJDIR)/pgCodeCompressor.o:
	$(MAKE) -C pages $(MAKETGT)

$(OBJDIR)/pgCodePorter.o:
	$(MAKE) -C pages $(MAKETGT)

$(OBJDIR)/pgPointerSearcher.o:
	$(MAKE) -C pages $(MAKETGT)

### End Object Builds

clean:
	mkdir -p $(OBJDIR) && rm -r $(OBJDIR)

rebuild: clean
rebuild: $(EXE)

rebuild-dbg: clean
rebuild-dbg: debug

erase: delete
delete:
	mkdir -p $(BUILDROOT) && rm -r $(BUILDROOT)

install:
	cp $(EXE) $(INSTALL)
	ln -s $(INSTALL)/$(NAME) $(INSTALL)/$(ALTNAME)

