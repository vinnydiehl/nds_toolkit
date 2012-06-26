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
 * @file pgButtonActivatorGenerator.cpp -
 *           The program's Button Activator Generator page.
**/

#include "pgButtonActivatorGenerator.h"

// Title of the page:
wxString pgButtonActivatorGenerator::Title = _T("Button Activator Generator");

/** Initialize Identifiers **/

const long pgButtonActivatorGenerator::ID_CHANGE_TYPE = wxNewId();

const long pgButtonActivatorGenerator::ID_GENERATE = wxNewId();

const long pgButtonActivatorGenerator::ID_COPY = wxNewId();
const long pgButtonActivatorGenerator::ID_CLEAR = wxNewId();

pgButtonActivatorGenerator::pgButtonActivatorGenerator(wxWindow *parent)
                          : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    vboxMain = new wxBoxSizer(wxVERTICAL);

////////////////////////////////////////////////////////////////////////////////

    gridGroups = new wxFlexGridSizer(2, 2, 5, 5);

    ///// Begin svboxButtonType

    svboxButtonType = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                           _T("Button Type"));

    radGba = new wxRadioButton(pnlMain, ID_CHANGE_TYPE, _T("&GBA"),
                               wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radNds = new wxRadioButton(pnlMain, ID_CHANGE_TYPE, _T("&NDS"));

    // :TODO: 2012-06-16 gbchaosmaster - Check cross-platform layout looks
    // I'm putting some padding to the right of these because it seems to look
    // better, it's a little too close to the edge of the static box without
    // it. Check out what this looks like on other platforms.
    svboxButtonType->Add(radGba, 0, wxBOTTOM | wxRIGHT, 5);
    svboxButtonType->Add(radNds, 0, wxRIGHT, 5);

    ///// Begin svboxGbaButtons

    svboxGbaButtons = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                           _T("GBA Buttons"));

    // In here we have gridGbaButtons with the checkboxes
    gridGbaButtons = new wxFlexGridSizer(2, 5, 5, 5);

    chkA = new wxCheckBox(pnlMain, wxID_ANY, _T("&A"));
    chkUp = new wxCheckBox(pnlMain, wxID_ANY, _T("&Up"));
    chkL = new wxCheckBox(pnlMain, wxID_ANY, _T("&L"));
    chkR = new wxCheckBox(pnlMain, wxID_ANY, _T("&R"));
    chkStart = new wxCheckBox(pnlMain, wxID_ANY, _T("&Start"));
    chkB = new wxCheckBox(pnlMain, wxID_ANY, _T("&B"));
    chkDown = new wxCheckBox(pnlMain, wxID_ANY, _T("&Down"));
    chkLeft = new wxCheckBox(pnlMain, wxID_ANY, _T("L&eft"));
    chkRight = new wxCheckBox(pnlMain, wxID_ANY, _T("R&ight"));
    chkSelect = new wxCheckBox(pnlMain, wxID_ANY, _T("Selec&t"));

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

    ///// Begin svboxTarget

    svboxTarget = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                       _T("Target"));

    radArCode = new wxRadioButton(pnlMain, wxID_ANY, _T("AR &Code"),
                                  wxDefaultPosition, wxDefaultSize,
                                  wxRB_GROUP);
    radTstValue = new wxRadioButton(pnlMain, wxID_ANY, _T("TST &Value"));

    // See svboxButtonType for comment on the 5px padding to the right
    svboxTarget->Add(radArCode, 0, wxBOTTOM | wxRIGHT, 5);
    svboxTarget->Add(radTstValue, 0, wxRIGHT, 5);

    ///// Begin shboxNdsButtons

    shboxNdsButtons = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                           _T("NDS Buttons"));

    chkX = new wxCheckBox(pnlMain, wxID_ANY, _T("&X"));
    chkY = new wxCheckBox(pnlMain, wxID_ANY, _T("&Y"));
    chkNdsFolded = new wxCheckBox(pnlMain, wxID_ANY, _T("NDS &Folded"));
    chkDebugButton = new wxCheckBox(pnlMain, wxID_ANY, _T("Deb&ug Button"));

    shboxNdsButtons->Add(chkX, 1, wxALIGN_CENTER_VERTICAL);
    shboxNdsButtons->Add(chkY, 1, wxALIGN_CENTER_VERTICAL);
    shboxNdsButtons->Add(chkNdsFolded, 2, wxALIGN_CENTER_VERTICAL);
    shboxNdsButtons->Add(chkDebugButton, 2, wxALIGN_CENTER_VERTICAL);

    // These are all disabled to start
    chkX->Disable();
    chkY->Disable();
    chkNdsFolded->Disable();
    chkDebugButton->Disable();

    // Row 1
    gridGroups->Add(svboxButtonType, 0, wxEXPAND);
    gridGroups->Add(svboxGbaButtons, 1, wxEXPAND);

    // Row 2
    gridGroups->Add(svboxTarget, 0, wxEXPAND);
    gridGroups->Add(shboxNdsButtons, 1, wxEXPAND);

    gridGroups->AddGrowableCol(1, 1);

