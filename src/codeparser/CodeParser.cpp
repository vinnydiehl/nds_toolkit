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

wxString CodeParser::Beautify(wxString code, bool stripComments)
{
    return _T("");
}

bool CodeParser::Verify(wxString code)
{
    /**
     * Return true if the input is valid as NDS code, otherwise return false.
    **/

    /** Preprocessing **/

    // Strip away stuff that we don't need; Comments, blanks, extra whitespace.
    wxArrayString raw = wxcArrayString::wxSplit(code, _T('\n'));
    wxArrayString lines;
    for (size_t i = 0; i < raw.GetCount(); ++i)
    {
        // Trim the current line so whitespace doesn't throw us off
        wxString line = raw[i].Trim().Trim(false);

        if (!line.IsEmpty() && line[0] != _T(':'))
            lines.Add(line);
    }

    // Strip the rest of the whitespace.
    // Yes, I know, I join with newlines and then strip the newlines. I just
    // want to ensure that the code is returned to its previous state before
    // all of the whitespace is removed.
    code = mStripChar(wxcArrayString::wxJoin(lines, _T('\n')), _T(" \t\n\r"));

    /** Verification **/

    // If we don't even have the right amount of digits, bail.
    if (code.Len() % 16 != 0)
        return false;

    // Make sure all characters are valid hexadecimal.
    wxString hex = _T("0123456789ABCDEFabcdef");
    for (size_t i = 0; i < code.Len(); ++i)
    {
        // Guilty until proven innocent
        bool ishex = false;

        for (size_t j = 0; j < hex.Len(); ++j)
            if (code[i] == hex[j])
                ishex = true;

        if (!ishex)
            return false;
    }

    // We're good!
    return true;
}

/** Private Methods **/

wxString CodeParser::mStripChar(wxString str, wxString ch)
{
    /**
     * Remove all of a certain character/characters out of a string.
     *
     * @param str - The string to be processed.
     * @param ch - The character(s) to be removed.
    **/

    wxString output;

    // Loop over the characters in str.
    for (size_t i = 0; i < str.Len(); ++i)
    {
        bool isallowed = true;

        // Check if any of the characters in ch match the current character.
        // If any of them do, the character will be stripped.
        for (size_t j = 0; j < ch.Len(); ++j)
            if (str[i] == str[j])
                isallowed = false;

        // If it wasn't stripped, add it to the output.
        if (isallowed)
            output += str[i];
    }

    return output;
}

