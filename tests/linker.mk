# -*- makefile -*-
# vim:set ts=8 sw=8 noet:

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

# @file linker.mk - Builds the executable for the tests.

# Orientation of this Makefile
TESTROOT = .
SRCROOT = ../src

# Output Name
NAME = testrunner

# wxWidgets Options
WXLDFLAGS = `wx-config --libs core`

# Output Directories
BUILDROOT = $(TESTROOT)/build
BINDIR = $(BUILDROOT)/bin
OBJDIR = $(BUILDROOT)/obj
SRCOBJDIR = $(BUILDROOT)/srcobj

# Output Files
EXE = $(BINDIR)/$(NAME)
OBJ = CodeParserTestSuite.o CodePorterTestSuite.o \
      LoopCodeGeneratorTestSuite.o PatchCodeBuilderTestSuite.o \
      PointerSearcherTestSuite.o main.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))
SRCOBJ = CodeParser.o CodePorter.o LoopCodeGenerator.o PatchCodeBuilder.o \
	 PointerSearcher.o arrstr.o
SRCOPATHS = $(addprefix $(SRCOBJDIR)/,$(SRCOBJ))

# Compiler
CXX = g++
LDFLAGS = -Wall -Wextra -O2 $(WXLDFLAGS)

.PHONY: all configure

all: configure
all: $(EXE)

configure:
	mkdir -p $(BINDIR)

$(EXE): $(OPATHS)
	$(CXX) $(OPATHS) $(SRCOPATHS) $(LDFLAGS) -o $@
