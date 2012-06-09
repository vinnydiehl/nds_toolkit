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

# @file Makefile - Recursively builds all of the application's pages.

# Make Utility
MAKE = make
MAKETGT =

# Orientation of this Makefile
ROOT = ..

# Output Directories
BUILDROOT = $(ROOT)/build
OBJDIR = $(BUILDROOT)/obj

# Output Files
OBJ = pgButtonActivatorGenerator.o pgCodePorter.o \
      pgPointerSearcher.o pgCodeCompressor.o
OPATHS = $(addprefix $(OBJDIR)/,$(OBJ))

.PHONY: all debug configure clean rebuild rebuild-dbg

all: CFLAGS += -O2
all: configure
all: $(OPATHS)

debug: CFLAGS += $(DEBUG)
debug: MAKETGT += debug
debug: configure
debug: $(OPATHS)

configure:
	mkdir -p $(OBJDIR)

$(OBJDIR)/pgButtonActivatorGenerator.o:
	$(MAKE) -C activator-generator $(MAKETGT)

$(OBJDIR)/pgCodePorter.o:
	$(MAKE) -C code-porter $(MAKETGT)

$(OBJDIR)/pgPointerSearcher.o:
	$(MAKE) -C pointer-searcher $(MAKETGT)

$(OBJDIR)/pgCodeCompressor.o:
	$(MAKE) -C code-compressor $(MAKETGT)

clean: configure
	touch $(OPATHS) && rm $(OPATHS)

rebuild: clean
rebuild: all

rebuild-dbg: clean
rebuild-dbg: debug

