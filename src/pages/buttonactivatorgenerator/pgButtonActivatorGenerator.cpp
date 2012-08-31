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
 * @file pgButtonActivatorGenerator.cpp -
 *           The program's Button Activator Generator page.
**/

#include "pgButtonActivatorGenerator.h"

// Title of the page:
wxString pgButtonActivatorGenerator::Title = _T("Button Activator Generator");

/** Initialize Identifiers **/

// GBA Buttons
const long pgButtonActivatorGenerator::ID_A = wxNewId();
const long pgButtonActivatorGenerator::ID_B = wxNewId();
const long pgButtonActivatorGenerator::ID_SELECT = wxNewId();
const long pgButtonActivatorGenerator::ID_START = wxNewId();
const long pgButtonActivatorGenerator::ID_RIGHT = wxNewId();
const long pgButtonActivatorGenerator::ID_LEFT = wxNewId();
const long pgButtonActivatorGenerator::ID_UP = wxNewId();
const long pgButtonActivatorGenerator::ID_DOWN = wxNewId();
const long pgButtonActivatorGenerator::ID_R = wxNewId();
const long pgButtonActivatorGenerator::ID_L = wxNewId();

// NDS Buttons
const long pgButtonActivatorGenerator::ID_X = wxNewId();
const long pgButtonActivatorGenerator::ID_Y = wxNewId();
const long pgButtonActivatorGenerator::ID_DEBUG = wxNewId();
const long pgButtonActivatorGenerator::ID_FOLDED = wxNewId();

// Interface Buttons
const long pgButtonActivatorGenerator::ID_CLEAR = wxNewId();
const long pgButtonActivatorGenerator::ID_COPY = wxNewId();
const long pgButtonActivatorGenerator::ID_PASTE = wxNewId();

// Code Input Textbox
const long pgButtonActivatorGenerator::ID_CODE_INPUT = wxNewId();

pgButtonActivatorGenerator::pgButtonActivatorGenerator(wxWindow *parent)
                          : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    hboxMain = new wxBoxSizer(wxHORIZONTAL);

////////////////////////////////////////////////////////////////////////////////

    vboxCodeInput = new wxBoxSizer(wxVERTICAL);

    lblCodeInput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Input"));
    txtCodeInput = new wxTextCtrl(pnlMain, ID_CODE_INPUT, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE | wxHSCROLL);

    vboxCodeInput->Add(lblCodeInput, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxCodeInput->Add(txtCodeInput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    vboxControls = new wxBoxSizer(wxVERTICAL);

    ///// Begin svboxButtons

    svboxButtons = new wxStaticBoxSizer(wxVERTICAL, pnlMain, _T("Buttons"));

    // In here we have gridButtons with the checkboxes
    gridButtons = new wxFlexGridSizer(7, 2, 5, 15);

    chkA = new wxCheckBox(pnlMain, ID_A, _T("&A"));
    chkB = new wxCheckBox(pnlMain, ID_B, _T("&B"));
    chkX = new wxCheckBox(pnlMain, ID_X, _T("&X"));
    chkY = new wxCheckBox(pnlMain, ID_Y, _T("&Y"));
    chkL = new wxCheckBox(pnlMain, ID_L, _T("&L"));
    chkR = new wxCheckBox(pnlMain, ID_R, _T("&R"));
    chkLeft = new wxCheckBox(pnlMain, ID_LEFT, _T("L&eft"));
    chkRight = new wxCheckBox(pnlMain, ID_RIGHT, _T("R&ight"));
    chkUp = new wxCheckBox(pnlMain, ID_UP, _T("&Up"));
    chkDown = new wxCheckBox(pnlMain, ID_DOWN, _T("&Down"));
    chkStart = new wxCheckBox(pnlMain, ID_START, _T("&Start"));
    chkSelect = new wxCheckBox(pnlMain, ID_SELECT, _T("Selec&t"));
    chkFolded = new wxCheckBox(pnlMain, ID_FOLDED, _T("&Folded"));
    chkDebug = new wxCheckBox(pnlMain, ID_DEBUG, _T("Deb&ug"));

    gridButtons->Add(chkA, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkB, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkX, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkY, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkL, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkR, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkLeft, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkRight, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkUp, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkDown, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkStart, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkSelect, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkFolded, 0, wxALIGN_CENTER_VERTICAL);
    gridButtons->Add(chkDebug, 0, wxALIGN_CENTER_VERTICAL);

    gridButtons->AddGrowableCol(0, 1);
    gridButtons->AddGrowableCol(1, 1);

    gridButtons->AddGrowableRow(0, 1);
    gridButtons->AddGrowableRow(1, 1);
    gridButtons->AddGrowableRow(2, 1);
    gridButtons->AddGrowableRow(3, 1);
    gridButtons->AddGrowableRow(4, 1);
    gridButtons->AddGrowableRow(5, 1);
    gridButtons->AddGrowableRow(6, 1);

    svboxButtons->Add(gridButtons, 1, wxEXPAND);

    ///// End svboxButtons

    // Interface Buttons
    btnClear = new wxButton(pnlMain, ID_CLEAR, _T("Clear"));
    btnCopy = new wxButton(pnlMain, ID_COPY, _T("Copy"));
    btnPaste = new wxButton(pnlMain, ID_PASTE, _T("Paste"));

    // We got another wxFlexGridSizer for the TST values.

    slnControls = new wxStaticLine(pnlMain);

    gridTstValues = new wxFlexGridSizer(2, 2, 5, 5);

    lblGbaTst = new wxStaticText(pnlMain, wxID_ANY, _T("GBA TST Value:"));
    txtGbaTst = new wxTextCtrl(pnlMain, wxID_ANY);
    lblNdsTst = new wxStaticText(pnlMain, wxID_ANY, _T("NDS TST Value:"));
    txtNdsTst = new wxTextCtrl(pnlMain, wxID_ANY);

    gridTstValues->Add(lblGbaTst, 0, wxALIGN_CENTER_VERTICAL);
    gridTstValues->Add(txtGbaTst, 1, wxEXPAND);
    gridTstValues->Add(lblNdsTst, 0, wxALIGN_CENTER_VERTICAL);
    gridTstValues->Add(txtNdsTst, 1, wxEXPAND);

    gridTstValues->AddGrowableCol(1, 1);

    vboxControls->Add(svboxButtons, 5, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(btnClear, 1, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(btnCopy, 1, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(btnPaste, 1, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(slnControls, 0, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(gridTstValues, 0, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    vboxCodeOutput = new wxBoxSizer(wxVERTICAL);

    lblCodeOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));
    txtCodeOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxTE_MULTILINE | wxHSCROLL);

    vboxCodeOutput->Add(lblCodeOutput, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxCodeOutput->Add(txtCodeOutput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    hboxMain->Add(vboxCodeInput, 4, wxEXPAND | wxRIGHT, 5);
    hboxMain->Add(vboxControls, 3, wxEXPAND | wxRIGHT, 5);
    hboxMain->Add(vboxCodeOutput, 4, wxEXPAND);

    pnlMain->SetSizer(hboxMain);
    hboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Instantiate the controller
    mController = new ButtonActivatorGenerator(txtCodeInput, txtCodeOutput,
                                               txtGbaTst, txtNdsTst);
    // Have it set up the output boxes right away
    mController->UpdateOutput();

    /** Connect Main Window Events **/

    // GBA Buttons
    Connect(ID_A, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleA));
    Connect(ID_B, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleB));
    Connect(ID_SELECT, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleSelect));
    Connect(ID_START, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleStart));
    Connect(ID_RIGHT, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleRight));
    Connect(ID_LEFT, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleLeft));
    Connect(ID_UP, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleUp));
    Connect(ID_DOWN, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleDown));
    Connect(ID_R, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleR));
    Connect(ID_L, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleL));

    // NDS Buttons
    Connect(ID_X, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleX));
    Connect(ID_Y, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleY));
    Connect(ID_DEBUG, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleDebug));
    Connect(ID_FOLDED, wxEVT_COMMAND_CHECKBOX_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ToggleFolded));

    // Other Controls
    Connect(ID_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Copy));
    Connect(ID_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Clear));
    Connect(ID_PASTE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Paste));

    // Code Input Text Changed
    Connect(ID_CODE_INPUT, wxEVT_COMMAND_TEXT_UPDATED,
            wxCommandEventHandler(pgButtonActivatorGenerator::CheckInput));
}

