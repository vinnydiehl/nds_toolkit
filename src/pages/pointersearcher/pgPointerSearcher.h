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
 * @file pgPointerSearcher.h - Header file for the Pointer Searcher page.
**/

#ifndef PGPOINTERSEARCHER_H_INCLUDED
#define PGPOINTERSEARCHER_H_INCLUDED

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/wfstream.h>

#include "PointerSearcher.h"

#include "CodeParser.h"
#include "FileHandler.h"
#include "globals.h"

class pgPointerSearcher : public wxPanel
{
public:

    static wxString Title;

    pgPointerSearcher(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *vboxMain;
    wxPanel *pnlMain;

    wxStaticBoxSizer *svboxFileDumps;
      wxFlexGridSizer *gridFileDumps;
        wxTextCtrl *txtFile1, *txtFile2;
        wxButton *btnFile1, *btnFile2;

    // gridLower contains everything under the File Dumps section.

    wxFlexGridSizer *gridLower;
      wxStaticBoxSizer *svboxDataInput;
        wxFlexGridSizer *gridDataInput;
          wxStaticText *lblAddress1, *lblAddress2, *lblHexValue;
          wxTextCtrl *txtAddress1, *txtAddress2, *txtHexValue;
      wxStaticBoxSizer *shboxOffsetTarget;
        wxBoxSizer *vboxOffsetTarget;
          wxBoxSizer *hboxOnlyPosNeg;
            wxRadioButton *radOnlyPos, *radOnlyNeg;
          wxBoxSizer *hboxMaxPtrOffset;
            wxStaticText *lblMaxPtrOffset;
            wxTextCtrl *txtMaxPtrOffset;
        wxButton *btnFindPointers;
      wxBoxSizer *vboxSearchResults;
        wxStaticText *lblSearchResults;
        wxListBox *lstSearchResults;
        wxBoxSizer *hboxResultsControls;
          wxButton *btnCopyResult, *btnImport, *btnExport;
      wxBoxSizer *vboxPtrCode;
        wxStaticText *lblPtrCode;
        wxTextCtrl *txtPtrCode;
        wxButton *btnCopyPtrCode;

    /** Events **/

    void FindPointers(wxCommandEvent &event);
    void RefreshPtrCode(wxCommandEvent &event);

    void SelectFile1(wxCommandEvent &event);
    void SelectFile2(wxCommandEvent &event);

    void CopyResult(wxCommandEvent &event);
    void CopyPtrCode(wxCommandEvent &event);
    void Import(wxCommandEvent &event);
    void Export(wxCommandEvent &event);

    /** Member Variables **/

    wxString Wildcard;
    wxFFileInputStream *File1Input, *File2Input;

private:

    /** Identifiers **/

    static const long ID_BROWSE_FILE_1, ID_BROWSE_FILE_2;
    static const long ID_FIND_POINTERS;
    static const long ID_SEARCH_RESULTS, ID_HEX_VALUE;
    static const long ID_COPY_RESULT, ID_COPY_PTR_CODE;
    static const long ID_IMPORT, ID_EXPORT;

    /** Private Methods **/

    void mParseFileName(wxString filename, wxTextCtrl *address);
};

#endif // PGPOINTERSEARCHER_H_INCLUDED
