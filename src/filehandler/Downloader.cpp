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
 * @file Downloader.cpp - Class for downloading files from the internet.
**/

#include "Downloader.h"

// Constructor sets the member variables to various arguments passed to it.
// Default download path is the current working directory.
Downloader::Downloader(wxWindow *parent, wxString url,
                       wxString filename, wxString path)
          : mParent(parent), Url(url), FileName(filename), mPath(path)
{
}

void Downloader::SetPath(wxString path)
{
    /**
     * Set the path to download the file to.
    **/

    mPath = path;
}

void Downloader::SetPathToCwd(void)
{
    /**
     * Set the path to download the file to to the current working directory.
    **/

    mPath = wxGetCwd();
}

void Downloader::SelectPath(void)
{
    /**
     * Have the user select a location to download the file to.
    **/

    wxFileDialog dlgSave(mParent, _T("Select Save Location"), mPath,
                         FileName, _T("All Files (*.*)|*.*"),
                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    // Display the dialog and, if they don't cancel, set their desired path.
    if (dlgSave.ShowModal() != wxID_CANCEL)
        mPath = dlgSave.GetPath();
}

void Downloader::Download(void)
{
    /**
     * Download the file to the specified location.
    **/

    wxProgressDialog dlgProgress(_T("Downloading..."),
                                 _T("Please wait while your file downloads."));

    wxURL dl(Url);
    if (dl.GetError() == wxURL_NOERR)
    {
        wxInputStream *in = dl.GetInputStream();
        if (in && in->IsOk())
        {
            wxFFileOutputStream out(mPath);

            while (dlgProgress.Pulse())
                in->Read(out);
        }
        delete in;
    }
}

