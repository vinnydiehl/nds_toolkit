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

# @file Makefile - Builds the application's frames.

# Orientation of this Makefile
ROOT = ..

# Source Directories
INCDIR = .
BASEINCDIR = $(ROOT)/base
CLIPINCDIR = $(ROOT)/clipboard
COMPATINCDIR = $(ROOT)/compatibility
FHINCDIR = $(ROOT)/filehandler
PAGESINCDIR = $(ROOT)/pages/buttonactivatorgenerator \
	      $(ROOT)/pages/codecompressor \
	      $(ROOT)/pages/codeporter \
	      $(ROOT)/pages/pointersearcher
PARSEINCDIR = $(ROOT)/codeparser
SHAREDINCDIR = $(ROOT)/shared
INCPATHS = $(INCDIR) $(BASEINCDIR) $(CLIPINCDIR) $(COMPATINCDIR) \
	   $(FHINCDIR) $(PAGESINCDIR) $(PARSEINCDIR) $(SHAREDINCDIR)
INCFLAGS = $(addprefix -I,$(INCPATHS))

PAGESINCLDS = \
  $(ROOT)/pages/buttonactivatorgenerator/pgButtonActivatorGenerator.h \
  $(ROOT)/pages/codeporter/pgCodePorter.h \
  $(ROOT)/pages/pointersearcher/pgPointerSearcher.h \
  $(ROOT)/pages/codecompressor/pgCodeCompressor.h

# wxWidgets Options
WXCFLAGS = `wx-config --cxxflags`

# Output Directories
BUILDROOT = $(ROOT)/build
OBJDIR = $(BUILDROOT)/obj

# Output Files
OBJ = frmMain.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

# Compiler
CXX = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -c -o $@ $(WXCFLAGS) $(INCFLAGS)

.PHONY: all debug configure clean rebuild rebuild-dbg

all: CFLAGS += -O2
all: configure
all: $(OPATHS)

debug: CFLAGS += $(DEBUG)
debug: configure
debug: $(OPATHS)

configure:
	mkdir -p $(OBJDIR)

$(OBJDIR)/frmMain.o: $(INCDIR)/frmMain.h $(BASEINCDIR)/MenuBar.h \
                     $(PAGESINCLDS) $(SHAREDINCDIR)/config.h \
		     $(SHAREDINCDIR)/globals.h
	$(CXX) $(CFLAGS) frmMain.cpp

clean: configure
	touch $(OPATHS) && rm $(OPATHS)

rebuild: clean
rebuild: all

rebuild-dbg: clean
rebuild-dbg: debug

