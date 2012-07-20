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
 * @file LoopCodeGenerator.cpp - The algorithm for the Loop Code Generator
 *                               section of the Code Compressor.
**/

#include "LoopCodeGenerator.h"

wxString LoopCodeGenerator::Generate(wxString baseCode,
                                     wxString totalLoopCountStr,
                                     wxString offsetIncrementStr,
                                     wxString valueIncrementStr)
{
    // The strings will be coverted over to these.
    unsigned long totalLoopCount, offsetIncrement, valueIncrement;

    // Detect any problems with the input.
    if (!CodeParser::Verify(baseCode))
        throw wxString(_T("Invalid Base Code input."));
    // For the numbers, convert them in the mean time.
    if (!totalLoopCountStr.ToULong(&totalLoopCount))
        throw wxString(_T("Total Loop Count must contain a number."));
    if (!offsetIncrementStr.ToULong(&offsetIncrement))
        throw wxString(_T("Offset Increment must contain a number."));
    if (!valueIncrementStr.IsEmpty())
        if (!valueIncrementStr.ToULong(&valueIncrement))
            throw wxString(_T("Value Increment must contain a number."));

    if (offsetIncrement == 1 || offsetIncrement == 2 || offsetIncrement == 4)
    {
        // Offset Increment is 1/2/4, make sure Base Code starts with 0
        if (!baseCode.StartsWith(_T("0")))
            throw wxString(
_T("If Offset Increment is 1/2/4, Base Code must start with '0'.")
            );

        return wxString::Format(
            _T("\
D5000000 %s\n\
C0000000 %s\n\
D%i000000 %s\n\
%s\
D2000000 00000000\
"),
            // Right half of the Base Code
            CodeParser::RightColumn(baseCode)[0].c_str(),
            // Total Loop Count, minus 1, converted to hex
            mZPad(wxString::Format(_T("%X"), totalLoopCount - 1), 8).c_str(),
            // Map the offset increment to this value with a big ternary
            offsetIncrement == 1 ? 8
                : offsetIncrement == 2 ? 7
                    : offsetIncrement == 4 ? 6
                        : 0,
            // Left half of the Base Code
            CodeParser::LeftColumn(baseCode)[0].c_str(),
            // If there's a Value Increment, gather up that
            valueIncrementStr.IsEmpty()
            ? _T("")
            : wxString::Format(
                _T("D4000000 %s\n"),
                mZPad(wxString::Format(_T("%X"), valueIncrement), 8).c_str()
            ).c_str()
        );
    }
    else
    {
        // Offset Increment is not 1/2/4, so there cannot be a Value Increment
        if (!valueIncrementStr.IsEmpty())
            throw wxString(
_T("If there is a Value Increment, the Offset Increment must be 1/2/4.")
            );

        return wxString::Format(
            _T("\
C0000000 %s\n\
%s\n\
DC000000 %s\n\
D2000000 00000000\
"),
            // Total Loop Count, minus 1, converted to hex
            mZPad(wxString::Format(_T("%X"), totalLoopCount - 1), 8).c_str(),
            // Entire Base Code
            baseCode.c_str(),
            // Offset Increment converted to hex
            mZPad(wxString::Format(_T("%X"), offsetIncrement), 8).c_str()
        );
    }
}

wxString LoopCodeGenerator::mZPad(wxString str, unsigned n)
{
    /**
     * Return str, padded to length n with zeros.
    **/

    return str.Len() < n
           ? str.Pad(n - str.Len(), _T('0'), false)
           : str;
}

