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
 * @file PSR.h - The header for the PSR file format class.
**/

#ifndef PSR_H_INCLUDED
#define PSR_H_INCLUDED

#include <wx/arrstr.h>
#include <wx/ffile.h>
#include <wx/regex.h>
#include <wx/string.h>
#include <wx/textfile.h>

#include "wx2.9/arrstr.h"

// Regular expression constants for verifying file validity.
const wxRegEx NUMBER(_T("\\A\\d+\\Z"), wxRE_ADVANCED);
// * because the "Hex Value" line is allowed to be blank.
const wxRegEx HEX_NUMBER(_T("\\A[0-9A-F]*\\Z"), wxRE_ADVANCED);
const wxRegEx RESULT(
    _T("\\A0x[0-9A-F]{8} : 0x[0-9A-F]{8} :: 0x[0-9A-F]{8}\\Z"),
    wxRE_ADVANCED
);

class PSR
{
public:
    PSR(wxFFile *file);
    PSR(wxString filename);

    void Read(wxFFile *file);
    void Read(wxString filename);

    static void Write(wxString filename, wxArrayString results,
                      int index, wxString hexValue);

    bool Verify(void);

    wxArrayString GetResults(void);
    int GetIndex(void);
    wxString GetHexValue(void);

private:
    wxArrayString mContents;
};

#endif // PSR_H_INCLUDED
