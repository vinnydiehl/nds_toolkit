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
 * @file pgPointerSearcher.h - Header file for the Pointer Searcher page.
**/

#ifndef PGPOINTERSEARCHER_H_INCLUDED
#define PGPOINTERSEARCHER_H_INCLUDED

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include "globals.h"

class pgPointerSearcher : public wxPanel
{
public:

    static wxString Title;

    pgPointerSearcher(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *vboxMain;
    wxPanel *pnlMain;

    /**
     * vboxMain will contain a single box sizer, simply named hboxUpper, to
     * contain the more complex upper portion of the widgets; the bottom part
     * is more straightforward and can actuall fit directly into vboxMain.
    **/

    wxBoxSizer *hboxUpper;
      wxBoxSizer *vboxControls;
        wxStaticBoxSizer *svboxFileDumps;
          wxBoxSizer *hboxFile1;
            wxButton *btnFile1;
            wxTextCtrl *txtFile1;
          wxBoxSizer *hboxFile2;
            wxButton *btnFile2;
            wxTextCtrl *txtFile2;
          wxCheckBox *chk8ChBeforeBin;
        wxStaticBoxSizer *shboxOffsetTarget;
          wxBoxSizer *vboxOnlyPosNegOptions;
            wxRadioButton *radOnlyPositive, *radOnlyNegative;
          wxBoxSizer *vboxMaxPtrOffset;
            wxStaticText *lblMaxPtrOffset;
            wxTextCtrl *txtMaxPtrOffset;
        wxStaticBoxSizer *shboxDataInput;
          wxBoxSizer *vboxDataInputFields;
            wxBoxSizer *hboxAddress1;
              wxStaticText *lblAddress1;
              wxTextCtrl *txtAddress1;
            wxBoxSizer *hboxAddress2;
              wxStaticText *lblAddress2;
              wxTextCtrl *txtAddress2;
            wxBoxSizer *hboxHexValue;
              wxStaticText *lblHexValue;
              wxTextCtrl *txtHexValue;
          wxButton *btnFindPointers;
      wxBoxSizer *vboxAddresses;
        wxBoxSizer *hboxAddressesLabels;
          wxStaticText *lblPtrAddress, *lblValueAt, *lblOffset;
        // 2012-06-11 gbchaosmaster - Maybe make this a wxListBox?
        wxTextCtrl *txtAddresses;

    wxStaticLine *slnUpperLowerSeparator;

    wxStaticText *lblPointerCode;
    wxTextCtrl *txtPointerCode;

    /** Events **/

    // Insert events here.

private:

    /** Identifiers **/

    static const long ID_BROWSE_FILE_1, ID_BROWSE_FILE_2;
    static const long ID_FIND_POINTERS;
};

#endif // PGPOINTERSEARCHER_H_INCLUDED

