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
 * @file CodePorter.h - Header file for the CodePorter class.
**/

#ifndef CODEPORTER_H_INCLUDED
#define CODEPORTER_H_INCLUDED

#include <wx/arrstr.h>
#include <wx/string.h>

#include "wx2.9/arrstr.h"

#include "CodeParser.h"

class CodePorter
{
public:
    static wxString Port(wxString code, wxString offset, bool dec=false);

private:
    static wxString mPurePort(wxString code, wxString offset, bool dec=false);
};

#endif // CODEPORTER_H_INCLUDED

