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
 * @file CodePorter.cpp - pgCodePorter's main algorithm.
**/

#include "CodePorter.h"

wxString CodePorter::Port(wxString code, wxString offset, bool dec)
{
    /**
     * The main interface to the code porting algorithm. This will run the
     * algorithm without disturbing any comments in the code.
     *
     * @param code - The code to be ported.
     * @param offset - The value to be inc/decremented to/from the offset.
     * @param dec - false if incrementing, true if decrementing.
     *              Default: false
    **/

    if (!CodeParser::Verify(code))
        throw wxString(_T("Invalid code input."));

    wxArrayString portedTokens;

    wxArrayString tokens = CodeParser::Tokenize(code);
    for (size_t i = 0; i < tokens.GetCount(); ++i)
        portedTokens.Add(
            // Is the token a comment?
            tokens[i][0] == _T(':')
            // If so, deposit it directly.
            ? tokens[i]
            // If it's code, process then deposit.
            : mPurePort(tokens[i], offset, dec)
        );

    return wxJoin(portedTokens, _T('\n'));
}

wxString CodePorter::mPurePort(wxString code, wxString offset, bool dec)
{
    /**
     * The algorithm for the code porter.
     *
     * @param code - The code to be ported.
     * @param offset - The value to be inc/decremented to/from the offset.
     * @param dec - false if incrementing, true if decrementing.
     * Default: false
    **/

    // Convert that offset wxString to a hex number
    long hexOffset;
    offset.ToLong(&hexOffset, 16);

    // Split into columns
    wxArrayString left, right;
    CodeParser::SplitColumns(code, &left, &right);

    for (size_t i = 0; i < left.GetCount(); ++i)
    {
        // Convert the current offset to hex
        long hexCurrent;
        left[i].ToLong(&hexCurrent, 16);

        // Port the current offset and format it back into a wxString
        wxString ported = wxString::Format(
            _T("%X"),
            // dec dictates what operator we use...
            !dec ? hexCurrent + hexOffset : hexCurrent - hexOffset
        );

        // Now pad to 8 zeros and set it back to its column.
        // 2012-07-04 gbchaosmaster - Fixed segfault while padding
        // :TODO: 2012-07-04 gbchaosmaster - Find a better way to pad
        // For some reason when I tried to pad to 8 zeros here when there
        // was already 8 characters caused a segfault. This fix solves the
        // problem, look into a possible better way to do this.
        left[i] = ported.Len() < 8
                  ? ported.Pad(8 - ported.Len(), _T('0'), false)
                  : ported;
    }

    return CodeParser::JoinColumns(left, right);
}

