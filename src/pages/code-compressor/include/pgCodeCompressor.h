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
 * @file pgCodeCompressor.h - Header file for the Code Compressor page.
**/

#ifndef PGCODECOMPRESSOR_H_INCLUDED
#define PGCODECOMPRESSOR_H_INCLUDED

#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>

#include "globals.h"

class pgCodeCompressor : public wxPanel
{
public:

    static wxString Title;

    pgCodeCompressor(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *hboxMain;
    wxPanel *pnlMain;

    wxStaticBoxSizer *svboxLoopCodeGenerator;
      wxBoxSizer *hboxBaseCode;
        wxStaticText *lblBaseCode;
        wxTextCtrl *txtBaseCode;
      wxBoxSizer *hboxTotalLoopCount;
        wxStaticText *lblTotalLoopCount;
        wxTextCtrl *txtTotalLoopCount;
      wxBoxSizer *hboxOffsetIncrement;
        wxStaticText *lblOffsetIncrement;
        wxTextCtrl *txtOffsetIncrement;
      wxBoxSizer *hboxValueIncrement;
        wxStaticText *lblValueIncrement;
        wxTextCtrl *txtValueIncrement;
        wxCheckBox *chkValueIncrement;
      wxBoxSizer *hboxLoopControls;
        wxButton *btnGenerate, *btnClearAll;
      wxStaticLine *slnLoopCodeGenerator;
      wxTextCtrl *txtLoopOutput;
      wxButton *btnLoopCopy;

    wxStaticBoxSizer *shboxEBuilder;
      wxBoxSizer *vboxInput;
        wxStaticText *lblInput;
        wxTextCtrl *txtInput;
        wxButton *btnBuild;
      wxBoxSizer *vboxOutput;
        wxStaticText *lblOutput;
        wxTextCtrl *txtOutput;
        wxButton *btnECopy;

    // Add layout boxes and such like so:
    // wxBoxSizer *hboxName;
    // wxStaticText *lblFoo;

    /** Events **/

    // Loop Code Generator
    void LoopGenerate(wxCommandEvent &event);
    void LoopClearAll(wxCommandEvent &event);
    void LoopCopy(wxCommandEvent &event);

    // E Builder
    void EBuild(wxCommandEvent &event);
    void ECopy(wxCommandEvent &event);

private:

    /** Identifiers **/

    static const long ID_GENERATE, ID_CLEAR_ALL;
    static const long ID_BUILD;
    static const long ID_LOOP_COPY, ID_E_COPY;
};

#endif // PGCODECOMPRESSOR_H_INCLUDED

