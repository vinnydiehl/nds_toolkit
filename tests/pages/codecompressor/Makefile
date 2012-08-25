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

# @file Makefile - Builds the Code Compressor's test suites.

# Orientation of this Makefile
TESTROOT = ../..
SRCROOT = ../../../src

# Source Directories
INCDIR = .
PAGEINCDIR = $(SRCROOT)/pages/codecompressor
PARSEINCDIR = $(SRCROOT)/codeparser
COMPATINCDIR = $(SRCROOT)/compatibility
INCPATHS = $(INCDIR) $(PAGEINCDIR) $(PARSEINCDIR) $(COMPATINCDIR)
INCFLAGS = $(addprefix -I,$(INCPATHS))

# wxWidgets Options
WXCFLAGS = `wx-config --cxxflags`

# Output Directories
BUILDROOT = $(TESTROOT)/build
OBJDIR = $(BUILDROOT)/obj

# Output Files
OBJ = LoopCodeGeneratorTestSuite.o PatchCodeBuilderTestSuite.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

# Compiler
CXX = g++
CFLAGS = -Wall -Wextra -O2 -c -o $@ $(WXCFLAGS) $(INCFLAGS)

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
	$(TESTGEN) $(PARTFLAGS) -o LoopCodeGeneratorTestSuite.test.cpp \
	                           LoopCodeGeneratorTestSuite.h
	$(TESTGEN) $(PARTFLAGS) -o PatchCodeBuilderTestSuite.test.cpp \
	                           PatchCodeBuilderTestSuite.h

LoopCodeGeneratorTestSuite.test.cpp: generate
PatchCodeBuilderTestSuite.test.cpp: generate

$(OBJDIR)/LoopCodeGeneratorTestSuite.o: \
    LoopCodeGeneratorTestSuite.test.cpp \
    $(INCDIR)/LoopCodeGeneratorTestSuite.h $(PAGEINCDIR)/LoopCodeGenerator.h
	$(CXX) $(CFLAGS) LoopCodeGeneratorTestSuite.test.cpp

$(OBJDIR)/PatchCodeBuilderTestSuite.o: PatchCodeBuilderTestSuite.test.cpp \
				       $(INCDIR)/PatchCodeBuilderTestSuite.h \
				       $(PAGEINCDIR)/PatchCodeBuilder.h
	$(CXX) $(CFLAGS) PatchCodeBuilderTestSuite.test.cpp

# Clean removes generated files.
GENS = LoopCodeGeneratorTestSuite.test.cpp PatchCodeBuilderTestSuite.test.cpp
clean:
	touch $(GENS) && rm $(GENS)

