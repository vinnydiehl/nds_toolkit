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
 * @file pgBlank.cpp - A template for creating a new page.
 * To keep this @file consistent with the other pages, use this format:
 * @file pgBlank.cpp - The program's <NAME OF PAGE> page.
**/

#include "pgBlank.h"

// Title of the page:
wxString pgBlank::Title = _T("Blank Page");

/** Initialize Identifiers **/

// Format:
// const long ClassName::ID_NAME = wxNewId();

pgBlank::pgBlank(wxWindow *parent)
       : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    vboxMain = new wxBoxSizer(wxVERTICAL);

    // Add layout boxes and whatnot like so:
    // hboxName = new wxBoxSizer(wxHORIZONTAL);
    // And then items to that:
    // lblFoo = new wxStaticText(pnlMain, wxID_ANY, _T("Whatever..."));
    // hboxName->Add(lblFoo, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    // Then add it to the main box...
    // vboxMain->Add(hboxName, 0, wxEXPAND);
    // Maybe add a separator? This uses the SEPARATOR macro from globals.h.
    // vboxMain->Add(-1, SEPARATOR);
    // You get the idea...

    pnlMain->SetSizer(vboxMain);
    vboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect main window events
    // Put all of your event connections here. Example:
//  Connect(ID_NAME, wxEVT_COMMAND_BUTTON_CLICKED,
//          wxCommandEventHandler(ClassName::MethodName));
}

