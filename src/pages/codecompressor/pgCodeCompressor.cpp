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
 * @file pgCodeCompressor.cpp - The program's Code Compressor page.
**/

#include "pgCodeCompressor.h"

// Title of the page:
wxString pgCodeCompressor::Title = _T("Code Compressor");

/** Initialize Identifiers **/

const long pgCodeCompressor::ID_LOOP_GENERATE = wxNewId();
const long pgCodeCompressor::ID_LOOP_CLEAR_ALL = wxNewId();

const long pgCodeCompressor::ID_LOOP_COPY = wxNewId();

const long pgCodeCompressor::ID_PATCH_BUILD = wxNewId();
const long pgCodeCompressor::ID_PATCH_COPY = wxNewId();
const long pgCodeCompressor::ID_PATCH_PASTE = wxNewId();
const long pgCodeCompressor::ID_PATCH_CLEAR = wxNewId();

pgCodeCompressor::pgCodeCompressor(wxWindow *parent)
                : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    hboxMain = new wxBoxSizer(wxHORIZONTAL);

////////////////////////////////////////////////////////////////////////////////

    svboxLoopCodeGenerator = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                                  _T("Loop Code Generator"));

#if USE_OLD_LAYOUT
    ///// Begin hboxBaseCode

    hboxBaseCode = new wxBoxSizer(wxHORIZONTAL);

    lblBaseCode = new wxStaticText(pnlMain, wxID_ANY, _T("Base Code:"));
    txtBaseCode = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxBaseCode->Add(lblBaseCode, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxBaseCode->Add(txtBaseCode, 1, wxEXPAND);

    ///// Begin hboxTotalLoopCount

    hboxTotalLoopCount = new wxBoxSizer(wxHORIZONTAL);

    lblTotalLoopCount = new wxStaticText(pnlMain, wxID_ANY,
                                         _T("Total Loop Count:"));
    txtTotalLoopCount = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxTotalLoopCount->Add(lblTotalLoopCount, 0,
                            wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxTotalLoopCount->Add(txtTotalLoopCount, 1, wxEXPAND);

    ///// Begin hboxOffsetIncrement

    hboxOffsetIncrement = new wxBoxSizer(wxHORIZONTAL);

    lblOffsetIncrement = new wxStaticText(pnlMain, wxID_ANY,
                                          _T("Offset Increment:"));
    txtOffsetIncrement = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxOffsetIncrement->Add(lblOffsetIncrement, 0,
                             wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxOffsetIncrement->Add(txtOffsetIncrement, 1, wxEXPAND);

    ///// Begin hboxValueIncrement

    hboxValueIncrement = new wxBoxSizer(wxHORIZONTAL);

    lblValueIncrement = new wxStaticText(pnlMain, wxID_ANY,
                                         _T("Value Increment:"));
    txtValueIncrement = new wxTextCtrl(pnlMain, wxID_ANY);

    hboxValueIncrement->Add(lblValueIncrement, 0,
                            wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxValueIncrement->Add(txtValueIncrement, 1, wxEXPAND);
#else
    gridLoopCodeGenerator = new wxFlexGridSizer(4, 2, 5, 5);

    // Base Code:
    lblBaseCode = new wxStaticText(pnlMain, wxID_ANY, _T("Base Code:"));
    txtBaseCode = new wxTextCtrl(pnlMain, wxID_ANY);

    // Total Loop Count:
    lblTotalLoopCount = new wxStaticText(pnlMain, wxID_ANY,
                                         _T("Total Loop Count:"));
    txtTotalLoopCount = new wxTextCtrl(pnlMain, wxID_ANY);

    // Offset Increment:
    lblOffsetIncrement = new wxStaticText(pnlMain, wxID_ANY,
                                          _T("Offset Increment:"));
    txtOffsetIncrement = new wxTextCtrl(pnlMain, wxID_ANY);

    // Value Increment:
    lblValueIncrement = new wxStaticText(pnlMain, wxID_ANY,
                                         _T("Value Increment:"));
    txtValueIncrement = new wxTextCtrl(pnlMain, wxID_ANY);

    // Row 1
    gridLoopCodeGenerator->Add(lblBaseCode, 0, wxALIGN_CENTER_VERTICAL);
    gridLoopCodeGenerator->Add(txtBaseCode, 1, wxEXPAND);

    // Row 2
    gridLoopCodeGenerator->Add(lblTotalLoopCount, 0, wxALIGN_CENTER_VERTICAL);
    gridLoopCodeGenerator->Add(txtTotalLoopCount, 1, wxEXPAND);

    // Row 3
    gridLoopCodeGenerator->Add(lblOffsetIncrement, 0, wxALIGN_CENTER_VERTICAL);
    gridLoopCodeGenerator->Add(txtOffsetIncrement, 1, wxEXPAND);

    /// Row 4
    gridLoopCodeGenerator->Add(lblValueIncrement, 0, wxALIGN_CENTER_VERTICAL);
    gridLoopCodeGenerator->Add(txtValueIncrement, 1, wxEXPAND);

    gridLoopCodeGenerator->AddGrowableCol(1, 1);
#endif

    ///// Begin hboxLoopControls

    hboxLoopControls = new wxBoxSizer(wxHORIZONTAL);

    btnGenerate = new wxButton(pnlMain, ID_LOOP_GENERATE, _T("&Generate"));
    btnClearAll = new wxButton(pnlMain, ID_LOOP_CLEAR_ALL, _T("Clear &All"));

    hboxLoopControls->Add(btnGenerate, 1, wxEXPAND | wxRIGHT, 5);
    hboxLoopControls->Add(btnClearAll, 1, wxEXPAND);

    // Now to do the lower part:

    // Divider Line
    slnLoopCodeGenerator = new wxStaticLine(pnlMain);

    // Output Box
    txtLoopOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxTE_MULTILINE | wxHSCROLL);

    txtLoopOutput->SetFont(FIXED_FONT);

    // Copy Button
    btnLoopCopy = new wxButton(pnlMain, ID_LOOP_COPY,
                               _T("&Copy to Clipboard"));

    // Finish up svboxLoopCodeGenerator
#if USE_OLD_LAYOUT
#   warning "USE_OLD_LAYOUT has been deprecated."

    svboxLoopCodeGenerator->Add(hboxBaseCode, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxTotalLoopCount, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxOffsetIncrement, 0,
                                wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(hboxValueIncrement, 0, wxEXPAND | wxBOTTOM, 5);
#else
    svboxLoopCodeGenerator->Add(gridLoopCodeGenerator, 0,
                                wxEXPAND | wxBOTTOM, 5);
#endif
    svboxLoopCodeGenerator->Add(hboxLoopControls, 0, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(slnLoopCodeGenerator, 0,
                                wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(txtLoopOutput, 1, wxEXPAND | wxBOTTOM, 5);
    svboxLoopCodeGenerator->Add(btnLoopCopy, 0, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    shboxPatchCodeBuilder = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                                 _T("Patch Code Builder"));

    ///// Begin vboxInput

    vboxInput = new wxBoxSizer(wxVERTICAL);

    lblInput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Input"));
    txtInput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                              wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE | wxHSCROLL);

    txtInput->SetFont(FIXED_FONT);

    // hbox to align the buttons in here
    hboxInputButtons = new wxBoxSizer(wxHORIZONTAL);
    btnPaste = new wxButton(pnlMain, ID_PATCH_PASTE, _T("&Paste"));
    btnBuild = new wxButton(pnlMain, ID_PATCH_BUILD, _T("&Build"));
    hboxInputButtons->Add(btnPaste, 1, wxEXPAND | wxRIGHT, 5);
    hboxInputButtons->Add(btnBuild, 1, wxEXPAND);

    vboxInput->Add(lblInput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxInput->Add(txtInput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxInput->Add(hboxInputButtons, 0, wxEXPAND);

    ///// Begin vboxOutput

    vboxOutput = new wxBoxSizer(wxVERTICAL);

    lblOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));
    txtOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxHSCROLL);

    txtOutput->SetFont(FIXED_FONT);

    // hbox to align the buttons in here
    hboxOutputButtons = new wxBoxSizer(wxHORIZONTAL);
    btnPatchCopy = new wxButton(pnlMain, ID_PATCH_COPY, _T("C&opy"));
    btnPatchClear = new wxButton(pnlMain, ID_PATCH_CLEAR, _T("C&lear"));
    hboxOutputButtons->Add(btnPatchCopy, 1, wxEXPAND | wxRIGHT, 5);
    hboxOutputButtons->Add(btnPatchClear, 1, wxEXPAND);

    vboxOutput->Add(lblOutput, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxOutput->Add(txtOutput, 1, wxEXPAND | wxBOTTOM, 5);
    vboxOutput->Add(hboxOutputButtons, 0, wxEXPAND);

    // Finish up shboxPatchCodeBuilder
    shboxPatchCodeBuilder->Add(vboxInput, 1, wxEXPAND | wxRIGHT, 5);
    shboxPatchCodeBuilder->Add(vboxOutput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    hboxMain->Add(svboxLoopCodeGenerator, 2, wxEXPAND | wxRIGHT, 5);
    hboxMain->Add(shboxPatchCodeBuilder, 3, wxEXPAND);

    pnlMain->SetSizer(hboxMain);
    hboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect main window events
    Connect(ID_LOOP_GENERATE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::LoopGenerate));
    Connect(ID_LOOP_CLEAR_ALL, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::LoopClearAll));

    Connect(ID_LOOP_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::LoopCopy));

    Connect(ID_PATCH_PASTE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::PatchPaste));
    Connect(ID_PATCH_BUILD, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::PatchBuild));
    Connect(ID_PATCH_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::PatchCopy));
    Connect(ID_PATCH_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeCompressor::PatchClear));
}

