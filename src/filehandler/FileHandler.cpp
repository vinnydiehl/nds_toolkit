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
 * @file FileHandler.cpp - Contains methods for file input.
**/

#include "FileHandler.h"

wxString FileHandler::mActiveFile = _T("");

/**
 * :BUG: 2012-09-13 gbchaosmaster - Active file auto-selection bug
 * These four methods will automatically highlight the previously selected
 * file, which is intended behavior, but if the file to be highlighted clashes
 * with the wildcard, the wildcard will break.
**/

wxString FileHandler::GetFileSelection(wxWindow *parent, wxTextCtrl *display,
                                       wxString wildcard, wxString title)
{
    wxFileDialog dlgOpenFile(parent, title,
                             // Default to home directory if it's the first
                             // time they're selecting a file.
                             !mActiveFile.IsEmpty() ? _T("") : wxGetHomeDir(),
                             // If they're already selected a file, jump to
                             // its location automatically and highlight it.
                             mActiveFile,
                             wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    // Show the dialog. Once it closes, if they pressed cancel, stop.
    if (dlgOpenFile.ShowModal() == wxID_CANCEL)
        return _T("");

    mActiveFile = dlgOpenFile.GetPath();

    // If they want to output the file path into a TextCtrl, do so.
    if (display != NULL)
        display->SetValue(mActiveFile);

    // Return the filename.
    return mActiveFile;
}

wxFFileInputStream* FileHandler::GetStream(wxWindow *parent,
                                           wxTextCtrl *display,
                                           wxString wildcard,
                                           wxString title)
{
    wxString filename = GetFileSelection(parent, display, wildcard, title);
    return filename.IsEmpty() ? NULL : new wxFFileInputStream(filename);
}

wxString FileHandler::GetSaveFileSelection(wxWindow *parent,
                                           wxString saveas,
                                           wxString wildcard,
                                           wxString title)
{
    wxFileDialog dlgSave(parent, title, wxGetHomeDir(),
                         saveas, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    // Display the dialog- if they cancel, return an empty string.
    if (dlgSave.ShowModal() == wxID_CANCEL)
        return _T("");

    mActiveFile = dlgSave.GetPath();

    return mActiveFile;
}

wxFFileOutputStream* FileHandler::GetSaveStream(wxWindow *parent,
                                                wxString saveas,
                                                wxString wildcard,
                                                wxString title)
{
    wxString filename = GetSaveFileSelection(parent, saveas, wildcard, title);
    return filename.IsEmpty() ? NULL : new wxFFileOutputStream(filename);
}
