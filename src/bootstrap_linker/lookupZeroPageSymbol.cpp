/**
 * \file src/bootstrap_linker/lookupZeroPageSymbol.cpp
 *
 * \brief Look up a zero page symbol.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

uint8_t bootstrap_linker::lookupZeroPageSymbol(const string& symbol)
{
    auto f = zeropage.find(symbol);
    if (zeropage.end() == f)
    {
        stringstream errorout;
        errorout << "symbol " << symbol << " not found.";
        throw runtime_error(errorout.str());
    }

    return f->second;
}
