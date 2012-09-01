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
 * @file PatchCodeBuilder.cpp - pgCodeCompressor's Patch Code Builder.
**/

#include "PatchCodeBuilder.h"

wxString PatchCodeBuilder::Build(wxString input)
{
    // Verify their input
    if (!CodeParser::Verify(input))
        throw wxString(_T("Invalid code input."));

    wxArrayString lines = wxc::wxSplit(
        // Filter the input through the beautifier, stripping comments
        CodeParser::Beautify(input,
                             UPPER_HEX |
                             STRIP_COMMENTS |
                             STRIP_BLANK_LINES),
        _T('\n')
    );

    // Generate an array with the last halves of each line.
    wxArrayString code;
    for (size_t i = 0; i < lines.GetCount(); ++i)
    {
        // Now is a good time as any to trim the lines
        wxString line = lines[i].Trim().Trim(false);
        if (!line.IsEmpty())
        {
            // Now grab everything after the space (it occurs at index 9)
            wxString end;
            for (size_t j = 9; j < line.Len(); ++j)
                end += line[j];

            // Add it to code
            code.Add(end);
        }
    }

    // Build the first line of the output based on the number of input lines
    // and the starting address of the code.
    wxString primer = wxString::Format(
        _T("E%s %.8X"),
        lines[0].Mid(1, 7).c_str(),
        // This needs a cast to int or it will throw a runtime warning on
        // Windows machines about the format specifier not matching the
        // argument type.
        (int)(code.GetCount() * 4)
    );

    // If the number of lines is odd, append a "00000000", we'll use it later
    if (code.GetCount() % 2 != 0)
        code.Add(_T("00000000"));

    // Build the output

    wxArrayString pairs = mGroup(code);

    return primer + _T('\n') + wxc::wxJoin(pairs, _T('\n'));
}

/** Container Manipulation **/

wxArrayString PatchCodeBuilder::mGroup(wxArrayString arr, size_t n)
{
    wxString accumulator;
    wxArrayString output;

    size_t tracker = 0;
    for (size_t i = 0; i < arr.GetCount(); ++i)
    {
        accumulator += arr[i] + _T(' ');
        ++tracker;
        if (tracker >= n)
        {
            accumulator.Trim();
            output.Add(accumulator);
            accumulator.Clear();
            tracker = 0;
        }
    }

    return output;
}

