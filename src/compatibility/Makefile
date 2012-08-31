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

# @file Makefile - Builds all compatibility libraries.

# Make Utility
MAKE = make
MAKETGT =

# Orientation of this Makefile
ROOT = ..

# Libraries
WX29 = wx2.9
WX29LIB = $(WX29)/lib

# Output Directories
WX29BUILD = $(WX29)/build

# Output Files
OPATHS = $(WX29BUILD)/arrstr.o

.PHONY: all debug configure clean rebuild rebuild-dbg

all: CFLAGS += -O3
all: $(OPATHS)

debug: CFLAGS += $(DEBUG)
debug: MAKETGT += debug
debug: $(OPATHS)

configure:
	@mkdir -p $(WX29BUILD)

$(WX29BUILD)/arrstr.o:
	$(MAKE) -C $(WX29LIB) $(MAKETGT)

clean: configure
	touch $(OPATHS) && rm $(OPATHS)

rebuild: clean
rebuild: all

rebuild-dbg: clean
rebuild-dbg: debug

