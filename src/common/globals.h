/**
 * NDS Toolkit - A suite of tools for hacking Nintendo video games.
 * Copyright (C) 2012 Vinny Diehl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

/**
 * @file globals.h - Constants and macros that are meant to be used in various
 *                   multiple files throughout the program.
**/

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <wx/string.h>

/** About NDS Toolkit **/

// Program name:
const wxString NAME = _T("NDS Toolkit");
// Current program version:
const wxString VERSION = _T("0.6");
// Description:
const wxString DESCRIPTION = _T("\
A suite of tools for hacking Nintendo games.\n\
A cross-platform port of the original NDS Toolkit by Demonic722.\
");
// Copyright:
const wxString COPYRIGHT = _T("\
Original application by Demonic722.\n\
This port is copyright (c) 2012 Vinny Diehl.\
");

// Usrcheat Download Info
const wxString USRCHEAT_URL =
    _T("http://syntechx.com/downloads/usrcheat.rar");
const wxString USRCHEAT_FILE_NAME = _T("usrcheat.rar");

// The margin between the edge of each page and the contents of the page:
const int MARGIN = 5;

#endif // GLOBALS_H_INCLUDED
