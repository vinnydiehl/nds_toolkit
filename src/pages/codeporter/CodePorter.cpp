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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

/**
 * @file CodePorter.cpp - pgCodePorter's main algorithm.
**/

#include "CodePorter.h"

wxString CodePorter::Port(wxString code, wxString offset, PorterMode mode)
{
    /**
     * The main interface to the code porting algorithm. This will run the
     * algorithm without disturbing any comments in the code.
     *
     * @param code - The code to be ported.
     * @param offset - The value to be inc/decremented to/from the offset.
     * @param mode - Add if incrementing, Sub if decrementing.
    **/

    if (!CodeParser::Verify(code))
        throw wxString(_T("Invalid code input."));

    wxArrayString ported;

    wxArrayString lines = wxc::wxSplit(code, _T('\n'));

    for (size_t i = 0; i < lines.GetCount(); ++i)
        ported.Add(
            // Is the token a comment?
            lines[i][0] == _T(':') || lines[i].IsEmpty()
            // If so, deposit it directly.
            ? lines[i]
            // If it's lines, process then deposit.
            : mPurePort(lines[i], offset, mode)
        );

    return wxc::wxJoin(ported, _T('\n'));
}

wxString CodePorter::mPurePort(wxString code, wxString offset, PorterMode mode)
{
    /**
     * The algorithm for the code porter; ports one line of code.
     *
     * @param code - The code to be ported.
     * @param offset - The value to be inc/decremented to/from the offset.
     * @param mode - Add if incrementing, Sub if decrementing.
    **/

    wxRegEx ignore(_T("\
[CD][0-2C4-5]0{6}\\s[0-F]{8}|[3-A]4[0-F]{6}\\s[0-F]{8}|927[0-F]{5}\\s[0-F]{8}\
"), wxRE_ADVANCED);
    wxRegEx portRight(_T("D[36-B]0{6}\\s[0-F]{8}"), wxRE_ADVANCED);

    // Convert the offset wxString to a hex number.
    long hexOffset;
    offset.ToLong(&hexOffset, 16);

    // If we're subtracting, make the hexOffset negative.
    hexOffset *= mode == Add ? 1 : -1;

    // Split into columns
    wxArrayString left, right;
    CodeParser::SplitColumns(code, &left, &right);
    wxArrayString lines = wxc::wxSplit(code, _T('\n'));

    for (size_t i = 0; i < lines.GetCount(); ++i)
    {
        if (ignore.Matches(lines[i]))
            continue;

        long currentLeft, currentRight;
        left[i].ToLong(&currentLeft, 16);
        right[i].ToLong(&currentRight, 16);

        if (portRight.Matches(lines[i]))
        {
            long currentRight;
            right[i].ToLong(&currentRight, 16);

            right[i] = wxString::Format(
                _T("%.8X"),
                currentRight + hexOffset
            );
        }
        else
        {
            long currentLeft;
            left[i].ToLong(&currentLeft, 16);

            left[i] = wxString::Format(
                _T("%.8X"),
                currentLeft + hexOffset
            );
        }
    }

    return CodeParser::JoinColumns(left, right);
}

