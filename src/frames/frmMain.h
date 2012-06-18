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
 * @file frmMain.h - Header file for the frmMain class.
**/

#ifndef FRMMAIN_H_INCLUDED
#define FRMMAIN_H_INCLUDED

#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/aui/auibook.h>

#include "MenuBar.h"

// Load config.h for the selective page generation
#include "config.h"

#ifdef ADD_BUTTON_ACTIVATOR_GENERATOR
#include "pgButtonActivatorGenerator.h"
#endif

#ifdef ADD_POINTER_SEARCHER
#include "pgPointerSearcher.h"
#endif

#ifdef ADD_CODE_PORTER
#include "pgCodePorter.h"
#endif

#ifdef ADD_CODE_COMPRESSOR
#include "pgCodeCompressor.h"
#endif

class frmMain : public wxFrame
{
public:

    frmMain(void);

    /** Main Window **/

    wxPanel *pnlNotebook;
    wxBoxSizer *vboxNotebook;
    wxAuiNotebook *nbMain;
};

#endif // FRMMAIN_H_INCLUDED

