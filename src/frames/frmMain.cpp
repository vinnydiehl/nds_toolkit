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
 * @file frmMain.cpp - The main wxFrame for the application.
**/

#include "frmMain.h"

// Title of the application:
const wxString TITLE = _T("NDS Hacking Kit");

frmMain::frmMain(void) : wxFrame(NULL, wxID_ANY, TITLE)
{
    /** Main Window **/

    pnlNotebook = new wxPanel(this, wxID_ANY);
    vboxNotebook = new wxBoxSizer(wxVERTICAL);

    // 2012-06-09 gbchaosmaster - How about using a wxAuiNotebook?
    nbMain = new wxAuiNotebook(pnlNotebook, wxID_ANY, wxDefaultPosition,
                               wxDefaultSize, wxAUI_NB_TOP |
                               wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE |
                               wxAUI_NB_SCROLL_BUTTONS);

    nbMain->AddPage(new pgButtonActivatorGenerator(nbMain),
                    pgButtonActivatorGenerator::Title);
    nbMain->AddPage(new pgPointerSearcher(nbMain),
                    pgPointerSearcher::Title);
    nbMain->AddPage(new pgCodePorter(nbMain),
                    pgCodePorter::Title);
    nbMain->AddPage(new pgCodeCompressor(nbMain),
                    pgCodeCompressor::Title);

    vboxNotebook->Add(nbMain, 1, wxEXPAND);
    pnlNotebook->SetSizer(vboxNotebook);
    vboxNotebook->SetSizeHints(pnlNotebook);

    /** Configure Form **/

    // Set the menu bar to a new instance of MenuBar
    SetMenuBar(new MenuBar(this));
    // Give it a starting size of 750x450 for now.
    SetSize(wxSize(750, 450));
    // Center the window on screen on startup
    Center();
}

