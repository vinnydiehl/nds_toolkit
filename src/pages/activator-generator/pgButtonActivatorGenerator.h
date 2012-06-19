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
 * @file pgButtonActivatorGenerator.h -
 *           Header file for the Button Activator Generator page.
**/

#ifndef PGBUTTONACTIVATORGENERATOR_H_INCLUDED
#define PGBUTTONACTIVATORGENERATOR_H_INCLUDED

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>

#include "Clipboard.h"
#include "globals.h"

class pgButtonActivatorGenerator : public wxPanel
{
public:

    static wxString Title;

    pgButtonActivatorGenerator(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *vboxMain;
    wxPanel *pnlMain;

    wxFlexGridSizer *gridGroups;
      wxStaticBoxSizer *svboxButtonType;
        wxRadioButton *radGba, *radNds;
      wxStaticBoxSizer *svboxGbaButtons;
        wxFlexGridSizer *gridGbaButtons;
          wxCheckBox *chkA, *chkUp, *chkL, *chkR, *chkStart,
                     *chkB, *chkDown, *chkLeft, *chkRight, *chkSelect;
      wxStaticBoxSizer *svboxTarget;
        wxRadioButton *radArCode, *radTstValue;
      wxStaticBoxSizer *shboxNdsButtons;
        wxCheckBox *chkX, *chkY, *chkNdsFolded, *chkDebugButton;

    wxButton *btnGenerate;

    wxStaticLine *slnSeparator;

    wxStaticText *lblCodeOutput;
    wxTextCtrl *txtCodeOutput;

    wxBoxSizer *hboxCodeOutputControls;
      wxButton *btnCopy, *btnClear;

    /** Events **/

    void ChangeType(wxCommandEvent &event);

    void Generate(wxCommandEvent &event);

    void Copy(wxCommandEvent &event);
    void Clear(wxCommandEvent &event);

private:

    /** Identifiers **/

    static const long ID_CHANGE_TYPE;
    static const long ID_GENERATE;
    static const long ID_COPY, ID_CLEAR;
};

#endif // PGBUTTONACTIVATORGENERATOR_H_INCLUDED

