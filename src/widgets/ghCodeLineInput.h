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
 * @file ghCodeLineInput.h - Header file for the ghCodeLineInput widget.
**/

#ifndef GHCODELINEINPUT_H_INCLUDED
#define GHCODELINEINPUT_H_INCLUDED

#include <wx/textctrl.h>

#include <wx/regex.h>

class ghCodeLineInput : public wxTextCtrl
{
public:
    ghCodeLineInput(wxWindow *parent,
                    wxWindowID id,
                    const wxString &value=_T(""),
                    const wxPoint &pos=wxDefaultPosition,
                    const wxSize &size=wxDefaultSize,
                    long style=0,
                    const wxValidator &validator=wxDefaultValidator,
                    const wxString &name=wxTextCtrlNameStr);

private:
    static const wxRegEx HEXCHAR;

    void mOnKeyDown(wxKeyEvent &evt);
    void mOnTextUpdated(wxCommandEvent &evt);

    void mFormatText(void);
    wxString mStripToHex(wxString str);
};

#endif // GHCODELINEINPUT_H_INCLUDED
