/**
 * \file src/bootstrap_linker/pass2.cpp
 *
 * \brief Driver for the second linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iostream>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::pass2(istream& in, ostream& log, ostream& out)
{
    bool in_pass = true;

    // loop while there's input and we are in the pass.
    while (in.good() && in_pass)
    {
        // read a line from the object stream.
        string line;
        getline(in, line);
        if (!in.good())
        {
            throw runtime_error("end of stream without an X command.");
        }

        // scrub whitespace at the start of the line.
        string::iterator f =
            find_if_not(
                line.begin(), line.end(),
                [](char c) -> bool { return isspace(c); } );

        // skip blank lines.
        if (f == line.end())
        {
            continue;
        }

        // log the line.
        log << line << endl;

        // decode the line
        decodeLine2(*f, string(f+1, line.end()), in_pass, log, out);
    }
}
