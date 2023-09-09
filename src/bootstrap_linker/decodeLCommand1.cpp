/**
 * \file src/bootstrap_linker/decodeLCommand1.cpp
 *
 * \brief Decode a L command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeLCommand1(istream& in, ostream& log)
{
    string symbol;
    stringstream errorout;

    in >> symbol;

    if (global_symbols.count(symbol) > 0)
    {
        errorout << "local symbol " << symbol
                 << " shadows global symbol of the same name.";
        throw runtime_error(errorout.str());
    }

    if (local_symbols.count(symbol) > 0)
    {
        errorout << "local symbol " << symbol << " already defined.";
        throw runtime_error(errorout.str());
    }

    local_symbols[symbol] = text_address;

    auto logflags = log.flags();
    log << "local symbol " << symbol << " defined at "
        << uppercase << hex << setw(4) << setfill('0') << text_address
        << "." << endl;
    log.flags(logflags);
}
