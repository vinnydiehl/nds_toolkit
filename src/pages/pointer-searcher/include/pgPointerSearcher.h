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
 * @file pgPointerSearcher.h - Header file for the Pointer Searcher page.
**/

#ifndef PGPOINTERSEARCHER_H_INCLUDED
#define PGPOINTERSEARCHER_H_INCLUDED

#include <wx/wx.h>

#include "globals.h"

class pgPointerSearcher : public wxPanel
{
public:

    static wxString Title;

    pgPointerSearcher(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *vboxMain;
    wxPanel *pnlMain;

    // Add layout boxes and such like so:
    // wxBoxSizer *hboxName;
    // wxStaticText *lblFoo;

    /** Events **/

    // Insert events here.

private:

    /** Identifiers **/

    // Format:
    // static const long ID_NAME;
};

#endif // PGPOINTERSEARCHER_H_INCLUDED

