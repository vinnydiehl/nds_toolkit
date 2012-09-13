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
 * @file PointerSearcher.cpp - Pointer Searcher main algorithm.
**/

#include "PointerSearcher.h"

void PointerSearcher::Search(wxArrayString *outputSearchResults,
                             unsigned *outputSmallest,
                             wxFFileInputStream *file1,
                             wxFFileInputStream *file2,
                             wxString addr1str,
                             wxString addr2str,
                             wxString hexValueStr,
                             TargetType offsetTargetType,
                             wxString maxPtrOffsetStr)
{
    /**
     * Run the algorithm for the Pointer Searcher.
     *
     * @param outputSearchResults - String to place search result output into.
     * @param file1 - The File 1 input's wxFFileInputStream.
     * @param file2 - The File 2 input's wxFFileInputStream.
     * @param addr1str - The Address 1 input.
     * @param addr2str - The Address 2 input.
     * @param hexValueStr - The Hex Value input.
     * @param offsetTargetType - "Only Positive"/"Only Negative" selection.
     * @param maxPtrOffsetStr - The Max Pointer Offset input.
    **/

    // Snoop around for problems before continuing.

    // Might as well save these as variables, a couple of the tests use them.
    long file1len = file1->GetLength();
    long file2len = file2->GetLength();

    // If, for whatever reason, the length cannot be determined, error.
    if (file1len == wxInvalidOffset)
        throw wxString(_T("The length of File 1 could not be determined."));
    if (file2len == wxInvalidOffset)
        throw wxString(_T("The length of File 2 could not be determined."));

    // Error if either file is empty.
    if (file1len == 0)
        throw wxString(_T("File 1 contains no data."));
    if (file2len == 0)
        throw wxString(_T("File 2 contains no data."));

    // Are the two files the same length? If not, error.
    if (file1len != file2len)
        throw wxString(_T("The files being compared are different lengths."));

    // Try converting all of the numeric stuff to numeric types now.
    long addr1, addr2, hexValue, maxPtrOffset;

    if (!addr1str.ToLong(&addr1, 16))
        throw wxString(_T("Address 1 must be a hex number."));
    if (!addr2str.ToLong(&addr2, 16))
        throw wxString(_T("Address 2 must be a hex number."));
    if (!hexValueStr.ToLong(&hexValue, 16))
        throw wxString(_T("Hex Value must be a hex number."));
    if (!maxPtrOffsetStr.ToLong(&maxPtrOffset, 16))
        throw wxString(_T("Max Pointer Offset must be a hex number."));

    // Now just do a few tests with those numeric values.
    // (Testing number inputs while they're still strings is unsafe.)

    // Make sure that the addresses are different.
    if (addr1 == addr2)
        throw wxString(_T("Please input two different addresses."));

    // Addresses should be from 6-7 characters, not including 0's.
    if (addr1 < 0x100000)
        throw wxString(_T("Address 1 is too small."));
    if (addr1 > 0xFFFFFFF)
        throw wxString(_T("Address 1 is too big."));
    if (addr2 < 0x100000)
        throw wxString(_T("Address 2 is too small."));
    if (addr2 > 0xFFFFFFF)
        throw wxString(_T("Address 2 is too big."));

    // End of error checking, beginning of calculation.

    // We can clear out the output strings now so they can be appended to.
    outputSearchResults->Clear();

    // Seek to the beginning of each stream.
    // Without this, the search can only run once on each file.
    file1->SeekI(0);
    file2->SeekI(0);

    // Get data streams to allow reading from the binary files.
    wxDataInputStream data1(*file1);
    wxDataInputStream data2(*file2);

    // Calculate their desired offset from their inputs.
    // Absolute value of maxPtrOffset:
    long desiredOffset = maxPtrOffset < 0
                         ? 0 - maxPtrOffset
                         : maxPtrOffset;
    // Make it negative if they selected that option:
    if (offsetTargetType == Negative)
        desiredOffset *= -1;

    // Loop through the file's size in bytes.
    // sizeof(int) because 32-bit integers are being read from the files.
    for (long i = 0; i < file1len; i += sizeof(int))
    {
        long offset1 = addr1 - data1.Read32();
        long offset2 = addr2 - data2.Read32();

        if (offset1 == offset2 &&
            ((offset1 <= desiredOffset && offset1 > 0) ||
             (offset1 >= desiredOffset && offset1 < 0)))
            outputSearchResults->Add(wxString::Format(
                _T("0x%.8X : 0x%.8X :: 0x%.8X"),
                i + 0x2000000,
                addr1 - offset1,
                offset1
            ));
    }

    if (outputSearchResults->IsEmpty())
        throw wxString(_T("No results were found."));

    // Copy this locally, it looks cleaner.
    wxArrayString results = *outputSearchResults;

    // These need to be tracked outside of the loop.
    long smallestOffset = 0;
    unsigned smallest = 0;

    // Loop over the results and find the smallest.
    for (unsigned i = 0; i < results.GetCount(); ++i)
    {
        // Just to be on the safe side, make sure we don't have a blank.
        if (results[i].Trim().Trim(false).IsEmpty())
            continue;

        // Parse the offset value.
        long offset;
        results[i].Mid(29, 8).ToLong(&offset, 16);

        // If this result is the best so far, save some data about it.
        if (smallestOffset == 0 || offset < smallestOffset)
        {
            smallest = i;
            smallestOffset = offset;
        }
    }

    *outputSmallest = smallest;
}

wxString PointerSearcher::ArCode(wxString result, wxString hexValueStr)
{
    // Convert the hex value to an integer.
    long hexValue;
    if (!hexValueStr.ToLong(&hexValue, 16))
        throw wxString(_T("Hex Value must be a hex number."));

    // Use the hex value to determine the code type.
    char codeType = hexValue >= 0x0 && hexValue <= 0xFF
                    ? 2
                    : hexValue > 0xFF && hexValue <= 0xFFFF
                      ? 1
                      : 0;

    // Get the offset and the address...
    long offset;
    result.Mid(29, 8).ToLong(&offset, 16);
    wxString address = result.Mid(3, 7);

    // First two lines of the AR code output:
    wxString builder = wxString::Format(
        _T("6%s 00000000\nB%s 00000000\n"),
        address.c_str(), address.c_str()
    );

    builder += offset < 0
        // Offset is negative:
        ? wxString::Format(
            _T("\
DC000000 %.8X\n\
%X8000000 %.8X\n\
D2000000 00000000\
"),
            offset - 0x8000000,
            codeType,
            hexValue
        )
        // Offset is positive:
        : wxString::Format(
            _T("\
%X%.7X %.8X\n\
D2000000 00000000\
"),
            codeType,
            offset,
            hexValue
        );

    return builder;
}
