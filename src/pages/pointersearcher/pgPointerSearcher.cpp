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
 * @file pgPointerSearcher.cpp - The program's Pointer Searcher page.
**/

#include "pgPointerSearcher.h"

// Title of the page:
wxString pgPointerSearcher::Title = _T("Pointer Searcher");

/** Initialize Identifiers **/

const long pgPointerSearcher::ID_BROWSE_FILE_1 = wxNewId();
const long pgPointerSearcher::ID_BROWSE_FILE_2 = wxNewId();

const long pgPointerSearcher::ID_FIND_POINTERS = wxNewId();

const long pgPointerSearcher::ID_SEARCH_RESULTS = wxNewId();
const long pgPointerSearcher::ID_HEX_VALUE = wxNewId();

pgPointerSearcher::pgPointerSearcher(wxWindow *parent)
                 :  wxPanel(parent, wxID_ANY)
{
    /** Initialize Member Variables **/

    Wildcard = _T("Binary Files (*.bin)|*.bin|All Files|*");

    /** Main Content **/

    vboxMargin = new wxBoxSizer(wxVERTICAL);

    pnlMain = new wxPanel(this, wxID_ANY);
    vboxMain = new wxBoxSizer(wxVERTICAL);

////////////////////////////////////////////////////////////////////////////////

    svboxFileDumps = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                          _T("File Dumps"));

    gridFileDumps = new wxFlexGridSizer(2, 2, 5, 5);

    txtFile1 = new wxTextCtrl(pnlMain, wxID_ANY);
    btnFile1 = new wxButton(pnlMain, ID_BROWSE_FILE_1, _T("File &1"));
    txtFile2 = new wxTextCtrl(pnlMain, wxID_ANY);
    btnFile2 = new wxButton(pnlMain, ID_BROWSE_FILE_2, _T("File &2"));

    // Row 1
    gridFileDumps->Add(txtFile1, 1, wxEXPAND);
    gridFileDumps->Add(btnFile1);

    // Row 2
    gridFileDumps->Add(txtFile2, 1, wxEXPAND);
    gridFileDumps->Add(btnFile2);

    gridFileDumps->AddGrowableCol(0, 1);

    svboxFileDumps->Add(gridFileDumps, 1, wxEXPAND);

