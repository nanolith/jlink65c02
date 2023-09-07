/**
 * \file src/bootstrap_linker/decodeGCommand1.cpp
 *
 * \brief Decode a G command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeGCommand1(istream& in, ostream& log)
{
    string symbol;
    stringstream errorout;

    in >> symbol;

    if (local_symbols.count(symbol) > 0)
    {
        errorout << "local symbol " << symbol
                 << " shadows global symbol of the same name.";
        throw runtime_error(errorout.str());
    }

    if (global_symbols.count(symbol) > 0)
    {
        errorout << "global symbol " << symbol << " already defined.";
        throw runtime_error(errorout.str());
    }

    global_symbols[symbol] = text_address;

    auto logflags = log.flags();
    log << "global symbol " << symbol << " defined at "
        << uppercase << hex << setw(4) << setfill('0') << text_address << "."
        << endl;
    log.flags(logflags);
}
