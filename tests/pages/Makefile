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

# @file Makefile - Recursively builds all of the page test suites.

# Make Utility
MAKE = make

# Orientation of this Makefile
TESTROOT = ..

# Output Directories
BUILDROOT = $(TESTROOT)/build
OBJDIR = $(BUILDROOT)/obj

# Output Files
OBJ = LoopCodeGeneratorTestSuite.o PointerSearcherTestSuite.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

.PHONY: all configure

all: configure
all: $(OPATHS)

configure:
	mkdir -p $(OBJDIR)

$(OBJDIR)/LoopCodeGeneratorTestSuite.o:
	$(MAKE) -C codecompressor

$(OBJDIR)/PointerSearcherTestSuite.o:
	$(MAKE) -C pointersearcher

