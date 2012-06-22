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
 * @file CodeParser.cpp - Class with static methods for code verification.
 *
 * See #1 on the issue tracker.
**/

#include "CodeParser.h"

/** Public Methods **/

wxString CodeParser::Beautify(wxString code)
{
    return _T("");
}

bool CodeParser::Verify(wxString code)
{
    return true;
}

/** Private Methods **/

wxString CodeParser::mStripChar(wxString str, wxChar ch)
{
    /**
     * Remove all of a certain character out of a string.
     *
     * @param str - The string to be processed.
     * @param ch - The character to be removed. Defaults to ' '.
    **/

    wxString output;

    for (size_t i = 0; i < str.Len(); ++i)
        if (str[i] != ch)
            output += str[i];

    return output;
}

