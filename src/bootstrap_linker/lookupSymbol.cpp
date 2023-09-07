/**
 * \file src/bootstrap_linker/lookupSymbol.cpp
 *
 * \brief Look up an absolute symbol from either the local symbols or global
 * symbols.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

uint16_t bootstrap_linker::lookupSymbol(const string& symbol)
{
    auto f = local_symbols.find(symbol);
    if (local_symbols.end() == f)
    {
        f = global_symbols.find(symbol);
        if (global_symbols.end() == f)
        {
            stringstream errorout;
            errorout << "symbol " << symbol << " not found.";
            throw runtime_error(errorout.str());
        }
    }

    return f->second;
}
