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
 * @file wxcArrayString.h - Header file for the wxcArrayString class.
**/

#pragma once

#ifndef WXCARRAYSTRING_H_INCLUDED
#define WXCARRAYSTRING_H_INLCUDED

#include <wx/arrstr.h>
#include <wx/string.h>

class wxcArrayString
{
public:
    static wxString wxJoin(wxArrayString arr, wxChar sep);
    static wxArrayString wxSplit(wxString stf, wxChar sep);
};

#endif // WXCARRAYSTRING_H_INLCUDED

