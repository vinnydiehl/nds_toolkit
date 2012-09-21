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
 * @file Downloader.cpp - Class for downloading files from the internet.
**/

#include "Downloader.h"

// Constructor sets the member variables to various arguments passed to it.
// Default download path is the current working directory.
Downloader::Downloader(wxWindow *parent, wxString url,
                       wxString filename, wxString path)
          : Url(url), FileName(filename), mParent(parent), mPath(path)
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

bool Downloader::SelectPath(void)
{
    /**
     * Have the user select a location to download the file to.
     *
     * Returns whether or not the selection was successful.
    **/

    wxFileDialog dlgSave(mParent, _T("Select Save Location"), mPath,
                         FileName, _T("All Files (*.*)|*.*"),
                         wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    // Display the dialog and, if they don't cancel, set their desired path.
    if (dlgSave.ShowModal() != wxID_CANCEL)
    {
        mPath = dlgSave.GetPath();
        return true;
    }

    return false;
}

void Downloader::Download(void)
{
    /**
     * Download the file to the specified location.
    **/

    // 16 KB read
    const size_t BUFSIZE = 0x4000;

    wxURL url(Url);
    if (url.GetError() == wxURL_NOERR)
    {
        wxFFileOutputStream out(mPath);
        wxInputStream *in = url.GetInputStream();

        if (in && in->IsOk())
        {
            unsigned char buffer[BUFSIZE];

            size_t total_len = in->GetSize();
            size_t data_loaded = 0;
            bool abort = false;

            wxProgressDialog dlgProgress(
                _T("Downloading..."),
                _T("Download in progress."),
                total_len, NULL,
                wxPD_CAN_ABORT | wxPD_SMOOTH | wxPD_APP_MODAL |
                wxPD_ELAPSED_TIME | wxPD_REMAINING_TIME
            );

            while (in->CanRead() && !in->Eof() && !abort)
            {
                // Download some data into the buffer.
                in->Read(buffer, BUFSIZE);
                size_t readlen = in->LastRead();

                // If data was read into the buffer, write it to the file.
                if (readlen > 0)
                {
                    out.Write(buffer, readlen);
                    data_loaded += readlen;
                }

                // Display KB on the dialog unless 1 MB or more has been
                // downloaded- then display MB.
                wxString unit = _T("KB");
                float divisor = 0x400;
                if (data_loaded >= 0x100000)
                {
                    unit = _T("MB");
                    divisor = 0x100000;
                }

                if (data_loaded >= total_len)
                    dlgProgress.SetTitle(_T("Download Complete"));

                // Update the dialog if we know the file length, otherwise
                // just pulse it. Set abort if they cancel the download.
                abort = total_len > 0
                        ? data_loaded < total_len
                          ? !dlgProgress.Update(
                                data_loaded,
                                wxString::Format(
                                    _T("Downloaded %.1f of %.1f %s"),
                                    data_loaded / divisor,
                                    total_len / divisor,
                                    unit.c_str()
                                )
                            )
                          // If the download is finished, write the final
                          // message.
                          : !dlgProgress.Update(
                                data_loaded,
                                _T("Download completed.")
                            )
                        : !dlgProgress.Pulse();
            }

            // Console output for the download result.
            wxPuts(
                abort
                ? _T("Download was cancelled.")
                : wxString::Format(
                      _T("Downloaded %ld bytes."), out.GetSize()
                  )
            );

            if (abort)
            {
                // Delete the partial file if they cancelled the downloaded.
                wxRemoveFile(mPath);
                dlgProgress.Hide();
                wxMessageBox(_T("Your download has been cancelled."),
                             _T("Download Cancelled"));
            }
        }

        delete in;
    }
}

void Downloader::SelectAndDownload(void)
{
    if (SelectPath())
        Download();
}
