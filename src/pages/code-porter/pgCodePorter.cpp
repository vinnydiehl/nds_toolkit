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
 * @file pgCodePorter.cpp - The program's Code Porter page.
**/

#include "pgCodePorter.h"

// Title of the page:
wxString pgCodePorter::Title = _T("Code Porter");

/** Initialize Identifiers **/

const long pgCodePorter::ID_PORT = wxNewId();

const long pgCodePorter::ID_CLEAR = wxNewId();
const long pgCodePorter::ID_COPY = wxNewId();
const long pgCodePorter::ID_PASTE = wxNewId();

pgCodePorter::pgCodePorter(wxWindow *parent)
            : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    hboxMain = new wxBoxSizer(wxHORIZONTAL);

////////////////////////////////////////////////////////////////////////////////

    vboxInput = new wxBoxSizer(wxVERTICAL);

    lblInput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Input"));
    txtInput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                              wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE | wxHSCROLL);

    vboxInput->Add(lblInput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxInput->Add(txtInput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    vboxControls = new wxBoxSizer(wxVERTICAL);

    ///// Begin svboxOperation

    svboxOperation = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                          _T("Operation"));

    // The radio buttons in here have their own hbox
    hboxOperationRadios = new wxBoxSizer(wxHORIZONTAL);

    radAdd = new wxRadioButton(pnlMain, wxID_ANY, _T("&Add"),
                               wxDefaultPosition, wxDefaultSize,
                               wxRB_GROUP);
    radSub = new wxRadioButton(pnlMain, wxID_ANY, _T("&Sub"));

    hboxOperationRadios->Add(radAdd, 1, wxEXPAND);
    hboxOperationRadios->Add(radSub, 1, wxEXPAND);

    lblOffset = new wxStaticText(pnlMain, wxID_ANY, _T("Offset (hex):"));
    txtOffset = new wxTextCtrl(pnlMain, wxID_ANY);

    svboxOperation->Add(hboxOperationRadios, 0, wxEXPAND | wxBOTTOM, 5);
    svboxOperation->Add(lblOffset, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    svboxOperation->Add(txtOffset, 0, wxEXPAND);

    ///// btnPort is top-level

    btnPort = new wxButton(pnlMain, ID_PORT, _T("&Port"));

    ///// Begin svboxTools

    svboxTools = new wxStaticBoxSizer(wxVERTICAL, pnlMain, _T("Tools"));

    btnClear = new wxButton(pnlMain, ID_CLEAR, _T("C&lear"));
    btnCopy = new wxButton(pnlMain, ID_COPY, _T("&Copy"));
    btnPaste = new wxButton(pnlMain, ID_PASTE, _T("&Paste"));

    svboxTools->Add(btnClear, 0, wxEXPAND | wxBOTTOM, 2);
    svboxTools->Add(btnCopy, 0, wxEXPAND | wxBOTTOM, 2);
    svboxTools->Add(btnPaste, 0, wxEXPAND);


    // Finish up vboxControls
    vboxControls->Add(svboxOperation, 0, wxEXPAND | wxLEFT |
                      wxRIGHT | wxBOTTOM, 5);
    vboxControls->Add(btnPort, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    vboxControls->Add(svboxTools, 0, wxEXPAND | wxLEFT | wxRIGHT, 5);

////////////////////////////////////////////////////////////////////////////////

    vboxOutput = new wxBoxSizer(wxVERTICAL);

    lblOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));
    txtOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxHSCROLL);

    vboxOutput->Add(lblOutput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxOutput->Add(txtOutput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    hboxMain->Add(vboxInput, 2, wxEXPAND);
    hboxMain->Add(vboxControls, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);
    hboxMain->Add(vboxOutput, 2, wxEXPAND);

    pnlMain->SetSizer(hboxMain);
    hboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect Code Porter events
    Connect(ID_PORT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodePorter::Port));

    Connect(ID_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodePorter::Clear));
    Connect(ID_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodePorter::Copy));
    Connect(ID_PASTE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodePorter::Paste));
}

void pgCodePorter::Port(wxCommandEvent &WXUNUSED(event))
{
}

void pgCodePorter::Clear(wxCommandEvent &WXUNUSED(event))
{
}
void pgCodePorter::Copy(wxCommandEvent &WXUNUSED(event))
{
}
void pgCodePorter::Paste(wxCommandEvent &WXUNUSED(event))
{
}

