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
 * @file EBuilder.h - Header file for pgCodeCompressor's E Builder.
**/

#ifndef EBUILDER_H_INCLUDED
#define EBUILDER_H_INCLUDED

#include <wx/arrstr.h>
#include <wx/string.h>

#include "CodeParser.h"
#include "wxcArrayString.h"

wxString buildECodeType(wxString input);
wxArrayString group(wxArrayString arr, size_t n=2);

#endif // EBUILDER_H_INCLUDED