/** Main Algorithms **/

void pgCodeCompressor::LoopGenerate(wxCommandEvent &WXUNUSED(event))
{
    // Pull in all of the inputs and trim them
    wxString baseCode = txtBaseCode->GetValue().Trim().Trim(false);
    wxString totalLoopCount = txtTotalLoopCount->GetValue().Trim().Trim(false);
    wxString offsetIncrement =
        txtOffsetIncrement->GetValue().Trim().Trim(false);
    wxString valueIncrement = txtValueIncrement->GetValue().Trim().Trim(false);

    // Error testing
    if (baseCode.IsEmpty())
    {
        wxMessageBox(_T("There is no Base Code input."), _T("Error"));
        return;
    }
    if (totalLoopCount.IsEmpty())
    {
        wxMessageBox(_T("There is no Total Loop Count input."), _T("Error"));
        return;
    }
    if (offsetIncrement.IsEmpty())
    {
        wxMessageBox(_T("There is no Offset Increment input."), _T("Error"));
        return;
    }

    try
    {
        txtLoopOutput->SetValue(LoopCodeGenerator::Generate(
            CodeParser::Beautify(baseCode),
            totalLoopCount,
            offsetIncrement,
            valueIncrement
        ));
    }
    catch (wxString msg)
    {
        wxMessageBox(msg, _T("Error"));
    }
}

