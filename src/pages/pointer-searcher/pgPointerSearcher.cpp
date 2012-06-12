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
 * @file pgPointerSearcher.cpp - The program's Pointer Searcher page.
**/

#include "pgPointerSearcher.h"

// Title of the page:
wxString pgPointerSearcher::Title = _T("Pointer Searcher");

/** Initialize Identifiers **/

const long pgPointerSearcher::ID_BROWSE_FILE_1 = wxNewId();
const long pgPointerSearcher::ID_BROWSE_FILE_2 = wxNewId();

pgPointerSearcher::pgPointerSearcher(wxWindow *parent)
                 :  wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    vboxMain = new wxBoxSizer(wxVERTICAL);

    // hboxUpper - Contains everything above the Pointer Code section.

    hboxUpper = new wxBoxSizer(wxHORIZONTAL);

        // vboxControls - The control column/input fields on the left side.

    vboxControls = new wxBoxSizer(wxVERTICAL);

    /**
     * The wxStaticBoxSizers in vboxControls have a lot of box sizers nested
     * inside of them, so for the sake of sanity and readability, I'm not going
     * to rope those off with // Begin <name> and // End <name> tags. The
     * box sizers inside of the statics will only be marked with smaller
     * inline comments, which is more eye friendly in this case.
    **/

            // Begin svboxFileDumps

    svboxFileDumps = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                          _T("File Dumps"));

    // hboxFile1:
    hboxFile1 = new wxBoxSizer(wxHORIZONTAL);
    btnFile1 = new wxButton(pnlMain, ID_BROWSE_FILE_1, _T("File &1"));
    txtFile1 = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxFile1->Add(btnFile1, 0, wxRIGHT, 5);
    hboxFile1->Add(txtFile1, 1, wxEXPAND);

    // hboxFile2:
    hboxFile2 = new wxBoxSizer(wxHORIZONTAL);
    btnFile2 = new wxButton(pnlMain, ID_BROWSE_FILE_2, _T("File &2"));
    txtFile2 = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxFile2->Add(btnFile2, 0, wxRIGHT, 5);
    hboxFile2->Add(txtFile2, 1, wxEXPAND);

    // The checkbox is on its own
    chk8ChBeforeBin = new wxCheckBox(
        pnlMain, wxID_ANY, _T("8 Characters Before .bin to the Address Boxes")
    );

    // Add the above to the static
    svboxFileDumps->Add(hboxFile1, 1, wxEXPAND | wxBOTTOM, 5);
    svboxFileDumps->Add(hboxFile2, 1, wxEXPAND | wxBOTTOM, 5);
    svboxFileDumps->Add(chk8ChBeforeBin, 0, wxALIGN_CENTER_HORIZONTAL);

            // End svboxFileDumps

            // Begin shboxOffsetTarget

    shboxOffsetTarget = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                             _T("Offset Target"));

            // End shboxOffsetTarget

            // Begin shboxDataInput

    shboxDataInput = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                          _T("Data Input"));

            // End shboxDataInput

    vboxControls->Add(svboxFileDumps, 0, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(shboxOffsetTarget, 0, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(shboxDataInput, 0, wxEXPAND);

        // End vboxControls

        // vboxAddresses - Area on the right listing the discovered addresses.

    vboxAddresses = new wxBoxSizer(wxVERTICAL);

        // End vboxAddresses

    hboxUpper->Add(vboxControls, 1, wxEXPAND | wxRIGHT, 5);
    hboxUpper->Add(vboxAddresses, 0, wxEXPAND);

    // End hboxUpper

    vboxMain->Add(hboxUpper, 0, wxEXPAND | wxBOTTOM, 5);

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

