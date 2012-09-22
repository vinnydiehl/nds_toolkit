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
 * @file ghCodeLineInput.cpp - The ghCodeLineInput widget.
**/

#include "ghCodeLineInput.h"

const wxRegEx ghCodeLineInput::HEXCHAR(_T("\\A[0-9A-Fa-f]\\Z"), wxRE_ADVANCED);

ghCodeLineInput::ghCodeLineInput(wxWindow *parent, wxWindowID id,
                                 const wxString &value, const wxPoint &pos,
                                 const wxSize &size, long style,
                                 const wxValidator &validator,
                                 const wxString &name)
               : wxTextCtrl(parent, id, value, pos, size,
                            style, validator, name)
{
    // Line of code with a space- 17 characters long.
    SetMaxLength(17);

    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(ghCodeLineInput::mOnKeyDown));
    Connect(wxEVT_COMMAND_TEXT_UPDATED,
            wxCommandEventHandler(ghCodeLineInput::mOnTextUpdated));
}

/** Events **/

void ghCodeLineInput::mOnKeyDown(wxKeyEvent &evt)
{
    // If the user clicks right after the space and tries to delete it, skip
    // the insertion point to the character right before the space, so it
    // deletes that.
    if (GetInsertionPoint() == 9 && evt.GetKeyCode() == WXK_BACK)
        SetInsertionPoint(8);

    evt.Skip();
}

void ghCodeLineInput::mOnTextUpdated(wxCommandEvent &WXUNUSED(evt))
{
    mFormatText();
}

/** Helpers **/

void ghCodeLineInput::mFormatText(void)
{
    wxString text = mStripToHex(GetValue());
    wxString final;

    for (size_t i = 0; i < text.Len(); ++i)
    {
        if (i == 8)
            final += _T(' ');
        final += text[i];
    }

    // An attempt at a hack to get it to just work, but no good.
    // For some reason when you enter that 9th character, this method runs
    // again, not going into the conditional the second time. Maybe it's the
    // ChangeValue() that does it for some reason?
    if (final.Len() == 10 && GetValue().Len() == 10)
    {
        SetInsertionPointEnd();
    }

    // Most of the time this won't even change anything, so don't apply the
    // space adjustment unless it needs to be done.
    if (final != GetValue())
    {
        int pos = GetInsertionPoint();
        ChangeValue(final);
        SetInsertionPoint(pos);
    }
}

wxString ghCodeLineInput::mStripToHex(wxString str)
{
    /**
     * Strip all non-hex characters from str and return the result.
    **/

    wxString output;

    for (size_t i = 0; i < str.Len(); ++i)
        if (HEXCHAR.Matches(str[i]))
            output += str[i];

    return output.Upper().Left(16);
}
