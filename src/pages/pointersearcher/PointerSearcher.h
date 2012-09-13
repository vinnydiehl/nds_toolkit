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
 * @file PointerSearcher.h - Header file for the PointerSearcher class.
**/

#ifndef POINTERSEARCHER_H_INCLUDED
#define POINTERSEARCHER_H_INCLUDED

#include <wx/arrstr.h>
#include <wx/datstrm.h>
#include <wx/stream.h>
#include <wx/string.h>
#include <wx/wfstream.h>

#include "wx2.9/arrstr.h"

enum TargetType
{
    Negative,
    Positive
};

class PointerSearcher
{
public:
    static void Search(wxArrayString *outputSearchResults,
                       unsigned *outputSmallest,
                       wxFFileInputStream *file1, wxFFileInputStream *file2,
                       wxString addr1, wxString addr2, wxString hexValueStr,
                       TargetType posneg, wxString maxPtrOffsetStr);

    static wxString ArCode(wxString result, wxString hexValueStr);
};

#endif // POINTERSEARCHER_H_INCLUDED
