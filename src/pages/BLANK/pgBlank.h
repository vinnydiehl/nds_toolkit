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
 * @file pgBlank.h - A template header file for creating a new page.
 * To keep this @file consistent with the other pages, use this format:
 * @file pgBlank.h - Header file for the <NAME OF PAGE> page.
**/

// DO NOT FORGET TO SET THESE HEADER GUARDS PROPERLY:

#ifndef PGBLANK_H_INCLUDED
#define PGBLANK_H_INCLUDED

#include <wx/panel.h>
#include <wx/sizer.h>

#include "globals.h"

class pgBlank : public wxPanel
{
public:

    static wxString Title;

    pgBlank(wxWindow *parent);

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

#endif // PGBLANK_H_INCLUDED

