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
 * @file CodeParser.cpp - Class with static methods for code verification.
 *
 * See #1 on the issue tracker.
**/

#include "CodeParser.h"

/** Public Methods **/

wxString CodeParser::Beautify(wxString code, int flags)
{
    /**
     * Fix the formatting of NDS code.
     *
     * @param code - Code to be beautified.
     * @param flags - Code parser options.
    **/

    // First verify the input, or risk death.
    if (!Verify(code))
        return _T("Invalid");

    // Split the input into lines...
    wxArrayString raw = wxc::wxSplit(code, _T('\n'));

    // Build the code onto here.
    wxArrayString processed;

    for (size_t i = 0; i < raw.GetCount(); ++i)
    {
        // Trim everything.
        wxString line = raw[i].Trim().Trim(false);

        // Skip comments/blank lines if they aren't allowed.
        if ((flags & STRIP_COMMENTS && line[0] == _T(':')) ||
            (flags & STRIP_BLANK_LINES && line.IsEmpty()))
            continue;

        // Add comments and blank lines directly...
        if (line[0] == _T(':') || line.IsEmpty())
            processed.Add(line);
        // Otherwise it's a line of code...
        else
        {
            // Enforce the UPPER_HEX option.
            if (flags & UPPER_HEX)
                line.MakeUpper();

            // Remove the whitespace.
            wxString builder;
            for (size_t j = 0; j < line.Len(); ++j)
                if (!(wxString(_T(" \t"))).Contains(line[j]))
                    builder += line[j];

            // Condense all hunks of code into one line.
            // If processed is empty, or the last line in processed is
            // either a blank or a comment, we need to start a new code line.
            if (processed.IsEmpty() ||
                processed.Last().IsEmpty() ||
                processed.Last()[0] == _T(':'))
                processed.Add(builder);
            // Otherwise, append onto the current going code line.
            else processed[processed.GetCount() - 1] += builder;
        }
    }

    // Build the final result onto here.
    wxArrayString final;

    for (size_t i = 0; i < processed.GetCount(); ++i)
    {
        wxString line = processed[i];

        if (line[0] == _T(':') || line.IsEmpty())
            final.Add(line);
        else
        {
            // If we don't have the right number of characters, uh-oh...
            // bail out and call it invalid.
            if (line.Len() % 16 != 0)
                return _T("Invalid");

            while (!line.IsEmpty())
            {
                final.Add(line.Left(16).insert(8, _T(" ")));
                line.Remove(0, 16);
            }
        }
    }

    // Trim any whitespace on either end before returning.
    return wxc::wxJoin(final, _T('\n')).Trim().Trim(false);
}

bool CodeParser::Verify(wxString code)
{
    /**
     * Return true if the input is valid as NDS code, otherwise return false.
    **/

    /** Preprocessing **/

    // Strip away stuff that we don't need; Comments, blanks, extra whitespace.
    wxArrayString raw = wxc::wxSplit(code, _T('\n'));

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
    code = mStripChar(wxc::wxJoin(lines, _T('\n')), _T(" \t\n\r"));

    // Now that it's parsed, we just need to see whether or not it has the
    // right amount of digits (some multiple of 16), and if it is valid
    // hexadecimal. We can return whatever result we get from that.
    return code.Len() % 16 == 0 && IsHex(code);
}
bool CodeParser::IsHex(wxString str)
{
    /**
     * Return true if str is a valid hexadecimal value, false otherwise.
    **/

    return HEX.Matches(str);
}

wxArrayString CodeParser::LeftColumn(wxString code)
{
    wxArrayString output;

    wxArrayString lines = wxc::wxSplit(code, _T('\n'));
    for (size_t i = 0; i < lines.GetCount(); ++i)
        output.Add(lines[i].Left(8));

    return output;
}
wxArrayString CodeParser::RightColumn(wxString code)
{
    wxArrayString output;

    wxArrayString lines = wxc::wxSplit(code, _T('\n'));
    for (size_t i = 0; i < lines.GetCount(); ++i)
        output.Add(lines[i].Right(8));

    return output;
}
void CodeParser::SplitColumns(wxString code, wxArrayString *left,
                              wxArrayString *right)
{
    *left = LeftColumn(code);
    *right = RightColumn(code);
}
wxString CodeParser::JoinColumns(wxArrayString left, wxArrayString right)
{
    wxArrayString pairs;

    // Just in case they gave us arrays of differing sizes, always use the
    // smaller count to loop with...
    size_t count = left.GetCount() > right.GetCount()
                   ? right.GetCount()
                   : left.GetCount();

    for (size_t i = 0; i < count; ++i)
        pairs.Add(left[i] + _T(' ') + right[i]);

    return wxc::wxJoin(pairs, _T('\n'));
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
            if (str[i] == ch[j])
                isallowed = false;

        // If it wasn't stripped, add it to the output.
        if (isallowed)
            output += str[i];
    }

    return output;
}
