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
 * @file ButtonActivatorGenerator.cpp -
 *           pgButtonActivatorGenerator's main algorithm.
**/

#include "ButtonActivatorGenerator.h"

// Constructor to initialize member variables
ButtonActivatorGenerator::ButtonActivatorGenerator(wxTextCtrl *ndsOutput,
                                                   wxTextCtrl *tstOutput)
                        : mArOutput(ndsOutput), mTstOutput(tstOutput),
                          mAr(NONE_AR), mTst(NONE_TST)
{
}

void ButtonActivatorGenerator::UpdateOutput(void)
{
    /**
     * Update the output wxTextControls.
    **/

    // :TODO: gbchaosmaster 2012-07-18 - Use a C string here
    // I just end up pulling out the C string from the wxString anyway, but
    // trying to use const char* here gives a GTK error when it tries to
    // format it below. Figure out how to eliminate the need to make
    // this variable a wxString.
    wxString tst = IsNds() ? _T("4000130") : _T("27FFFA8");

    mArOutput->SetValue(wxString::Format(
        _T("9%s %X0000\n\nD2000000 00000000"),
        tst.c_str(), mAr
    ));
    mTstOutput->SetValue(wxString::Format(
        _T("Tst 0x%X to the value at 0x0%s"),
        mTst, tst.c_str()
    ));
}

bool ButtonActivatorGenerator::IsNds(void)
{
    /**
     * Return true if an NDS value is selected, false otherwise.
    **/

    return (mTst & X_TST) || (mTst & Y_TST) ||
           (mTst & DEBUG_TST) || (mTst & FOLDED_TST);
}

void ButtonActivatorGenerator::Toggle(Button btn, bool update)
{
    /**
     * Toggle a button.
     *
     * @param btn - The button to be toggled.
     * @param update - true if you want to run UpdateOutput() at the end.
     *                 Default: True
    **/

    switch (btn)
    {
        // GBA Buttons
        case A:
            mAr ^= NONE_AR - A_AR;
            mTst ^= A_TST;
            break;
        case B:
            mAr ^= NONE_AR - B_AR;
            mTst ^= B_TST;
            break;
        case Select:
            mAr ^= NONE_AR - SELECT_AR;
            mTst ^= SELECT_TST;
            break;
        case Start:
            mAr ^= NONE_AR - START_AR;
            mTst ^= START_TST;
            break;
        case Right:
            mAr ^= NONE_AR - RIGHT_AR;
            mTst ^= RIGHT_TST;
            break;
        case Left:
            mAr ^= NONE_AR - LEFT_AR;
            mTst ^= LEFT_TST;
            break;
        case Up:
            mAr ^= NONE_AR - UP_AR;
            mTst ^= UP_TST;
            break;
        case Down:
            mAr ^= NONE_AR - DOWN_AR;
            mTst ^= DOWN_TST;
            break;
        case R:
            mAr ^= NONE_AR - R_AR;
            mTst ^= R_TST;
            break;
        case L:
            mAr ^= NONE_AR - L_AR;
            mTst ^= L_TST;
            break;

        // NDS Buttons
        case X:
            mAr ^= NONE_AR - X_AR;
            mTst ^= X_TST;
            break;
        case Y:
            mAr ^= NONE_AR - Y_AR;
            mTst ^= Y_TST;
            break;
        case Debug:
            mAr ^= NONE_AR - DEBUG_AR;
            mTst ^= DEBUG_TST;
            break;
        case Folded:
            mAr ^= NONE_AR - FOLDED_AR;
            mTst ^= FOLDED_TST;
            break;

        // If the input wasn't valid, do nothing and print a debug message.
        default:
            wxPuts(
                _T("\n\nInvalid input to ButtonActivatorGenerator::Toggle().")
            );
            break;
    }

    if (update)
        UpdateOutput();
}
void ButtonActivatorGenerator::Clear(bool update)
{
    /**
     * Clears all values.
     *
     * @param update - true if you want to run UpdateOutput() at the end.
     *                 Default: True
    **/

    mAr = NONE_AR;
    mTst = NONE_TST;

    if (update)
        UpdateOutput();
}