////////////////////////////////////////////////////////////////////////////////

    gridLower = new wxFlexGridSizer(2, 2, 5, 5);

    ///// Begin svboxDataInput

    svboxDataInput = new wxStaticBoxSizer(wxVERTICAL, pnlMain,
                                          _T("Data Input"));

    gridDataInput = new wxFlexGridSizer(2, 3, 5, 5);

    lblAddress1 = new wxStaticText(pnlMain, wxID_ANY, _T("Address 1"));
    txtAddress1 = new wxTextCtrl(pnlMain, wxID_ANY);

    lblAddress2 = new wxStaticText(pnlMain, wxID_ANY, _T("Address 2"));
    txtAddress2 = new wxTextCtrl(pnlMain, wxID_ANY);

    lblHexValue = new wxStaticText(pnlMain, wxID_ANY, _T("Hex Value"));
    txtHexValue = new wxTextCtrl(pnlMain, ID_HEX_VALUE);

    // Row 1
    gridDataInput->Add(lblAddress1, 0, wxALIGN_CENTER_HORIZONTAL);
    gridDataInput->Add(lblAddress2, 0, wxALIGN_CENTER_HORIZONTAL);
    gridDataInput->Add(lblHexValue, 0, wxALIGN_CENTER_HORIZONTAL);

    // Row 2
    gridDataInput->Add(txtAddress1, 1, wxEXPAND);
    gridDataInput->Add(txtAddress2, 1, wxEXPAND);
    gridDataInput->Add(txtHexValue, 1, wxEXPAND);

    // 2012-08-24 gbchaosmaster - This looked a little squished at the top.
    // Adding 3 pixels of padding seems to balance it out okay.
    svboxDataInput->Add(gridDataInput, 1, wxEXPAND | wxTOP, 3);

    gridDataInput->AddGrowableCol(0, 1);
    gridDataInput->AddGrowableCol(1, 1);
    gridDataInput->AddGrowableCol(2, 1);

    ///// Begin shboxOffsetTarget

    shboxOffsetTarget = new wxStaticBoxSizer(wxHORIZONTAL, pnlMain,
                                             _T("Offset Target"));

    // This vbox has everything left of the button in the Offset Target group.
    // It has two internal hboxes to line things up further. Try to follow
    // along, this is probably the messiest part.
    vboxOffsetTarget = new wxBoxSizer(wxVERTICAL);

    // Top half of Offset Target, contains radio buttons
    hboxOnlyPosNeg = new wxBoxSizer(wxHORIZONTAL);

    radOnlyPos = new wxRadioButton(pnlMain, wxID_ANY, _T("Only &Positive"),
                                   wxDefaultPosition, wxDefaultSize,
                                   wxRB_GROUP);
    radOnlyNeg = new wxRadioButton(pnlMain, wxID_ANY, _T("Only &Negative"));

    // With this setup, radOnlyPos will stay to the left half and
    // radOnlyNeg will stay to the right half, good for resizing.
    hboxOnlyPosNeg->Add(radOnlyPos, 1, wxEXPAND);
    hboxOnlyPosNeg->Add(radOnlyNeg, 1, wxEXPAND);

    // Lower half of Offset Target, contains "Max Pointer Offset:" input
    hboxMaxPtrOffset = new wxBoxSizer(wxHORIZONTAL);

    lblMaxPtrOffset = new wxStaticText(pnlMain, wxID_ANY,
                                       _T("Max Pointer Offset:"));
    txtMaxPtrOffset = new wxTextCtrl(pnlMain, wxID_ANY);

    // Default text in txtMaxPtrOffset
    txtMaxPtrOffset->SetValue(_T("00008000"));

    hboxMaxPtrOffset->Add(lblMaxPtrOffset, 0,
                          wxALIGN_CENTER_VERTICAL | wxRIGHT, 5);
    hboxMaxPtrOffset->Add(txtMaxPtrOffset, 1, wxEXPAND);

    vboxOffsetTarget->Add(hboxOnlyPosNeg, 1, wxEXPAND | wxBOTTOM, 5);
    vboxOffsetTarget->Add(hboxMaxPtrOffset, 1, wxEXPAND);

    // This button goes directly into shboxOffsetTarget
    btnFindPointers = new wxButton(pnlMain, ID_FIND_POINTERS,
                                   _T("&Find Pointers"));

    shboxOffsetTarget->Add(vboxOffsetTarget, 1, wxEXPAND | wxRIGHT, 5);
    shboxOffsetTarget->Add(btnFindPointers, 0, wxEXPAND);

    ///// Begin vboxSearchResults

    vboxSearchResults = new wxBoxSizer(wxVERTICAL);

    lblSearchResults = new wxStaticText(
        pnlMain, wxID_ANY, _T("Pointer Address : Value At :: Offset")
    );
    lstSearchResults = new wxListBox(pnlMain, ID_SEARCH_RESULTS);

    vboxSearchResults->Add(lblSearchResults, 0,
                           wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxSearchResults->Add(lstSearchResults, 1, wxEXPAND);

    ///// Begin vboxPtrCode

    vboxPtrCode = new wxBoxSizer(wxVERTICAL);

    lblPtrCode = new wxStaticText(pnlMain, wxID_ANY, _T("Pointer Code"));
    txtPtrCode = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE | wxHSCROLL);

    vboxPtrCode->Add(lblPtrCode, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxPtrCode->Add(txtPtrCode, 1, wxEXPAND);

    ///// Finish up gridLower

    // Row 1
    gridLower->Add(svboxDataInput, 0, wxEXPAND);
    gridLower->Add(shboxOffsetTarget, 0, wxEXPAND);

    // Row 2
    gridLower->Add(vboxSearchResults, 1, wxEXPAND);
    gridLower->Add(vboxPtrCode, 1, wxEXPAND);

    gridLower->AddGrowableCol(0, 1);
    gridLower->AddGrowableCol(1, 1);

    gridLower->AddGrowableRow(1, 1);

////////////////////////////////////////////////////////////////////////////////

    vboxMain->Add(svboxFileDumps, 0, wxEXPAND | wxBOTTOM, 5);
    vboxMain->Add(gridLower, 1, wxEXPAND);

    pnlMain->SetSizer(vboxMain);
    vboxMain->SetSizeHints(pnlMain);

    vboxMargin->Add(pnlMain, 1, wxEXPAND | wxALL, MARGIN);
    SetSizer(vboxMargin);
    vboxMargin->SetSizeHints(this);

    // Connect main window events
    Connect(ID_FIND_POINTERS, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::FindPointers));

    Connect(ID_BROWSE_FILE_1, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::SelectFile1));
    Connect(ID_BROWSE_FILE_2, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::SelectFile2));

    Connect(ID_SEARCH_RESULTS, wxEVT_COMMAND_LISTBOX_SELECTED,
            wxCommandEventHandler(pgPointerSearcher::RefreshPtrCode));
    Connect(ID_HEX_VALUE, wxEVT_COMMAND_TEXT_UPDATED,
            wxCommandEventHandler(pgPointerSearcher::RefreshPtrCode));
}

