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
 * @file PSR.cpp - The Pointer Searcher Results file format.
**/

#include "PSR.h"

// Read in a file when constructing an instance.
PSR::PSR(wxFFile *file)
{
    Read(file);
}
PSR::PSR(wxString filename)
{
    Read(filename);
}

void PSR::Read(wxFFile *file)
{
    /**
     * Read in a new PSR file.
    **/

    // Read the file into a temporary string.
    wxString contents;
    file->ReadAll(&contents);

    // Separate the lines into a wxArrayString.
    mContents = wxc::wxSplit(contents, _T('\n'));

    // Trim leading/trailing whitespace from each line.
    for (size_t i = 0; i < mContents.GetCount(); ++i)
        mContents[i] = mContents[i].Trim().Trim(false);
}
void PSR::Read(wxString filename)
{
    /**
     * Overload to allow the filename to be passed in as a wxString.
    **/

    Read(new wxFFile(filename));
}

void PSR::Write(wxString filename, wxArrayString results,
                int index, wxString hexValue)
{
    /**
     * Write the information to a Pointer Searcher Results file.
    **/

    wxTextFile file(filename);

    // Prepare the file for writing.
    if (file.Exists())
        file.Open();
    else file.Create();

    // Empty out any existing contents and write to the file.
    file.Clear();
    file.AddLine(wxString::Format(
        _T("%d\n%s\n%s"),
        index,
        hexValue.c_str(),
        wxc::wxJoin(results, _T('\n')).c_str()
    ));

    // Save the file to the disk.
    file.Write();
    file.Close();
}

bool PSR::Verify(void)
{
    /**
     * Return true if the currently loaded file is a properly formatted
     * Pointer Searcher Results file.
    **/

    // Should definitely have 3 or more lines.
    // Checking this up here prevents an out of range error during the for
    // loop below.
    if (mContents.GetCount() < 3)
        return false;

    // Make sure that all lines except the first two are valid, well-formatted
    // search results.
    for (size_t i = 2; i < mContents.GetCount(); ++i)
        if (!RESULT.Matches(mContents[i]))
            return false;

    // Make sure that the first line is a number and that the number, an index
    // to the rest of the wxArrayString, doesn't go out of range. Also check
    // that the Hex Value is a valid hexadecimal string.
    return NUMBER.Matches(mContents[0]) &&
           HEX_NUMBER.Matches(mContents[1]) &&
           (unsigned)GetIndex() < mContents.GetCount();
}

wxArrayString PSR::GetResults(void)
{
    /**
     * Return a wxArrayString containing all of the search results.
    **/

    // Make and return a copy of the wxArrayString and remove the first two
    // elements.
    wxArrayString copy = mContents;
    copy.RemoveAt(0, 2);

    return copy;
}
int PSR::GetIndex(void)
{
    /**
     * Return the index of the currently selected item.
    **/

    // This will hold the converted number.
    long index;

    // Just fall back to 0 if the conversion to a number fails.
    return mContents[0].ToLong(&index) ? index : 0;
}
wxString PSR::GetHexValue(void)
{
    /**
     * Return the contents of the Hex Value input.
    **/

    return mContents[1];
}