void pgCodeCompressor::PatchBuild(wxCommandEvent &WXUNUSED(event))
{
    wxString inputval = txtInput->GetValue();

    // Error testing
    if (inputval.Trim().Trim(false).IsEmpty())
    {
        wxMessageBox(_T("There is no code input."), _T("Error"));
        return;
    }

    try
    {
        txtOutput->SetValue(PatchCodeBuilder::Build(inputval));
    }
    catch (wxString msg)
    {
        wxMessageBox(msg, _T("Error"));
    }
}

/** Loop Code Generator GUI Events **/

void pgCodeCompressor::LoopClearAll(wxCommandEvent &WXUNUSED(event))
{
    // Don't bother if they're all empty
    if (txtBaseCode->IsEmpty() && txtTotalLoopCount->IsEmpty() &&
        txtOffsetIncrement->IsEmpty() && txtValueIncrement->IsEmpty())
        return;

    int dlgresult = wxMessageBox(
        _T("Are you sure that you would like to clear the loop code input?"),
        _T("Clear Loop Code Input?"), wxYES_NO
    );

    if (dlgresult == wxYES)
    {
        txtBaseCode->SetValue(_T(""));
        txtTotalLoopCount->SetValue(_T(""));
        txtOffsetIncrement->SetValue(_T(""));
        txtValueIncrement->SetValue(_T(""));
    }
}

void pgCodeCompressor::LoopCopy(wxCommandEvent &WXUNUSED(event))
{
    wxString str = txtLoopOutput->GetValue();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("Loop output copied successfully."),
                         _T("Success"));
    }
}

/** E Builder GUI Events **/

void pgCodeCompressor::PatchPaste(wxCommandEvent &WXUNUSED(event))
{
    // Prompt them if the input box isn't empty.
    int dlgresult = !txtInput->GetValue().IsEmpty()
                    ? wxMessageBox(
                        _T("\
Are you sure that you would like to paste in a new input?\n\
This will overwrite any current data in the input box.\
"),
                        _T("Overwrite Input?"), wxYES_NO
                    )
                    : wxYES;

    if (dlgresult == wxYES)
        txtInput->SetValue(Clipboard::GetClipboard());
}
void pgCodeCompressor::PatchCopy(wxCommandEvent &WXUNUSED(event))
{
    wxString str = txtOutput->GetValue();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("Code output copied successfully."),
                         _T("Success"));
    }
}
void pgCodeCompressor::PatchClear(wxCommandEvent &WXUNUSED(event))
{    int dlgresult = wxMessageBox(
        _T("\
Are you sure that you would like to clear the input and output boxes?\
"),
        _T("Clear Input/Output?"), wxYES_NO
    );

    if (dlgresult == wxYES)
    {
        txtInput->SetValue(_T(""));
        txtOutput->SetValue(_T(""));
    }
}
