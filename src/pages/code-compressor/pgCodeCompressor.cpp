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
 * @file pgCodeCompressor.cpp - The program's Code Compressor page.
**/

#include "pgCodeCompressor.h"

// Title of the page:
wxString pgCodeCompressor::Title = _T("Code Compressor");

/** Initialize Identifiers **/

const long pgCodeCompressor::ID_GENERATE = wxNewId();
const long pgCodeCompressor::ID_CLEAR_ALL = wxNewId();

const long pgCodeCompressor::ID_BUILD = wxNewId();

const long pgCodeCompressor::ID_LOOP_COPY = wxNewId();
const long pgCodeCompressor::ID_E_COPY = wxNewId();

pgCodeCompressor::pgCodeCompressor(wxWindow *parent)
                : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    hboxMain = new wxBoxSizer(wxHORIZONTAL);

    // svboxLoopCodeGenerator - Loop Code Generator section

    svboxLoopCodeGenerator = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                                  _T("Loop Code Generator"));

        // Begin hboxBaseCode

    hboxBaseCode = new wxBoxSizer(wxHORIZONTAL);

    lblBaseCode = new wxStaticText(pnlMain, wxID_ANY, _T("Base Code:"));
    txtBaseCode = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxBaseCode->Add(lblBaseCode, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxBaseCode->Add(txtBaseCode, 1, wxEXPAND);

        // End hboxBaseCode

        // Begin hboxTotalLoopCount

    hboxTotalLoopCount = new wxBoxSizer(wxHORIZONTAL);

    lblTotalLoopCount = new wxStaticText(pnlMain, wxID_ANY,
                                         _T("Total Loop Count:"));
    txtTotalLoopCount = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxTotalLoopCount->Add(lblTotalLoopCount, 0,
                            wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxTotalLoopCount->Add(txtTotalLoopCount, 1, wxEXPAND);

        // End hboxTotalLoopCount

        // Begin hboxOffsetIncrement

    hboxOffsetIncrement = new wxBoxSizer(wxHORIZONTAL);

    lblOffsetIncrement = new wxStaticText(pnlMain, wxID_ANY,
                                          _T("Offset Increment:"));
    txtOffsetIncrement = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxOffsetIncrement->Add(lblOffsetIncrement, 0,
                             wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxOffsetIncrement->Add(txtOffsetIncrement, 1, wxEXPAND);

        // End hboxOffsetIncrement

        // Begin hboxValueIncrement

    hboxValueIncrement = new wxBoxSizer(wxHORIZONTAL);

    lblValueIncrement = new wxStaticText(pnlMain, wxID_ANY,
                                         _T("Value Increment:"));
    txtValueIncrement = new wxTextCtrl(pnlMain, wxID_ANY);
    chkValueIncrement = new wxCheckBox(pnlMain, wxID_ANY, wxEmptyString);

    hboxValueIncrement->Add(lblValueIncrement, 0,
                            wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxValueIncrement->Add(txtValueIncrement, 1, wxEXPAND);
    hboxValueIncrement->Add(chkValueIncrement, 0,
                            wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

        // End hboxValueIncrement

        // Begin hboxLoopControls

    hboxLoopControls = new wxBoxSizer(wxHORIZONTAL);

    btnGenerate = new wxButton(pnlMain, ID_GENERATE, _T("&Generate"));
    btnClearAll = new wxButton(pnlMain, ID_CLEAR_ALL, _T("Clear &All"));

    hboxLoopControls->Add(btnGenerate, 1, wxEXPAND | wxRIGHT, 5);
    hboxLoopControls->Add(btnClearAll, 1, wxEXPAND);

        // End hboxLoopControls

    // Divider Line
    slnLoopCodeGenerator = new wxStaticLine(pnlMain);

    // Output Box
    txtLoopOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxTE_MULTILINE);

    // Copy Button
    btnLoopCopy = new wxButton(pnlMain, ID_LOOP_COPY,
                               _T("&Copy to Clipboard"));

    svboxLoopCodeGenerator->Add(hboxBaseCode, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxTotalLoopCount, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxOffsetIncrement, 0,
                                wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxValueIncrement, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxLoopControls, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(slnLoopCodeGenerator, 0,
                                wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(txtLoopOutput, 1, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(btnLoopCopy, 0, wxEXPAND);

    // End svboxLoopCodeGenerator

    // shboxEBuilder - E Builder section

    shboxEBuilder = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                         _T("E Builder"));

        // Begin vboxInput

    vboxInput = new wxBoxSizer(wxVERTICAL);

    lblInput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Input"));
    txtInput = new wxTextCtrl(pnlMain, wxID_ANY);
    btnBuild = new wxButton(pnlMain, ID_BUILD, _T("&Build"));

    vboxInput->Add(lblInput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxInput->Add(txtInput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxInput->Add(btnBuild, 0, wxEXPAND);

        // End vboxInput

        // Begin vboxOutput

    vboxOutput = new wxBoxSizer(wxVERTICAL);

    lblOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));
    txtOutput = new wxTextCtrl(pnlMain, wxID_ANY);
    btnECopy = new wxButton(pnlMain, ID_E_COPY, _T("C&opy to Clipboard"));

    vboxOutput->Add(lblOutput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxOutput->Add(txtOutput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxOutput->Add(btnECopy, 0, wxEXPAND);

        // End vboxOutput

    shboxEBuilder->Add(vboxInput, 1, wxEXPAND | wxRIGHT, 5);
    shboxEBuilder->Add(vboxOutput, 1, wxEXPAND);

    // End shboxEBuilder

    hboxMain->Add(svboxLoopCodeGenerator, 1, wxEXPAND | wxRIGHT, 5);
    hboxMain->Add(shboxEBuilder, 2, wxEXPAND);

    pnlMain->SetSizer(hboxMain);
    hboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect main window events
    Connect(ID_GENERATE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::LoopGenerate));
    Connect(ID_CLEAR_ALL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::LoopClearAll));
    Connect(ID_LOOP_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::LoopCopy));

    Connect(ID_BUILD, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::EBuild));
    Connect(ID_E_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::ECopy));
}

/** Loop Code Generator Events **/

void pgCodeCompressor::LoopGenerate(wxCommandEvent &WXUNUSED(event))
{
}

void pgCodeCompressor::LoopClearAll(wxCommandEvent &WXUNUSED(event))
{
}

void pgCodeCompressor::LoopCopy(wxCommandEvent &WXUNUSED(event))
{
}

/** E Builder Events **/

void pgCodeCompressor::EBuild(wxCommandEvent &WXUNUSED(event))
{
}

void pgCodeCompressor::ECopy(wxCommandEvent &WXUNUSED(event))
{
}

