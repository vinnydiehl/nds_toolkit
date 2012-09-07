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
 * @file arrstr.cpp - Functions from the wxWidgets 2.9 wxArrayStrings.
**/

#include "arrstr.h"

namespace wxc {

wxString wxJoin(wxArrayString arr, wxChar sep)
{
    wxString output;

    for (size_t i = 0; i < arr.GetCount(); ++i)
    {
        output += arr[i];
        if (i < arr.GetCount() - 1)
            output += sep;
    }

    return output;
}
wxArrayString wxSplit(wxString str, wxChar sep)
{
    wxArrayString output;
    wxString accumulator = _T("");

    for (size_t i = 0; i < str.Len(); ++i)
    {
        if (str[i] == sep)
        {
            // If we encounter the separator (or if we reach the end of the
            // string), add the current state of the accumulator to the output
            // array and reset the accumulator.
            output.Add(accumulator);
            accumulator = _T("");
        }
        else if (i == str.Len() - 1)
        {
            // Last character of the string and it isn't the separator, so add
            // it to the accumulator and then add the accumulator to output.
            accumulator += str[i];
            output.Add(accumulator);
        }
        else // Non-separator character, add it to the accumulator.
            accumulator += str[i];
    }

    return output;
}

} // End namespace wxc
