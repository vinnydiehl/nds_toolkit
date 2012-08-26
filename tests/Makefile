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

# @file Makefile - Contains instructions for building the tests.

# Orientation of this Makefile
TESTROOT = .
SRCROOT = ../src

# Output Name
NAME = testrunner

# Output Directories
BUILDROOT = $(TESTROOT)/build
BINDIR = $(BUILDROOT)/bin
OBJDIR = $(BUILDROOT)/obj
SRCOBJDIR = $(BUILDROOT)/srcobj
SRCBUILDOBJDIR = $(SRCROOT)/build/obj
TEMPDIR = $(BUILDROOT)/temp

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
CFLAGS = -Wall -Wextra -O2 -c -o $@

# cxxtestgen
TESTGEN = cxxtestgen
ROOTFLAGS = --root --error-printer

# Make
MAKE = make

.PHONY: all configure run clean delete

all: configure
all: $(EXE)
all: run
all: clean

configure:
	mkdir -p $(OBJDIR) $(SRCOBJDIR) $(TEMPDIR)

$(EXE): $(OPATHS) $(SRCOPATHS)
	$(MAKE) -f linker.mk

# Generate Main Source File
$(TEMPDIR)/main.cpp:
	$(TESTGEN) $(ROOTFLAGS) -o $(TEMPDIR)/main.cpp
$(OBJDIR)/main.o: $(TEMPDIR)/main.cpp
	$(CXX) $(CFLAGS) $(TEMPDIR)/main.cpp

### Test Object Builds

$(OBJDIR)/CodeParserTestSuite.o:
	$(MAKE) -C codeparser

$(OBJDIR)/PointerSearcherTestSuite.o:
	$(MAKE) -C pages
$(OBJDIR)/CodePorterTestSuite.o:
	$(MAKE) -C pages
$(OBJDIR)/LoopCodeGeneratorTestSuite.o:
	$(MAKE) -C pages
$(OBJDIR)/PatchCodeBuilderTestSuite.o:
	$(MAKE) -C pages

### Source Object Builds

$(SRCOBJDIR)/CodeParser.o:
	$(MAKE) -C $(SRCROOT)/codeparser rebuild
	mv $(SRCBUILDOBJDIR)/CodeParser.o $(SRCOBJDIR)

$(SRCOBJDIR)/CodePorter.o:
	$(MAKE) -C $(SRCROOT)/pages/codeporter rebuild
	mv $(SRCBUILDOBJDIR)/CodePorter.o $(SRCOBJDIR)

$(SRCOBJDIR)/LoopCodeGenerator.o:
	$(MAKE) -C $(SRCROOT)/pages/codecompressor rebuild
	mv $(SRCBUILDOBJDIR)/LoopCodeGenerator.o $(SRCOBJDIR)

$(SRCOBJDIR)/PatchCodeBuilder.o:
	$(MAKE) -C $(SRCROOT)/pages/codecompressor rebuild
	mv $(SRCBUILDOBJDIR)/PatchCodeBuilder.o $(SRCOBJDIR)

$(SRCOBJDIR)/PointerSearcher.o:
	$(MAKE) -C $(SRCROOT)/pages/pointersearcher rebuild
	mv $(SRCBUILDOBJDIR)/PointerSearcher.o $(SRCOBJDIR)

$(SRCOBJDIR)/arrstr.o:
	$(MAKE) -C $(SRCROOT)/compatibility rebuild
	mv $(SRCROOT)/compatibility/wx2.9/build/arrstr.o $(SRCOBJDIR)

# Gotta change directories to run the tests, here's the function for that:
CHDIR_SHELL := $(SHELL)
define chdir
   $(eval _D=$(firstword $(1) $(@D)))
   $(info $(MAKE): cd $(_D)) $(eval SHELL = cd $(_D); $(CHDIR_SHELL))
endef

run: clean
	$(call chdir,$(BINDIR))
	clear
	@./$(NAME) $(OPTIONS)

clean:
	mkdir -p $(OBJDIR) $(SRCOBJDIR) $(TEMPDIR)
	rm -r $(OBJDIR) $(SRCOBJDIR) $(TEMPDIR)

erase: delete
delete:
	mkdir -p $(BUILDROOT) && rm -r $(BUILDROOT)

