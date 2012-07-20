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

// Other Controls
const long pgButtonActivatorGenerator::ID_CLEAR = wxNewId();

const long pgButtonActivatorGenerator::ID_COPY_AR = wxNewId();
const long pgButtonActivatorGenerator::ID_COPY_TST = wxNewId();

pgButtonActivatorGenerator::pgButtonActivatorGenerator(wxWindow *parent)
                          : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    vboxMain = new wxBoxSizer(wxVERTICAL);

////////////////////////////////////////////////////////////////////////////////

    hboxUpper = new wxBoxSizer(wxHORIZONTAL);

    ///// Begin vboxButtons - This contains two wxStaticBoxSizers.

    vboxButtons = new wxBoxSizer(wxVERTICAL);

    ///// svboxGbaButtons

    svboxGbaButtons = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                           _T("GBA Buttons"));

    // In here we have gridGbaButtons with the checkboxes
    gridGbaButtons = new wxFlexGridSizer(2, 5, 5, 5);

    chkA = new wxCheckBox(pnlMain, ID_A, _T("&A"));
    chkUp = new wxCheckBox(pnlMain, ID_UP, _T("&Up"));
    chkL = new wxCheckBox(pnlMain, ID_L, _T("&L"));
    chkR = new wxCheckBox(pnlMain, ID_R, _T("&R"));
    chkStart = new wxCheckBox(pnlMain, ID_START, _T("&Start"));
    chkB = new wxCheckBox(pnlMain, ID_B, _T("&B"));
    chkDown = new wxCheckBox(pnlMain, ID_DOWN, _T("&Down"));
    chkLeft = new wxCheckBox(pnlMain, ID_LEFT, _T("L&eft"));
    chkRight = new wxCheckBox(pnlMain, ID_RIGHT, _T("R&ight"));
    chkSelect = new wxCheckBox(pnlMain, ID_START, _T("Selec&t"));

    gridGbaButtons->Add(chkA);
    gridGbaButtons->Add(chkUp);
    gridGbaButtons->Add(chkL);
    gridGbaButtons->Add(chkR);
    gridGbaButtons->Add(chkStart);
    gridGbaButtons->Add(chkB);
    gridGbaButtons->Add(chkDown);
    gridGbaButtons->Add(chkLeft);
    gridGbaButtons->Add(chkRight);
    gridGbaButtons->Add(chkSelect);

    gridGbaButtons->AddGrowableCol(0, 2);
    gridGbaButtons->AddGrowableCol(1, 3);
    gridGbaButtons->AddGrowableCol(2, 3);
    gridGbaButtons->AddGrowableCol(3, 3);
    gridGbaButtons->AddGrowableCol(4, 3);

    svboxGbaButtons->Add(gridGbaButtons, 1, wxEXPAND);

    ///// shboxNdsButtons

    shboxNdsButtons = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                           _T("NDS Buttons"));

    chkX = new wxCheckBox(pnlMain, ID_X, _T("&X"));
    chkY = new wxCheckBox(pnlMain, ID_Y, _T("&Y"));
    chkFolded = new wxCheckBox(pnlMain, ID_FOLDED, _T("NDS &Folded"));
    chkDebug = new wxCheckBox(pnlMain, ID_DEBUG, _T("Deb&ug Button"));

    shboxNdsButtons->Add(chkX, 1, wxALIGN_CENTER_VERTICAL);
    shboxNdsButtons->Add(chkY, 1, wxALIGN_CENTER_VERTICAL);
    shboxNdsButtons->Add(chkFolded, 2, wxALIGN_CENTER_VERTICAL);
    shboxNdsButtons->Add(chkDebug, 2, wxALIGN_CENTER_VERTICAL);

    vboxButtons->Add(svboxGbaButtons, 0, wxEXPAND | wxBOTTOM, 5);
    vboxButtons->Add(shboxNdsButtons, 0, wxEXPAND);

    ///// End vboxButtons

    /**
     * 2012-07-17 gbchaosmaster - btnClear height hack
     *
     * btnClear is an interesting one. If I just place it into the hbox, it
     * sits there just fine, but it overhangs a little bit on the top because
     * of the height of the label.
     *
     * My remedy was to put the button into a vertical box sizer and then pad
     * it on top with half the height of a random label.
    **/

    vboxClearButton = new wxBoxSizer(wxVERTICAL);

    btnClear = new wxButton(pnlMain, ID_CLEAR, _T("&Clear"));

    wxStaticText *lblHeightTest = new wxStaticText(
        pnlMain, wxID_ANY, _T("")
    );
    vboxClearButton->Add(
        btnClear, 1, wxEXPAND | wxTOP,
        (int)(lblHeightTest->GetClientSize().GetHeight() / 2)
    );
    delete lblHeightTest;

    hboxUpper->Add(vboxButtons, 1, wxEXPAND | wxRIGHT, 5);
    hboxUpper->Add(vboxClearButton, 0, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    // The rest of the controls are top-level.

    // Separator between the sections:
    slnSeparator = new wxStaticLine(pnlMain);

    // The output section

    lblCodeOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));

    txtArOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                 wxDefaultPosition, wxDefaultSize,
                                 wxTE_MULTILINE | wxHSCROLL);
    btnCopyAr = new wxButton(pnlMain, ID_COPY_AR, _T("Co&py AR Code"));

    txtTstOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE);
    btnCopyTst = new wxButton(pnlMain, ID_COPY_TST, _T("Copy TST &Value"));

////////////////////////////////////////////////////////////////////////////////

    vboxMain->Add(hboxUpper, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(slnSeparator, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(lblCodeOutput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxMain->Add(txtArOutput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(btnCopyAr, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(txtTstOutput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(btnCopyTst, 0, wxEXPAND);

    pnlMain->SetSizer(vboxMain);
    vboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Instantiate the controller
    mController = new ButtonActivatorGenerator(txtArOutput, txtTstOutput);
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
    Connect(ID_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Clear));

    Connect(ID_COPY_AR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::CopyAr));
    Connect(ID_COPY_TST, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::CopyTst));
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

// :TODO: 2012-07-17 gbchaosmaster - Abstract these further.
// CopyAr() and CopyTst() are ridiculously similar. Implement similar
// functionality into the Clipboard class.
void pgButtonActivatorGenerator::CopyAr(wxCommandEvent &WXUNUSED(event))
{
    wxString str = txtArOutput->GetValue();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("AR output copied successfully."),
                         _T("Success"));
    }
}
void pgButtonActivatorGenerator::CopyTst(wxCommandEvent &WXUNUSED(event))
{
    wxString str = txtTstOutput->GetValue();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("TST output copied successfully."),
                         _T("Success"));
    }
}

