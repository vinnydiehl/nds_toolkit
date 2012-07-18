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
 * @file ButtonActivatorGenerator.h -
 *           Header file for the ButtonActivatorGenerator class.
**/

#ifndef BUTTONACTIVATORGENERATOR_H_INCLUDED
#define BUTTONACTIVATORGENERATOR_H_INCLUDED

#include <wx/string.h>
#include <wx/textctrl.h>

enum Button
{
    // GBA
    A, B, Start, Select, Right, Left, Up, Down, R, L,
    // NDS
    X, Y, Debug, Folded
};

// Values for TST output
enum
{
    NONE_TST = 0x0,

    // GBA Button Values
    A_TST = 0x1,
    B_TST = 0x2,
    SELECT_TST = 0x4,
    START_TST = 0x8,
    RIGHT_TST = 0x10,
    LEFT_TST = 0x20,
    UP_TST = 0x40,
    DOWN_TST = 0x80,
    R_TST = 0x100,
    L_TST = 0x200,

    // NDS Button Values
    X_TST = 0x400,
    Y_TST = 0x800,
    DEBUG_TST = 0x2000,
    FOLDED_TST = 0x8000
};

// Values for AR code output
enum
{
    NONE_AR = 0xFFFF,

    // GBA Button Values
    A_AR = 0xFFFE,
    B_AR = 0xFFFD,
    SELECT_AR = 0xFFFB,
    START_AR = 0xFFF7,
    RIGHT_AR = 0xFFEF,
    LEFT_AR = 0xFFDF,
    UP_AR = 0xFFBF,
    DOWN_AR = 0xFF7F,
    R_AR = 0xFEFF,
    L_AR = 0xFDFF,

    // NDS Button Values
    X_AR = 0xFBFF,
    Y_AR = 0xF7FF,
    DEBUG_AR = 0xDFFF,
    FOLDED_AR = 0x7FFF
};

class ButtonActivatorGenerator
{
public:
    ButtonActivatorGenerator(wxTextCtrl *arOutput, wxTextCtrl *tstOutput);

    void UpdateOutput(void);

    bool IsNds(void);

    void Toggle(Button btn, bool update=true);
    void Clear(bool update=true);

private:
    wxTextCtrl *mArOutput, *mTstOutput;
    int mAr, mTst;
};

#endif // BUTTONACTIVATORGENERATOR_H_INCLUDED