/** Events **/

void pgButtonActivatorGenerator::ToggleA(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(A);
}
void pgButtonActivatorGenerator::ToggleB(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(B);
}
void pgButtonActivatorGenerator::ToggleSelect(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Select);
}
void pgButtonActivatorGenerator::ToggleStart(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Start);
}
void pgButtonActivatorGenerator::ToggleRight(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Right);
}
void pgButtonActivatorGenerator::ToggleLeft(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Left);
}
void pgButtonActivatorGenerator::ToggleUp(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Up);
}
void pgButtonActivatorGenerator::ToggleDown(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Down);
}
void pgButtonActivatorGenerator::ToggleR(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(R);
}
void pgButtonActivatorGenerator::ToggleL(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(L);
}
void pgButtonActivatorGenerator::ToggleX(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(X);
}
void pgButtonActivatorGenerator::ToggleY(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Y);
}
void pgButtonActivatorGenerator::ToggleDebug(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Debug);
}
void pgButtonActivatorGenerator::ToggleFolded(wxCommandEvent &WXUNUSED(event))
{
    mController->Toggle(Folded);
}

void pgButtonActivatorGenerator::Clear(wxCommandEvent &WXUNUSED(event))
{
    int dlgresult = wxMessageBox(
        _T("Are you sure that you would like to clear everything?"),
        _T("Clear Window?"), wxYES_NO
    );

    // Bail if they didn't say yes
    if (dlgresult != wxYES)
        return;

    // Reset all of the checkboxes...

    // GBA Buttons
    chkA->SetValue(false);
    chkB->SetValue(false);
    chkSelect->SetValue(false);
    chkStart->SetValue(false);
    chkRight->SetValue(false);
    chkLeft->SetValue(false);
    chkUp->SetValue(false);
    chkDown->SetValue(false);
    chkR->SetValue(false);
    chkL->SetValue(false);

    // NDS Buttons
    chkX->SetValue(false);
    chkY->SetValue(false);
    chkDebug->SetValue(false);
    chkFolded->SetValue(false);

    // Reset the controller and the outputs
    mController->Clear();
}
void pgButtonActivatorGenerator::Copy(wxCommandEvent &WXUNUSED(event))
{
    wxString str = txtCodeOutput->GetValue();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("Code output copied successfully."),
                         _T("Success"));
    }
}
void pgButtonActivatorGenerator::Paste(wxCommandEvent &WXUNUSED(event))
{
    // Prompt them if the input box isn't empty.
    int dlgresult = !txtCodeInput->GetValue().IsEmpty()
                    ? wxMessageBox(
                        _T("\
Are you sure that you would like to paste in a new input?\n\
This will overwrite any current data in the code input box.\
"),
                        _T("Overwrite Code Input?"), wxYES_NO
                    )
                    : wxYES;

    if (dlgresult == wxYES)
        txtCodeInput->SetValue(Clipboard::GetClipboard());
}

void pgButtonActivatorGenerator::CheckInput(wxCommandEvent &WXUNUSED(event))
{
    mController->UpdateOutput();
}

