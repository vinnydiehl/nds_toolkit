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
 * @file pgCodeBeautifier.cpp - The program's Code Beautifier page.
**/

#include "pgCodeBeautifier.h"

// Title of the page:
wxString pgCodeBeautifier::Title = _T("Code Beautifier");

/** Initialize Identifiers **/

const long pgCodeBeautifier::ID_BEAUTIFY = wxNewId();

const long pgCodeBeautifier::ID_CLEAR = wxNewId();
const long pgCodeBeautifier::ID_COPY = wxNewId();
const long pgCodeBeautifier::ID_PASTE = wxNewId();

pgCodeBeautifier::pgCodeBeautifier(wxWindow *parent)
                : wxPanel(parent, wxID_ANY)
{
    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    hboxMain = new wxBoxSizer(wxHORIZONTAL);

////////////////////////////////////////////////////////////////////////////////

    vboxCodeInput = new wxBoxSizer(wxVERTICAL);

    lblCodeInput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Input"));
    txtCodeInput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE | wxHSCROLL);

    txtCodeInput->SetFont(FIXED_FONT);

    vboxCodeInput->Add(lblCodeInput, 0,
                       wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxCodeInput->Add(txtCodeInput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    vboxControls = new wxBoxSizer(wxVERTICAL);

    ///// Begin svboxOptions/vboxOptions

    /**
     * The Options box is a wxBoxSizer within a wxStaticBoxSizer. The
     * checkboxes are all in the former, which is then added to the latter
     * with the wxALIGN_CENTER_HORIZONTAL flag, thus keeping the checkboxes
     * aligned in the center of the static box, but keeping them aligned
     * on the left with respect to each other.
    **/

    svboxOptions = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                        _T("Options"));

    vboxOptions = new wxBoxSizer(wxVERTICAL);

    chkUpperHex = new wxCheckBox(pnlMain, wxID_ANY, _T("&Uppercase Hex"));
    chkStripBlankLines = new wxCheckBox(pnlMain, wxID_ANY,
                                        _T("&Strip Blank Lines"));
    chkStripComments = new wxCheckBox(pnlMain, wxID_ANY,
                                      _T("S&trip Comments"));

    // Checked by default:
    chkUpperHex->SetValue(true);

    vboxOptions->Add(chkUpperHex, 0, wxBOTTOM, 5);
    vboxOptions->Add(chkStripBlankLines, 0, wxBOTTOM, 5);
    vboxOptions->Add(chkStripComments);

    svboxOptions->Add(vboxOptions, 0, wxALIGN_CENTER_HORIZONTAL);

    ///// btnBeautify is top-level

    btnBeautify = new wxButton(pnlMain, ID_BEAUTIFY, _T("&Beautify"));

    ///// Begin svboxTools

    svboxTools = new wxStaticBoxSizer(wxVERTICAL, pnlMain, _T("Tools"));

    btnClear = new wxButton(pnlMain, ID_CLEAR, _T("C&lear"));
    btnCopy = new wxButton(pnlMain, ID_COPY, _T("&Copy"));
    btnPaste = new wxButton(pnlMain, ID_PASTE, _T("&Paste"));

    svboxTools->Add(btnClear, 0, wxEXPAND | wxBOTTOM, 3);
    svboxTools->Add(btnCopy, 0, wxEXPAND | wxBOTTOM, 3);
    svboxTools->Add(btnPaste, 0, wxEXPAND);

    // Finish up vboxControls
    vboxControls->Add(svboxOptions, 0, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(btnBeautify, 1, wxEXPAND | wxBOTTOM, 5);
    vboxControls->Add(svboxTools, 0, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    vboxCodeOutput = new wxBoxSizer(wxVERTICAL);

    lblCodeOutput = new wxStaticText(pnlMain, wxID_ANY, _T("Code Output"));
    txtCodeOutput = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                   wxDefaultPosition, wxDefaultSize,
                                   wxTE_MULTILINE | wxHSCROLL);

    txtCodeOutput->SetFont(FIXED_FONT);

    vboxCodeOutput->Add(lblCodeOutput, 0,
                        wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxCodeOutput->Add(txtCodeOutput, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    hboxMain->Add(vboxCodeInput, 2, wxEXPAND | wxRIGHT, 5);
    hboxMain->Add(vboxControls, 1, wxEXPAND | wxRIGHT, 5);
    hboxMain->Add(vboxCodeOutput, 2, wxEXPAND);

    pnlMain->SetSizer(hboxMain);
    hboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect Code Porter events
    Connect(ID_BEAUTIFY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeBeautifier::Beautify));

    Connect(ID_CLEAR, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeBeautifier::Clear));
    Connect(ID_COPY, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeBeautifier::Copy));
    Connect(ID_PASTE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgCodeBeautifier::Paste));
}

void pgCodeBeautifier::Beautify(wxCommandEvent &WXUNUSED(event))
{
    wxString inputval = txtCodeInput->GetValue();

    // Test for things that would make us want to bail.
    if (inputval.Trim().Trim(false).IsEmpty())
    {
        wxMessageBox(_T("There is no code input."), _T("Error"));
        return;
    }

    // Gather all of the flags from the checkboxes.
    int flags = 0x0;
    if (chkUpperHex->GetValue())
        flags |= UPPER_HEX;
    if (chkStripBlankLines->GetValue())
        flags |= STRIP_BLANK_LINES;
    if (chkStripComments->GetValue())
        flags |= STRIP_COMMENTS;

    // Run CodeParser::Beautify() and get the result...
    wxString result = CodeParser::Beautify(txtCodeInput->GetValue(), flags);

    // Test the result to see if we got an invalid, if so, error.
    if (result == _T("Invalid"))
    {
        wxMessageBox(_T("Invalid code input."), _T("Error"));
        return;
    }

    // If it passed, set the output.
    txtCodeOutput->SetValue(result);
}

void pgCodeBeautifier::Clear(wxCommandEvent &WXUNUSED(event))
{
    int dlgresult = wxMessageBox(
        _T("\
Are you sure that you would like to clear the input and output boxes?\
"),
        _T("Clear Input/Output?"), wxYES_NO
    );

    if (dlgresult == wxYES)
    {
        txtCodeInput->SetValue(_T(""));
        txtCodeOutput->SetValue(_T(""));
    }
}
void pgCodeBeautifier::Copy(wxCommandEvent &WXUNUSED(event))
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
void pgCodeBeautifier::Paste(wxCommandEvent &WXUNUSED(event))
{
    // Prompt them if the input box isn't empty.
    int dlgresult = !txtCodeInput->GetValue().IsEmpty()
                    ? wxMessageBox(
                        _T("\
Are you sure that you would like to paste in a new input?\n\
This will overwrite any current data in the input box.\
"),
                        _T("Overwrite Input?"), wxYES_NO
                    )
                    : wxYES;

    if (dlgresult == wxYES)
        txtCodeInput->SetValue(Clipboard::GetClipboard());
}
