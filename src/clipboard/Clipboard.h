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
 * @file Clipboard.h - Header file for the Clipboard class.
**/

#pragma once

#ifndef CLIPBOARD_H_INCLUDED
#define CLIPBOARD_H_INLCUDED

#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#include <wx/string.h>

class Clipboard
{
public:
    static void SetClipboard(wxString str);
    static wxString GetClipboard(void);
};

#endif // CLIPBOARD_H_INLCUDED
