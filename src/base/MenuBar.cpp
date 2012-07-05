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
 * @file MenuBar.cpp - Build the menu bar for the application.
**/

#include "MenuBar.h"

/** Initialize Identifiers **/

const long MenuBar::ID_USRCHEAT = wxNewId();

MenuBar::MenuBar(wxFrame *parent) : Parent(parent), wxMenuBar()
{
    /** File **/

    File = new wxMenu;

    File->Append(wxID_EXIT, _T("&Quit\tCtrl+W"));

    /** Tools **/

    Tools = new wxMenu;

    Tools->Append(wxID_ANY, _T("&Download usrcheat.dat\tCtrl+U"));

    /** Help **/

    Help = new wxMenu;

    Help->Append(wxID_ABOUT, _T("&About\tF1"));

    // Assemble the menu bar
    Append(File, _T("&File"));
    Append(Tools, _T("&Tools"));
    Append(Help, _T("&Help"));

    // Connect the menu bar items to their events
    parent->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
                    wxCommandEventHandler(MenuBar::Quit));
    parent->Connect(ID_USRCHEAT, wxEVT_COMMAND_MENU_SELECTED,
                    wxCommandEventHandler(MenuBar::DownloadUsrcheat));
    parent->Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
                    wxCommandEventHandler(MenuBar::About));
}

/** Events **/

void MenuBar::Quit(wxCommandEvent &WXUNUSED(event))
{
    Close();
}

void MenuBar::DownloadUsrcheat(wxCommandEvent &WXUNUSED(event))
{
    // :TODO: 2012-07-05 gbchaosmaster - Implement MenuBar::DownloadUsrcheat()
}

void MenuBar::About(wxCommandEvent &WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName(NAME);
    info.SetVersion(VERSION);
    info.SetDescription(DESCRIPTION);
    info.SetCopyright(COPYRIGHT);

    wxAboutBox(info);
}

