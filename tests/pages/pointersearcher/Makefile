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

# @file Makefile - Builds the Pointer Searcher's test suite.

# Orientation of this Makefile
TESTROOT = ../..
SRCROOT = ../../../src

# Source Directories
INCDIR = .
PAGEINCDIR = $(SRCROOT)/pages/pointersearcher
COMPATINCDIR = $(SRCROOT)/compatibility
INCPATHS = $(INCDIR) $(PAGEINCDIR) $(COMPATINCDIR)
INCFLAGS = $(addprefix -I,$(INCPATHS))

# wxWidgets Options
WXCFLAGS = `wx-config --cxxflags`

# Output Directories
BUILDROOT = $(TESTROOT)/build
OBJDIR = $(BUILDROOT)/obj

# Output Files
OBJ = PointerSearcherTestSuite.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

# Compiler
CXX = g++
CXXTESTFLAGS = -I$$CXXTEST
CFLAGS = -Wall -Wextra -O2 -c -o $@ $(CXXTESTFLAGS) $(WXCFLAGS) $(INCFLAGS)

# Make Utility
MAKE = make

# cxxtestgen
TESTGEN = cxxtestgen
PARTFLAGS = --part

.PHONY: all configure generate clean

all: configure
all: $(OPATHS)
all: clean

configure:
	mkdir -p $(OBJDIR)

generate:
	$(TESTGEN) $(PARTFLAGS) -o PointerSearcherTestSuite.test.cpp \
	                           PointerSearcherTestSuite.h

PointerSearcherTestSuite.test.cpp: generate

$(OBJDIR)/PointerSearcherTestSuite.o: PointerSearcherTestSuite.test.cpp \
                                      $(INCDIR)/PointerSearcherTestSuite.h \
				      $(PAGEINCDIR)/PointerSearcher.h
	$(CXX) $(CFLAGS) PointerSearcherTestSuite.test.cpp

# Clean removes generated files.
GENS = PointerSearcherTestSuite.test.cpp
clean:
	touch $(GENS) && rm $(GENS)

