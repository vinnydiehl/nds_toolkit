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

wxString CodeParser::Beautify(wxString code, bool upperHex,
                              bool stripComments, bool stripEmpty)
{
    /**
     * Fix the formatting of NDS code.
     *
     * @param code - Code to be beautified.
     * @param upperHex - Capitalize any lowercase hex digits.
     * @param stripComments - Remove all comments from the code.
     * @param stripEmpty - Remove all empty lines from the code.
    **/

    // First verify the input. It will fuck us up heavily if we don't.

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Beautify()- BEGINNING VERIFICATION"));
#endif

    if (!Verify(code))
        return _T("Invalid");

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Beautify()- VERIFICATION COMPLETE"));
#endif

    // Do all line processing now.
    wxArrayString raw = wxcArrayString::wxSplit(code, _T('\n'));

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Beautify()- Contents of raw:\n"));
    for (size_t i = 0; i < raw.GetCount(); ++i)
        wxPuts(raw[i]);
#endif

    wxArrayString lines;
    for (size_t i = 0; i < raw.GetCount(); ++i)
    {
        // Trim the line while we're here
        wxString line = raw[i].Trim().Trim(false);

        if ((!stripEmpty || !line.IsEmpty()) &&
            (!stripComments || line[0] != _T(':')))
            lines.Add(
                // Might as well also do the hex capitalization here.
                // Capitalize the string if it isn't a comment and upperHex
                // is enabled.
                upperHex && line[0] != _T(':')
                ? line.Upper()
                : line
            );
    }

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Beautify()- Contents of lines:\n"));
    for (size_t i = 0; i < lines.GetCount(); ++i)
        wxPuts(lines[i]);
#endif

    // Packing up the code while leaving comments untouched is very tricky.
    // I don't want to use a wrapper, so do some preliminary touchups.

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Beautify()- BEGINNING PACKING"));
#endif

    wxArrayString codepkg;
    if (stripComments)
    {
#ifdef DEBUG
        wxPuts(_T("\
DEBUG INFO- CodeParser::Beautify()-\n\
\tComment stripping enabled, packing the code as a whole.\
"));
#endif
        codepkg.Add(mStripChar(wxcArrayString::wxJoin(lines, _T('\n')),
                               _T(" \t\n\r")));
    }
    else
    {
#ifdef DEBUG
        wxPuts(_T("\
DEBUG INFO- CodeParser::Beautify()-\n\
\tComments are being packed with the code.\
"));
#endif
        wxArrayString stage;
        for (size_t i = 0; i < lines.GetCount(); ++i)
        {
            if (lines[i][0] != _T(':'))
            {
                stage.Add(lines[i]);

                if (i >= lines.GetCount() - 1)
                {
                    // We've reached the last line, pack up the stage and add
                    // it to codepkg so we can finish.
                    codepkg.Add(
                        mStripChar(wxcArrayString::wxJoin(stage, _T('\n')),
                                   _T(" \t\n\r"))
                    );
                }
            }
            else
            {
                if (!stage.IsEmpty())
                {
                    // There is code on the stage that still needs to be
                    // packed so that we can pack in this comment.
                    // Pack the stage, add to codepkg, then clear the stage.
                    codepkg.Add(
                        mStripChar(wxcArrayString::wxJoin(stage, _T('\n')),
                                   _T(" \t\n\r"))
                    );
                    stage.Clear();
                }

                // Now add the comment to the package
                codepkg.Add(lines[i]);
            }
        }
    }

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Beautify()- PACKING COMPLETE"));
    wxPuts(_T("DEBUG INFO- CodeParser::Beautify()- Contents of codepkg:\n"));
    for (size_t i = 0; i < codepkg.GetCount(); ++i)
        wxPuts(codepkg[i]);
#endif

    // We will unpack the codepkg into its final form here.
    wxArrayString final;

    // Loop over the code package so we can unpack.
    for (size_t i = 0; i < codepkg.GetCount(); ++i)
    {
        wxString chunk = codepkg[i];

        // If the chunk is a comment, direct deposit...
        if (chunk[0] == _T(':'))
            final.Add(chunk);
        else
            while (!chunk.IsEmpty())
            {
                // Grap the first 16 characters of the string...
                wxString group = chunk.Left(16);
                // Add a space in the middle...
                group.insert(8, _T(" "));
                // Remove those 16 characters from the chunk...
                chunk.Remove(0, 16);
                // And now add that group to the code.
                final.Add(group);
            }
    }

    return wxcArrayString::wxJoin(final, _T('\n'));
}

