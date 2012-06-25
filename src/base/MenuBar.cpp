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

MenuBar::MenuBar(wxFrame *_parent) : wxMenuBar()
{
    parent = _parent;

    /** File **/

    file = new wxMenu;

    file->Append(wxID_EXIT, _T("&Quit\tCtrl+W"));

    /** Help **/

    help = new wxMenu;

    help->Append(wxID_ABOUT, _T("&About\tF1"));

    // Assemble the menu bar
    Append(file, _T("&File"));
    Append(help, _T("&Help"));

    // Connect the menu bar items to their events
    parent->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
                    wxCommandEventHandler(MenuBar::Quit));
    parent->Connect(wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED,
                    wxCommandEventHandler(MenuBar::About));
}

/** Events **/

void MenuBar::Quit(wxCommandEvent &WXUNUSED(event))
{
    Close();
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