/** Main Algorithm **/

void pgPointerSearcher::FindPointers(wxCommandEvent &WXUNUSED(event))
{
    wxString address1 = txtAddress1->GetValue().Trim().Trim(false);
    wxString address2 = txtAddress2->GetValue().Trim().Trim(false);
    wxString hexValue = txtHexValue->GetValue().Trim().Trim(false);
    wxString maxPtrOffset = txtMaxPtrOffset->GetValue().Trim().Trim(false);

    // UI-level error testing

    // Test lack of files
    if (!File1Input)
    {
        wxMessageBox(_T("Please select a file for File 1."), _T("Error"));
        return;
    }
    if (!File2Input)
    {
        wxMessageBox(_T("Please select a file for File 2."), _T("Error"));
        return;
    }

    // Test lack of text box inputs
    if (address1.IsEmpty())
    {
        wxMessageBox(_T("There is no Address 1 input."), _T("Error"));
        return;
    }
    if (address2.IsEmpty())
    {
        wxMessageBox(_T("There is no Address 2 input."), _T("Error"));
        return;
    }
    if (hexValue.IsEmpty())
    {
        wxMessageBox(_T("There is no Hex Value input."), _T("Error"));
        return;
    }
    if (maxPtrOffset.IsEmpty())
    {
        wxMessageBox(_T("There is no Max Pointer Offset input."), _T("Error"));
        return;
    }

    wxArrayString searchResults;
    wxString ptrCode;
    unsigned smallest;

    try
    {
        PointerSearcher::Search(&searchResults, &ptrCode, &smallest,
                                File1Input, File2Input,
                                txtAddress1->GetValue(),
                                txtAddress2->GetValue(),
                                txtHexValue->GetValue(),
                                radOnlyPos->GetValue() ? Positive : Negative,
                                txtMaxPtrOffset->GetValue());
    }
    catch (wxString msg)
    {
        wxMessageBox(msg, _T("Error"));
        return;
    }

    lstSearchResults->Set(searchResults);
    lstSearchResults->SetSelection(smallest);
    txtPtrCode->SetValue(ptrCode);
}
void pgPointerSearcher::RefreshPtrCode(wxCommandEvent &WXUNUSED(event))
{
    // Stop if we have nothing to do.
    if (lstSearchResults->IsEmpty() || txtHexValue->IsEmpty())
        return;

    try
    {
        txtPtrCode->SetValue(
            PointerSearcher::ArCode(
                lstSearchResults->GetStringSelection(),
                txtHexValue->GetValue()
            )
        );
    }
    catch (wxString msg)
    {
        wxMessageBox(msg, _T("Error"));
        return;
    }
}

/** File Input **/

void pgPointerSearcher::SelectFile1(wxCommandEvent &WXUNUSED(event))
{
    File1Input = FileHandler::GetStream(this, txtFile1, Wildcard);
    mParseFileName(txtFile1->GetValue(), txtAddress1);
}
void pgPointerSearcher::SelectFile2(wxCommandEvent &WXUNUSED(event))
{
    File2Input = FileHandler::GetStream(this, txtFile2, Wildcard);
    mParseFileName(txtFile2->GetValue(), txtAddress2);
}
void pgPointerSearcher::mParseFileName(wxString filename, wxTextCtrl *address)
{
    // If the filename has an 8 digit hex number at the end of it, just
    // before the .bin, put that in the corresponding Address text box.
    // Otherwise, clear the text box.
    wxString last8 = filename.Mid(filename.Len() - 12, 8);
    address->SetValue(CodeParser::IsHex(last8) ? last8.Upper() : _T(""));
}

