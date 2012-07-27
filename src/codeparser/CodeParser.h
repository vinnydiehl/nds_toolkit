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
 * @file CodeParser.h - Header file for the CodeParser class.
**/

#pragma once

#ifndef CODEPARSER_H_INCLUDED
#define CODEPARSER_H_INLCUDED

#include <wx/regex.h>
#include <wx/string.h>

#include "wx2.9/arrstr.h"

const wxRegEx HEX(_T("\\A[0-9a-fA-F]+\\Z"), wxRE_ADVANCED);

// Flags for Beautify()
enum
{
    UPPER_HEX = 0x2,
    STRIP_BLANK_LINES = 0x4,
    STRIP_COMMENTS = 0x8,
    BEAUTIFY_DEFAULT = UPPER_HEX | STRIP_BLANK_LINES
};

class CodeParser
{
public:
    static wxString Beautify(wxString code, int flags=BEAUTIFY_DEFAULT);

    static bool Verify(wxString code);
    static bool IsHex(wxString str);

    static wxArrayString LeftColumn(wxString code);
    static wxArrayString RightColumn(wxString code);
    static void SplitColumns(wxString code, wxArrayString *left,
                             wxArrayString *right);
    static wxString JoinColumns(wxArrayString left, wxArrayString right);

private:
    static wxString mStripChar(wxString str, wxString ch);
};

#endif // CODEPARSER_H_INLCUDED

