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
 * @file ButtonActivatorGenerator.cpp -
 *           pgButtonActivatorGenerator's main algorithm.
**/

#include "ButtonActivatorGenerator.h"

// Constructor to initialize member variables
ButtonActivatorGenerator::ButtonActivatorGenerator(wxTextCtrl *codeInput,
                                                   wxTextCtrl *codeOutput,
                                                   wxTextCtrl *gbaTstOutput,
                                                   wxTextCtrl *ndsTstOutput)
                        : mCodeInput(codeInput),
                          mCodeOutput(codeOutput),
                          mGbaTstOutput(gbaTstOutput),
                          mNdsTstOutput(ndsTstOutput),
                          mGbaAr(NONE_AR), mGbaTst(NONE_TST),
                          mNdsAr(NONE_AR), mNdsTst(NONE_TST)
{
}

void ButtonActivatorGenerator::UpdateOutput(void)
{
    /**
     * Update the output wxTextControls.
    **/

    // Clear all outputs and exit if nothing is selected.
    if (IsEmpty())
    {
        mCodeOutput->Clear();
        mGbaTstOutput->Clear();
        mNdsTstOutput->Clear();

        return;
    }

    // Build the AR code output onto this.
    wxString builder;

    if (IsNds())
    {
        builder += wxString::Format(_T("94000130 %.4X0000\n"), mNdsAr);
        mNdsTstOutput->SetValue(wxString::Format(_T("0x%.4X"), mNdsTst));
    }
    else mNdsTstOutput->Clear();

    if (IsGba())
    {
        builder += wxString::Format(_T("927FFFA8 %.4X0000\n"), mGbaAr);
        mGbaTstOutput->SetValue(wxString::Format(_T("0x%.4X"), mGbaTst));
    }
    else mGbaTstOutput->Clear();

    // If there is a valid code input, add it onto the builder.
    // Otherwise, just insert a blank line.
    wxString input = CodeParser::Beautify(mCodeInput->GetValue());
    builder += CodeParser::Verify(input)
               ? input + _T('\n')
               : _T("\n");

    // Final line of the AR code.
    builder += _T("D2000000 00000000");

    // Now set the builder to the code output.
    mCodeOutput->SetValue(builder);
}

bool ButtonActivatorGenerator::IsGba(void)
{
    /**
     * Return true if a GBA value is selected, false otherwise.
    **/

    return (bool)mGbaTst;
}
bool ButtonActivatorGenerator::IsNds(void)
{
    /**
     * Return true if an NDS value is selected, false otherwise.
    **/

    return (bool)mNdsTst;
}
bool ButtonActivatorGenerator::IsEmpty(void)
{
    /**
     * Return true if nothing is selected, false otherwise.
    **/

    return mGbaTst == NONE_TST && mNdsTst == NONE_TST;
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
            mGbaAr ^= NONE_AR - A_AR;
            mGbaTst ^= A_TST;
            break;
        case B:
            mGbaAr ^= NONE_AR - B_AR;
            mGbaTst ^= B_TST;
            break;
        case Select:
            mGbaAr ^= NONE_AR - SELECT_AR;
            mGbaTst ^= SELECT_TST;
            break;
        case Start:
            mGbaAr ^= NONE_AR - START_AR;
            mGbaTst ^= START_TST;
            break;
        case Right:
            mGbaAr ^= NONE_AR - RIGHT_AR;
            mGbaTst ^= RIGHT_TST;
            break;
        case Left:
            mGbaAr ^= NONE_AR - LEFT_AR;
            mGbaTst ^= LEFT_TST;
            break;
        case Up:
            mGbaAr ^= NONE_AR - UP_AR;
            mGbaTst ^= UP_TST;
            break;
        case Down:
            mGbaAr ^= NONE_AR - DOWN_AR;
            mGbaTst ^= DOWN_TST;
            break;
        case R:
            mGbaAr ^= NONE_AR - R_AR;
            mGbaTst ^= R_TST;
            break;
        case L:
            mGbaAr ^= NONE_AR - L_AR;
            mGbaTst ^= L_TST;
            break;

        // NDS Buttons
        case X:
            mNdsAr ^= NONE_AR - X_AR;
            mNdsTst ^= X_TST;
            break;
        case Y:
            mNdsAr ^= NONE_AR - Y_AR;
            mNdsTst ^= Y_TST;
            break;
        case Debug:
            mNdsAr ^= NONE_AR - DEBUG_AR;
            mNdsTst ^= DEBUG_TST;
            break;
        case Folded:
            mNdsAr ^= NONE_AR - FOLDED_AR;
            mNdsTst ^= FOLDED_TST;
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

    mGbaAr = mNdsAr = NONE_AR;
    mGbaTst = mNdsTst = NONE_TST;

    if (update)
        UpdateOutput();
}

