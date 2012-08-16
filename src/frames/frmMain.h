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
 * @file frmMain.h - Header file for the frmMain class.
**/

#ifndef FRMMAIN_H_INCLUDED
#define FRMMAIN_H_INCLUDED

#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/auibook.h>

#include "MenuBar.h"
#include "globals.h"

/** Selective Page Generation **/

/**
 * PAGE_CAST is used as a generic page to cast to, and recycles the existing
 * page classes. Because of the dynamic nature of including certain pages,
 * I can't just pick a random one, so I need to use some preprocessor magic
 * to make sure that the page that I'm trying to cast to exists.
**/

#include "config.h"

// Button Activator Generator
#ifdef ADD_BUTTON_ACTIVATOR_GENERATOR
#  include "pgButtonActivatorGenerator.h"
#  define PAGE_CAST pgButtonActivatorGenerator*
#endif

// Pointer Searcher
#ifdef ADD_POINTER_SEARCHER
#  include "pgPointerSearcher.h"

#  ifndef PAGE_CAST
#    define PAGE_CAST pgPointerSearcher*
#  endif

#endif

// Code Porter
#ifdef ADD_CODE_PORTER
#  include "pgCodePorter.h"

#  ifndef PAGE_CAST
#    define PAGE_CAST pgCodePorter*
#  endif

#endif

// Code Compressor
#ifdef ADD_CODE_COMPRESSOR
#  include "pgCodeCompressor.h"

#  ifndef PAGE_CAST
#    define PAGE_CAST pgCodeCompressor*
#  endif

#endif

// Code Beautifier
#ifdef ADD_CODE_BEAUTIFIER
#  include "pgCodeBeautifier.h"

#  ifndef PAGE_CAST
#    define PAGE_CAST pgCodeBeautifier*
#  endif

#endif

class frmMain : public wxFrame
{
public:

    frmMain(void);

    /** Main Window **/

    wxPanel *pnlNotebook;
    wxBoxSizer *vboxNotebook;
    wxAuiNotebook *nbMain;

    MenuBar *menuBar;

    /** Events **/

    void SetMinSizeToPage(void);
    void SetMinSizeToPage(wxCommandEvent &event);

private:

    /** Identifiers **/

    static const long ID_NOTEBOOK;
};

#endif // FRMMAIN_H_INCLUDED

