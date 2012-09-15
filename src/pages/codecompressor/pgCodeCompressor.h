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
 * @file pgCodeCompressor.h - Header file for the Code Compressor page.
**/

#ifndef PGCODECOMPRESSOR_H_INCLUDED
#define PGCODECOMPRESSOR_H_INCLUDED

#include <wx/button.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/string.h>
#include <wx/textctrl.h>

#include "LoopCodeGenerator.h"
#include "PatchCodeBuilder.h"

#include "Clipboard.h"
#include "fonts.h"
#include "globals.h"

// Set this to 1 if you want to use the old layout.
// In this layout, the text boxes in the Loop Code Generator aren't aligned
// on the left side. The new layout corrects this with a wxFlexGridSizer.
#define USE_OLD_LAYOUT 0

class pgCodeCompressor : public wxPanel
{
public:

    static wxString Title;

    pgCodeCompressor(wxWindow *parent);

    /** Main Content **/

    wxBoxSizer *vboxMargin, *hboxMain;
    wxPanel *pnlMain;

    wxStaticBoxSizer *svboxLoopCodeGenerator;
#if USE_OLD_LAYOUT
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
#else
      wxFlexGridSizer *gridLoopCodeGenerator;
        wxStaticText *lblBaseCode, *lblTotalLoopCount,
                     *lblOffsetIncrement, *lblValueIncrement;
        wxTextCtrl *txtBaseCode, *txtTotalLoopCount,
                   *txtOffsetIncrement, *txtValueIncrement;
#endif
      wxBoxSizer *hboxLoopControls;
        wxButton *btnGenerate, *btnClearAll;
      wxStaticLine *slnLoopCodeGenerator;
      wxTextCtrl *txtLoopOutput;
      wxButton *btnLoopCopy;

    wxStaticBoxSizer *shboxPatchCodeBuilder;
      wxBoxSizer *vboxInput;
        wxStaticText *lblInput;
        wxTextCtrl *txtInput;
        wxBoxSizer *hboxInputButtons;
          wxButton *btnPaste, *btnBuild;
      wxBoxSizer *vboxOutput;
        wxStaticText *lblOutput;
        wxTextCtrl *txtOutput;
        wxBoxSizer *hboxOutputButtons;
          wxButton *btnPatchCopy, *btnPatchClear;

    // Add layout boxes and such like so:
    // wxBoxSizer *hboxName;
    // wxStaticText *lblFoo;

    /** Events **/

    // Loop Code Generator
    void LoopGenerate(wxCommandEvent &event);
    void LoopClearAll(wxCommandEvent &event);
    void LoopCopy(wxCommandEvent &event);

    // E Builder
    void PatchBuild(wxCommandEvent &event);
    void PatchCopy(wxCommandEvent &event);
    void PatchPaste(wxCommandEvent &event);
    void PatchClear(wxCommandEvent &event);

private:

    /** Identifiers **/

    static const long ID_LOOP_GENERATE, ID_LOOP_CLEAR_ALL;
    static const long ID_LOOP_COPY;
    static const long ID_PATCH_BUILD, ID_PATCH_COPY,
                      ID_PATCH_PASTE, ID_PATCH_CLEAR;
};

#endif // PGCODECOMPRESSOR_H_INCLUDED
