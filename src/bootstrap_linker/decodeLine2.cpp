/**
 * \file src/bootstrap_linker/decodeLine2.cpp
 *
 * \brief Decode a line during the second pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeLine2(
    char cmd, const string& args, bool& in_pass, ostream& log, ostream& out)
{
    stringstream sin(args);
    stringstream errorout;

    switch (cmd)
    {
        case '+': decodePlusCommand2(sin, log, out); break;
        case 'A': case 'a': decodeACommand2(sin, log, out); break;
        case 'D': case 'd': decodeDCommand2(sin, log, out); break;
        case 'G': case 'g': decodeGCommand2(sin, log, out); break;
        case 'J': case 'j': decodeJCommand2(sin, log, out); break;
        case 'L': case 'l': decodeLCommand2(sin, log, out); break;
        case 'O': case 'o': decodeOCommand2(sin, log, out); break;
        case 'Q': case 'q': decodeQCommand2(sin, log, out); break;
        case 'R': case 'r': decodeRCommand2(sin, log, out); break;
        case 'X': case 'x': decodeXCommand2(sin, log); in_pass = false; break;
        case 'Z': case 'z': decodeZCommand2(sin, log, out); break;
        case ';': log << "ignoring comment." << endl; break;
        default:
            errorout << "unknown command " << cmd << ".";
            throw runtime_error(errorout.str());
    }
}
