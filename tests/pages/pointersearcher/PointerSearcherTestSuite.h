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
 * @file PointerSearcherTestSuite.cpp - Tests for the Pointer Searcher.
**/

#include <cxxtest/TestSuite.h>

#include <wx/arrstr.h>
#include <wx/ffile.h>
#include <wx/string.h>
#include <wx/wfstream.h>

#include "PointerSearcher.h"

#include "wx2.9/arrstr.h"

const wxString TEST_FILES = _T("../../pages/pointersearcher/test_files");

class PointerSearcherTestSuite : public CxxTest::TestSuite
{
public:

    void testBinResults1(void)
    {
        mRunBinFileTest(TEST_FILES + _T("/1"));
    }

private:

    void mRunBinFileTest(wxString dir)
    {
        // Files with input info and expected results will be read into these.
        unsigned long exSmallestIndex;
        wxString exPtrCode;
        wxArrayString inputOptions, exSearchResults;

        // Open the files with testing info.
        wxFFile fInputOptions((dir + _T("/input_options")).c_str());
        wxFFile fSearchResults((dir + _T("/search_results")).c_str());
        wxFFile fPtrCode((dir + _T("/pointer_code")).c_str());
        wxFFile fSmallestIndex((dir + _T("/smallest_index")).c_str());

        // Read the files into temporary strings.
        wxString sInputOptions, sSearchResults, sSmallestIndex;
        fInputOptions.ReadAll(&sInputOptions);
        fSearchResults.ReadAll(&sSearchResults);
        fSmallestIndex.ReadAll(&sSmallestIndex);

        // This one doesn't need a temporary string:
        fPtrCode.ReadAll(&exPtrCode);

        // Read input_options and search_results into wxArrayStrings.
        inputOptions = wxc::wxSplit(sInputOptions, _T('\n'));
        exSearchResults = wxc::wxSplit(sSearchResults, _T('\n'));

        // For the sake of being safe, trim all of the input files.
        wxArrayString trimmer = wxc::wxSplit(exPtrCode.Trim().Trim(false),
                                             _T('\n'));
        for (size_t i = 0; i < trimmer.GetCount(); ++i)
            trimmer[i] = trimmer[i].Trim().Trim(false);
        exPtrCode = wxc::wxJoin(trimmer, _T('\n'));

        for (size_t i = 0; i < inputOptions.GetCount(); ++i)
            inputOptions[i] = inputOptions[i].Trim().Trim(false);

        for (size_t i = 0; i < exSearchResults.GetCount(); ++i)
            exSearchResults[i] = exSearchResults[i].Trim().Trim(false);

        sSmallestIndex = sSmallestIndex.Trim().Trim(false);

        // Read smallest_index into an unsigned long.
        sSmallestIndex.ToULong(&exSmallestIndex);

        // The actual results will be stored into these and compared:
        wxArrayString searchResults;
        wxString pointerCode;
        unsigned smallestIndex;

        PointerSearcher::Search(
            &searchResults, &pointerCode, &smallestIndex,
            new wxFFileInputStream(dir + _T('/') + inputOptions[0]),
            new wxFFileInputStream(dir + _T('/') + inputOptions[1]),
            inputOptions[2],
            inputOptions[3],
            inputOptions[4],
            inputOptions[5] == _T("Positive") ? Positive : Negative,
            inputOptions[6]
        );

        TS_TRACE("Testing search results match...");
        TS_ASSERT(searchResults == exSearchResults);
        TS_TRACE("Testing pointer code match...");
        TS_ASSERT(pointerCode == exPtrCode);
        TS_TRACE("Testing smallest index match...");
        TS_ASSERT(smallestIndex == exSmallestIndex);
    }
};

