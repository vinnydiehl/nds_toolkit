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
 * @file pgCodeBeautifier.h - Header file for the Code Beautifier page.
**/

#ifndef PGCODEBEAUTIFIER_H_INCLUDED
#define PGCODEBEAUTIFIER_H_INCLUDED

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>

#include "Clipboard.h"
#include "CodeParser.h"
#include "globals.h"

class pgCodeBeautifier : public wxPanel
{
public:

    static wxString Title;

    pgCodeBeautifier(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *hboxMain;
    wxPanel *pnlMain;

    wxBoxSizer *vboxCodeInput;
      wxStaticText *lblCodeInput;
      wxTextCtrl *txtCodeInput;
    wxBoxSizer *vboxControls;
      wxStaticBoxSizer *svboxOptions;
        wxBoxSizer *vboxOptions;
          wxCheckBox *chkUpperHex, *chkStripBlankLines, *chkStripComments;
      wxButton *btnBeautify;
      wxStaticBoxSizer *svboxTools;
        wxButton *btnClear, *btnCopy, *btnPaste;
    wxBoxSizer *vboxCodeOutput;
      wxStaticText *lblCodeOutput;
      wxTextCtrl *txtCodeOutput;

    /** Events **/

    void Beautify(wxCommandEvent &event);

    void Clear(wxCommandEvent &event);
    void Copy(wxCommandEvent &event);
    void Paste(wxCommandEvent &event);

private:

    /** Identifiers **/

    static const long ID_BEAUTIFY;
    static const long ID_CLEAR, ID_COPY, ID_PASTE;
};

#endif // PGCODEBEAUTIFIER_H_INCLUDED
