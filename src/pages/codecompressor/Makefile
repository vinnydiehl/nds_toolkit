# NDS Toolkit - A suite of tools for hacking Nintendo video games.
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

# @file Makefile - Builds the Code Compressor page.

# Orientation of this Makefile
ROOT = ../..

# Source Directories
INCDIR = .
CLIPINCDIR = $(ROOT)/clipboard
COMMONINCDIR = $(ROOT)/common
COMPATINCDIR = $(ROOT)/compatibility
PARSEINCDIR = $(ROOT)/codeparser
INCPATHS = $(INCDIR) $(CLIPINCDIR) $(COMMONINCDIR) $(COMPATINCDIR) \
	   $(PARSEINCDIR)
INCFLAGS = $(addprefix -I,$(INCPATHS))

# wxWidgets Options
WXCFLAGS = `wx-config --cxxflags`

# Output Directories
BUILDROOT = $(ROOT)/build
OBJDIR = $(BUILDROOT)/obj

# Output Files
OBJ = pgCodeCompressor.o LoopCodeGenerator.o PatchCodeBuilder.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

# Compiler
CXX = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -Wextra -c -o $@ $(WXCFLAGS) $(INCFLAGS)

.PHONY: all debug configure clean rebuild rebuild-dbg

all: CFLAGS += -O3
all: configure
all: $(OPATHS)

debug: CFLAGS += $(DEBUG)
debug: configure
debug: $(OPATHS)

configure:
	@mkdir -p $(OBJDIR)

$(OBJDIR)/pgCodeCompressor.o: $(INCDIR)/pgCodeCompressor.h \
			      $(INCDIR)/LoopCodeGenerator.h \
    			      $(INCDIR)/PatchCodeBuilder.h \
     			      $(CLIPINCDIR)/Clipboard.h \
			      $(COMMONINCDIR)/globals.h \
			      $(PARSEINCDIR)/CodeParser.h
	$(CXX) $(CFLAGS) pgCodeCompressor.cpp

$(OBJDIR)/LoopCodeGenerator.o: $(INCDIR)/LoopCodeGenerator.h
	$(CXX) $(CFLAGS) LoopCodeGenerator.cpp

$(OBJDIR)/PatchCodeBuilder.o: $(INCDIR)/PatchCodeBuilder.h \
	              $(COMPATINCDIR)/wx2.9/arrstr.h
	$(CXX) $(CFLAGS) PatchCodeBuilder.cpp

clean: configure
	touch $(OPATHS) && rm $(OPATHS)

rebuild: clean
rebuild: all

rebuild-dbg: clean
rebuild-dbg: debug
