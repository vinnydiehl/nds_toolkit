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
 * @file Downloader.h - The header file for the Downloader class.
**/

#include <wx/filedlg.h>
#include <wx/filefn.h>
#include <wx/progdlg.h>
#include <wx/stream.h>
#include <wx/string.h>
#include <wx/url.h>
#include <wx/wfstream.h>

class Downloader
{
public:
    // Public member variables
    wxString Url, FileName;

    // Public methods
    Downloader(wxWindow *parent, wxString url,
               wxString filename, wxString path=wxGetCwd());

    void SetPath(wxString path);
    void SetPathToCwd(void);

    bool SelectPath(void);

    void Download(void);

    void SelectAndDownload(void);

private:
    wxWindow *mParent;
    wxString mPath;
};

