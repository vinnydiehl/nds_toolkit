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

const long pgPointerSearcher::ID_COPY_RESULT = wxNewId();
const long pgPointerSearcher::ID_COPY_PTR_CODE = wxNewId();

const long pgPointerSearcher::ID_IMPORT = wxNewId();
const long pgPointerSearcher::ID_EXPORT = wxNewId();

pgPointerSearcher::pgPointerSearcher(wxWindow *parent)
                 :  wxPanel(parent, wxID_ANY)
{
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

    // Nested hbox with search results buttons:
    hboxResultsControls = new wxBoxSizer(wxHORIZONTAL);
    //
    btnCopyResult = new wxButton(pnlMain, ID_COPY_RESULT,
                                 _T("Copy Current &Result"));
    btnImport = new wxButton(pnlMain, ID_IMPORT, _T("&Import"));
    btnExport = new wxButton(pnlMain, ID_EXPORT, _T("&Export"));
    //
    hboxResultsControls->Add(btnCopyResult, 3, wxEXPAND | wxRIGHT, 5);
    hboxResultsControls->Add(btnImport, 2, wxEXPAND | wxRIGHT, 5);
    hboxResultsControls->Add(btnExport, 2, wxEXPAND);

    vboxSearchResults->Add(lblSearchResults, 0,
                           wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxSearchResults->Add(lstSearchResults, 1, wxEXPAND | wxBOTTOM, 5);
    vboxSearchResults->Add(hboxResultsControls, 0, wxEXPAND);

    ///// Begin vboxPtrCode

    vboxPtrCode = new wxBoxSizer(wxVERTICAL);

    lblPtrCode = new wxStaticText(pnlMain, wxID_ANY, _T("Pointer Code"));
    txtPtrCode = new wxTextCtrl(pnlMain, wxID_ANY, wxEmptyString,
                                wxDefaultPosition, wxDefaultSize,
                                wxTE_MULTILINE | wxHSCROLL);
    btnCopyPtrCode = new wxButton(pnlMain, ID_COPY_PTR_CODE,
                                  _T("&Copy Pointer Code"));

    vboxPtrCode->Add(lblPtrCode, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 5);
    vboxPtrCode->Add(txtPtrCode, 1, wxEXPAND | wxBOTTOM, 5);
    vboxPtrCode->Add(btnCopyPtrCode, 0, wxEXPAND);

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

    Connect(ID_COPY_RESULT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::CopyResult));
    Connect(ID_COPY_PTR_CODE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::CopyPtrCode));

    Connect(ID_IMPORT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::Import));
    Connect(ID_EXPORT, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(pgPointerSearcher::Export));
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
    unsigned smallest;

    try
    {
        PointerSearcher::Search(&searchResults, &smallest,
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
    RefreshPtrCode();
}
void pgPointerSearcher::RefreshPtrCode(void)
{
    // Clear the output and stop if we can't do anything.
    if (lstSearchResults->IsEmpty() || txtHexValue->IsEmpty())
    {
        txtPtrCode->Clear();
        return;
    }

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
void pgPointerSearcher::RefreshPtrCode(wxCommandEvent &WXUNUSED(event))
{
    // Overload for use as an event.
    RefreshPtrCode();
}

/** File Input **/

const wxString pgPointerSearcher::BIN_WILDCARD =
    _T("Binary Files (*.bin)|*.bin|All Files|*");

void pgPointerSearcher::SelectFile1(wxCommandEvent &WXUNUSED(event))
{
    File1Input = FileHandler::GetStream(this, txtFile1, BIN_WILDCARD);
    mParseFileName(txtFile1->GetValue(), txtAddress1);
}
void pgPointerSearcher::SelectFile2(wxCommandEvent &WXUNUSED(event))
{
    File2Input = FileHandler::GetStream(this, txtFile2, BIN_WILDCARD);
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

/** Output Tools **/

void pgPointerSearcher::CopyResult(wxCommandEvent &WXUNUSED(event))
{
    wxString str = lstSearchResults->GetStringSelection();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("Currently selected result copied successfully."),
                         _T("Success"));
    }
}
void pgPointerSearcher::CopyPtrCode(wxCommandEvent &WXUNUSED(event))
{
    wxString str = txtPtrCode->GetValue();

    if (!str.IsEmpty())
    {
        Clipboard::SetClipboard(str);

        if (Clipboard::GetClipboard() == str)
            wxMessageBox(_T("Pointer code output copied successfully."),
                         _T("Success"));
    }
}

const wxString pgPointerSearcher::PSR_WILDCARD =
    _T("Pointer Searcher Results Files (*.psr)|*.psr|All Files|*");

void pgPointerSearcher::Import(wxCommandEvent &WXUNUSED(event))
{
    // Prompt them if there are search results that would be overwritten.
    int dlgresult = !lstSearchResults->IsEmpty()
                    ? wxMessageBox(
                        _T("\
Are you sure that you would like import new search results?\n\
This will overwrite any current data in the search result output.\
"),
                        _T("Overwrite Results?"), wxYES_NO
                    )
                    : wxYES;

    if (dlgresult != wxYES)
        return;

    wxString filename = FileHandler::GetFileSelection(this, NULL,
                                                      PSR_WILDCARD);

    // Make sure that a file has been selected.
    if (filename.IsEmpty())
        return;

    PSR psr(filename);

    if (!psr.Verify())
    {
        wxMessageBox(_T("Invalid Pointer Searcher Results file."),
                     _T("Error"));
        return;
    }

    txtHexValue->SetValue(psr.GetHexValue());
    lstSearchResults->Clear();
    lstSearchResults->InsertItems(psr.GetResults(), 0);
    lstSearchResults->SetSelection(psr.GetIndex());
    RefreshPtrCode();
}
void pgPointerSearcher::Export(wxCommandEvent &WXUNUSED(event))
{
    if (lstSearchResults->IsEmpty())
    {
        wxMessageBox(_T("There are no search results."), _T("Error"));
        return;
    }

    wxString filename = FileHandler::GetSaveFileSelection(
        this,
        _T("SearchResults.psr"),
        PSR_WILDCARD
    );

    if (!filename.IsEmpty())
    {
        PSR::Write(
            filename,
            lstSearchResults->GetStrings(),
            lstSearchResults->GetSelection(),
            txtHexValue->GetValue()
        );
    }
}