////////////////////////////////////////////////////////////////////////////////

    // We have some top-level controls here

    btnGenerate = new wxButton(pnlMain, ID_GENERATE,
                               _T("Generate Acti&vator"));

    slnSeparator = new wxStaticLine(pnlMain);

    lblCodeOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));
    txtCodeOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxTE_MULTILINE | wxHSCROLL);

////////////////////////////////////////////////////////////////////////////////

    hboxCodeOutputControls = new wxBoxSizer(wxHORIZONTAL);

    // Shit, I ran out of shortcut characters to use for these
    btnCopy = new wxButton(pnlMain, ID_COPY, _T("Copy"));
    btnClear = new wxButton(pnlMain, ID_CLEAR, _T("Clear"));

    hboxCodeOutputControls->Add(btnCopy, 1, wxEXPAND | wxRIGHT, 5);
    hboxCodeOutputControls->Add(btnClear, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    vboxMain->Add(gridGroups, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(btnGenerate, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(slnSeparator, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(lblCodeOutput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxMain->Add(txtCodeOutput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(hboxCodeOutputControls, 0, wxEXPAND);

    pnlMain->SetSizer(vboxMain);
    vboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect main window events
    Connect(ID_CHANGE_TYPE, wxEVT_COMMAND_RADIOBUTTON_SELECTED,
            wxCommandEventHandler(pgButtonActivatorGenerator::ChangeType));
    Connect(ID_GENERATE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Generate));
    Connect(ID_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Copy));
    Connect(ID_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgButtonActivatorGenerator::Clear));
}

/** Events **/

void pgButtonActivatorGenerator::ChangeType(wxCommandEvent &WXUNUSED(event))
{
    /**
     * Activate the NDS checkboxes when the NDS radio button is selected,
     * and the GBA checkboxes when the GBA radio is selected. Disable the
     * other checkboxes.
    **/

    if (radNds->GetValue())
    {
        // Enable NDS
        chkX->Enable();
        chkY->Enable();
        chkNdsFolded->Enable();
        chkDebugButton->Enable();

        // Disable GBA
        chkA->Disable();
        chkUp->Disable();
        chkL->Disable();
        chkR->Disable();
        chkStart->Disable();
        chkB->Disable();
        chkDown->Disable();
        chkLeft->Disable();
        chkRight->Disable();
        chkSelect->Disable();
    }
    else
    {
        // Enable GBA
        chkA->Enable();
        chkUp->Enable();
        chkL->Enable();
        chkR->Enable();
        chkStart->Enable();
        chkB->Enable();
        chkDown->Enable();
        chkLeft->Enable();
        chkRight->Enable();
        chkSelect->Enable();

        // Disable NDS
        chkX->Disable();
        chkY->Disable();
        chkNdsFolded->Disable();
        chkDebugButton->Disable();
    }
}

void pgButtonActivatorGenerator::Generate(wxCommandEvent &WXUNUSED(event))
{
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
void pgButtonActivatorGenerator::Clear(wxCommandEvent &WXUNUSED(event))
{
    int dlgresult = wxMessageBox(
        _T("Are you sure that you would like to clear the code output?"),
        _T("Clear Output?"), wxYES_NO
    );

    if (dlgresult == wxYES)
        txtCodeOutput->SetValue(_T(""));
}

