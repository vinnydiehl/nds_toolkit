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
 * @file MenuBar.h - MenuBar class contains the application's menubar.
**/

#ifndef MENUBAR_H_INCLUDED
#define MENUBAR_H_INCLUDED

#include <wx/aboutdlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/string.h>

#include "Downloader.h"

#include "globals.h"

class MenuBar : public wxMenuBar
{
public:

    MenuBar(wxFrame *parent);

    wxFrame *Parent;

    wxMenu *File;
    wxMenu *Tools;
    wxMenu *Help;

    /** Events **/

    void Quit(wxCommandEvent &event);
    void DownloadUsrcheat(wxCommandEvent &event);
    void About(wxCommandEvent &event);

private:

    /** Identifiers **/

    static const long ID_USRCHEAT;
};

#endif // MENUBAR_H_INCLUDED

