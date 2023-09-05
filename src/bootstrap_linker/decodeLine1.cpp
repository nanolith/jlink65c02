/**
 * \file src/bootstrap_linker/decodeLine1.cpp
 *
 * \brief Decode a line during the first pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeLine1(
    char cmd, const string& args, bool& in_pass, ostream& log)
{
    stringstream sin(args);
    stringstream errorout;

    switch (cmd)
    {
        case '+': decodePlusCommand1(sin, log); break;
        case 'A': case 'a': decodeACommand1(sin, log); break;
        case 'D': case 'd': decodeDCommand1(sin, log); break;
        case 'G': case 'g': decodeGCommand1(sin, log); break;
        case 'J': case 'j': decodeJCommand1(sin, log); break;
        case 'L': case 'l': decodeLCommand1(sin, log); break;
        case 'O': case 'o': decodeOCommand1(sin, log); break;
        case 'Q': case 'q': decodeQCommand1(sin, log); break;
        case 'R': case 'r': decodeRCommand1(sin, log); break;
        case 'X': case 'x': decodeXCommand1(sin, log); in_pass = false; break;
        case 'Z': case 'z': decodeZCommand1(sin, log); break;
        case ';': log << "ignoring comment." << endl; break;
        default:
            errorout << "unknown command " << cmd << ".";
            throw runtime_error(errorout.str());
    }
}
