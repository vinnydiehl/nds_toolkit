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
 * @file pgButtonActivatorGenerator.h -
 *           Header file for the Button Activator Generator page.
**/

#ifndef PGBUTTONACTIVATORGENERATOR_H_INCLUDED
#define PGBUTTONACTIVATORGENERATOR_H_INCLUDED

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>

#include "ButtonActivatorGenerator.h"

#include "Clipboard.h"
#include "CodeParser.h"
#include "globals.h"

class pgButtonActivatorGenerator : public wxPanel
{
public:

    static wxString Title;

    pgButtonActivatorGenerator(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *hboxMain;
    wxPanel *pnlMain;

    wxBoxSizer *vboxCodeInput;
      wxStaticText *lblCodeInput;
      wxTextCtrl *txtCodeInput;
    wxBoxSizer *vboxControls;
      wxStaticBoxSizer *svboxButtons;
        wxFlexGridSizer *gridButtons;
          wxCheckBox *chkA, *chkB, *chkX, *chkY, *chkL, *chkR,
                     *chkLeft, *chkRight, *chkUp, *chkDown,
                     *chkStart, *chkSelect, *chkFolded, *chkDebug;
      wxButton *btnClear, *btnCopy, *btnPaste;
      wxStaticLine *slnControls;
      wxFlexGridSizer *gridTstValues;
        wxStaticText *lblGbaTst, *lblNdsTst;
        wxTextCtrl *txtGbaTst, *txtNdsTst;
    wxBoxSizer *vboxCodeOutput;
      wxStaticText *lblCodeOutput;
      wxTextCtrl *txtCodeOutput;

    /** Events **/

    void Clear(wxCommandEvent &event);
    void Copy(wxCommandEvent &event);
    void Paste(wxCommandEvent &event);

    void CheckInput(wxCommandEvent &event);

    // Unfortunately each checkbox needs an event.

    // GBA Buttons
    void ToggleA(wxCommandEvent &event);
    void ToggleB(wxCommandEvent &event);
    void ToggleSelect(wxCommandEvent &event);
    void ToggleStart(wxCommandEvent &event);
    void ToggleRight(wxCommandEvent &event);
    void ToggleLeft(wxCommandEvent &event);
    void ToggleUp(wxCommandEvent &event);
    void ToggleDown(wxCommandEvent &event);
    void ToggleR(wxCommandEvent &event);
    void ToggleL(wxCommandEvent &event);

    // NDS Buttons
    void ToggleX(wxCommandEvent &event);
    void ToggleY(wxCommandEvent &event);
    void ToggleDebug(wxCommandEvent &event);
    void ToggleFolded(wxCommandEvent &event);

private:

    /** Identifiers **/

    // Lots of ID's for the checkboxes
    static const long ID_A, ID_B,
                      ID_SELECT, ID_START,
                      ID_RIGHT, ID_LEFT, ID_UP, ID_DOWN,
                      ID_R, ID_L,
                      ID_X, ID_Y,
                      ID_DEBUG, ID_FOLDED;
    static const long ID_CLEAR, ID_COPY, ID_PASTE;
    static const long ID_CODE_INPUT;

    /** Controller **/

    ButtonActivatorGenerator *mController;
};

#endif // PGBUTTONACTIVATORGENERATOR_H_INCLUDED

