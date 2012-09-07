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
 * @file FileHandler.h - The header file for the FileHandler class.
**/

#pragma once

#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

#include <wx/filedlg.h>
#include <wx/stream.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/wfstream.h>

class FileHandler
{
public:
    static wxFFileInputStream* GetStream(
        wxWindow *parent,
        wxTextCtrl *display=NULL,
        wxString wildcard=_T("All Files (*.*)|*.*"),
        wxString title=_T("Select a File")
    );

private:
    static wxString mActiveFile;
};

#endif // FILEHANDLER_H_INCLUDED
