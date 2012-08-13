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
 * @file frmMain.cpp - The main wxFrame for the application.
**/

#include "frmMain.h"

/** Initialize Identifiers **/

const long frmMain::ID_NOTEBOOK = wxNewId();

frmMain::frmMain(void) : wxFrame(NULL, wxID_ANY, NAME)
{
    /** Main Window **/

    pnlNotebook = new wxPanel(this, wxID_ANY);
    vboxNotebook = new wxBoxSizer(wxVERTICAL);

    // 2012-06-09 gbchaosmaster - How about using a wxAuiNotebook?
    // Changed nbMain, wxAuiNotebook from wxNotebook
    nbMain = new wxAuiNotebook(pnlNotebook, ID_NOTEBOOK, wxDefaultPosition,
                               wxDefaultSize, wxAUI_NB_TOP |
                               wxAUI_NB_TAB_SPLIT | wxAUI_NB_TAB_MOVE |
                               wxAUI_NB_SCROLL_BUTTONS);

    // Add the pages selectively depending on the build configuration.

#ifdef ADD_BUTTON_ACTIVATOR_GENERATOR
    nbMain->AddPage(new pgButtonActivatorGenerator(nbMain),
                    pgButtonActivatorGenerator::Title);
#endif

#ifdef ADD_POINTER_SEARCHER
    nbMain->AddPage(new pgPointerSearcher(nbMain),
                    pgPointerSearcher::Title);
#endif

#ifdef ADD_CODE_PORTER
    nbMain->AddPage(new pgCodePorter(nbMain),
                    pgCodePorter::Title);
#endif

#ifdef ADD_CODE_COMPRESSOR
    nbMain->AddPage(new pgCodeCompressor(nbMain),
                    pgCodeCompressor::Title);
#endif

#ifdef ADD_CODE_BEAUTIFIER
    nbMain->AddPage(new pgCodeBeautifier(nbMain),
                    pgCodeBeautifier::Title);
#endif

    vboxNotebook->Add(nbMain, 1, wxEXPAND);
    pnlNotebook->SetSizer(vboxNotebook);
    vboxNotebook->SetSizeHints(pnlNotebook);

    /** Configure Form **/

    // Set the menu bar.
    menuBar = new MenuBar(this);
    SetMenuBar(menuBar);
    // 800x500 default size seems reasonable.
    SetSize(wxSize(800, 500));
    // Center the window on screen on startup.
    Center();

    SetMinSizeToPage();

    Connect(ID_NOTEBOOK, wxEVT_COMMAND_AUINOTEBOOK_PAGE_CHANGED,
            wxCommandEventHandler(frmMain::SetMinSizeToPage));
}

void frmMain::SetMinSizeToPage(void)
{
    /**
     * Don't allow the window to shrink to where widgets are trunctuated.
    **/

    // Get the minimum size of the current notebook page.
    wxSize curPageMinSize =
        ((PAGE_CAST)nbMain->GetPage(
            nbMain->GetSelection()
         ))->vboxMargin->GetMinSize();

    // Just for the sake of having a little bit of extra padding...
    // This will be added onto both the height and width.
    unsigned char safety = MARGIN * 2;

    SetMinSize(wxSize(
        // Width
        curPageMinSize.GetWidth() +
        safety,
        // Height
        curPageMinSize.GetHeight() +
        // Account for the height of the menu bar and the notebook.
        menuBar->GetSize().GetHeight() + nbMain->GetTabCtrlHeight() +
        safety
    ));
}
void frmMain::SetMinSizeToPage(wxCommandEvent &WXUNUSED(event))
{
    // Overload so the function can be used as an event.
    SetMinSizeToPage();
}

