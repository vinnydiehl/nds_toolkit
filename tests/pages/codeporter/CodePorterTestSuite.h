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
 * @file CodePorterTestSuite.cpp - Tests for the Code Porter.
**/

#include <cxxtest/TestSuite.h>

#include <wx/arrstr.h>
#include <wx/ffile.h>
#include <wx/string.h>

#include "CodePorter.h"

#include "wx2.9/arrstr.h"

const wxString TEST_FILES = _T("../../pages/codeporter/test_files");

class CodePorterTestSuite : public CxxTest::TestSuite
{
public:

    void testPort1(void)
    {
        mRunTest(TEST_FILES + _T("/1"));
    }

private:

    void mRunTest(wxString dir)
    {
        // Files with input info and expected results will be read into these.
        wxString codeInput, exCodeOutput;
        wxArrayString inputOptions;

        // Open the files with testing info.
        wxFFile fInputOptions((dir + _T("/input_options")).c_str());
        wxFFile fCodeInput((dir + _T("/code_input")).c_str());
        wxFFile fCodeOutput((dir + _T("/code_output")).c_str());

        // Read the code output/input into their strings.
        fCodeInput.ReadAll(&codeInput);
        fCodeOutput.ReadAll(&exCodeOutput);

        // Read the input options into a temporary string.
        wxString sInputOptions;
        fInputOptions.ReadAll(&sInputOptions);
        // Now make that into a wxArrayString.
        inputOptions = wxc::wxSplit(sInputOptions, _T('\n'));

        // Trim all file inputs.
        wxArrayString trimmer = wxc::wxSplit(codeInput, _T('\n'));
        for (size_t i = 0; i < trimmer.GetCount(); ++i)
            trimmer[i] = trimmer[i].Trim().Trim(false);
        codeInput = wxc::wxJoin(trimmer, _T('\n')).Trim().Trim(false);

        trimmer = wxc::wxSplit(exCodeOutput, _T('\n'));
        for (size_t i = 0; i < trimmer.GetCount(); ++i)
            trimmer[i] = trimmer[i].Trim().Trim(false);
        exCodeOutput = wxc::wxJoin(trimmer, _T('\n')).Trim().Trim(false);

        for (size_t i = 0; i < inputOptions.GetCount(); ++i)
            inputOptions[i] = inputOptions[i].Trim().Trim(false);

        // The actual results will be stored into these and compared:
        wxString codeOutput = CodePorter::Port(
            codeInput,
            inputOptions[1],
            inputOptions[0] == _T("Add") ? Add : Sub
        );

        TS_TRACE("Testing ported code match...");
        TS_ASSERT(codeOutput == exCodeOutput);
    }
};

