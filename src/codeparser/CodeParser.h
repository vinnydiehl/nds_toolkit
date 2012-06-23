/**
 * NDS Hacking Kit - A suite of tools for hacking Nintendo video games.
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

#include <wx/string.h>

#include "wxcArrayString.h"

class CodeParser
{
public:
    static wxString Beautify(wxString code,
                             bool upperHex=true,
                             bool stripComments=false,
                             bool stripEmpty=true);
    static bool Verify(wxString code);

private:
    static wxString mStripChar(wxString str, wxString ch);
};

#endif // CODEPARSER_H_INLCUDED