bool CodeParser::Verify(wxString code)
{
    /**
     * Return true if the input is valid as NDS code, otherwise return false.
    **/

    /** Preprocessing **/

    // Strip away stuff that we don't need; Comments, blanks, extra whitespace.
    wxArrayString raw = wxcArrayString::wxSplit(code, _T('\n'));

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Verify()- Contents of raw:\n"));
    for (size_t i = 0; i < raw.GetCount(); ++i)
        wxPuts(raw[i]);
#endif

    wxArrayString lines;
    for (size_t i = 0; i < raw.GetCount(); ++i)
    {
        // Trim the current line so whitespace doesn't throw us off
        wxString line = raw[i].Trim().Trim(false);

        if (!line.IsEmpty() && line[0] != _T(':'))
            lines.Add(line);
    }

#ifdef DEBUG
    wxPuts(_T("\nDEBUG INFO- CodeParser::Verify()- Contents of lines:\n"));
    for (size_t i = 0; i < lines.GetCount(); ++i)
        wxPuts(lines[i]);
#endif

    // Strip the rest of the whitespace.
    // Yes, I know, I join with newlines and then strip the newlines. I just
    // want to ensure that the code is returned to its previous state before
    // all of the whitespace is removed.
    code = mStripChar(wxcArrayString::wxJoin(lines, _T('\n')), _T(" \t\n\r"));

#ifdef DEBUG
    wxPuts(_T("\
\nDEBUG INFO- CodeParser::Verify()- Contents of code after stripping:\n\
"));
    wxPuts(code);
#endif

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

wxArrayString CodeParser::Tokenize(wxString code)
{
    wxArrayString output;

    wxArrayString lines = wxcArrayString::wxSplit(code, _T('\n'));
    for (size_t i = 0; i < lines.GetCount(); ++i)
    {
        wxArrayString accumulator;
        bool iscomment = false;

        // Is this line a comment?
        if (lines[i][0] == _T(':'))
        {
            if (!iscomment) // The last line wasn't...
            {
                // Dump the current accumulation if there is any
                if (!accumulator.IsEmpty())
                {
                    output.Add(wxcArrayString::wxJoin(accumulator, _T('\n')));
                    accumulator.Clear();
                }

                // Start a comment accumulation
                iscomment = true;
                accumulator.Add(lines[i]);
            }
            else // Continue the comment accumulation
                accumulator.Add(lines[i]);
        }
        else // The line isn't a comment
        {
            if (iscomment) // But the last line was...
            {
                // Dump the current accumulation if there is any
                if (!accumulator.IsEmpty())
                {
                    output.Add(wxcArrayString::wxJoin(accumulator, _T('\n')));
                    accumulator.Clear();
                }

                // Start a code accumulation
                iscomment = false;
                accumulator.Add(lines[i]);
            }
            else // Continue the current code accumulation
                accumulator.Add(lines[i]);
        }
    }

    return output;
}

wxArrayString CodeParser::LeftColumn(wxString code)
{
    wxArrayString output;

    wxArrayString lines = wxcArrayString::wxSplit(code, _T('\n'));
    for (size_t i = 0; i < lines.GetCount(); ++i)
        output.Add(lines[i].Left(8));

    return output;
}
wxArrayString CodeParser::RightColumn(wxString code)
{
    wxArrayString output;

    wxArrayString lines = wxcArrayString::wxSplit(code, _T('\n'));
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

    return wxcArrayString::wxJoin(pairs, _T('\n'));
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

