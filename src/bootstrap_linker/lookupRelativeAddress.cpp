/**
 * \file src/bootstrap_linker/lookupRelativeAddress.cpp
 *
 * \brief Look up the address of a local symbol, relative to the given base
 * address.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

int8_t bootstrap_linker::lookupRelativeAddress(
    const string& symbol, uint16_t base_address)
{
    auto f = local_symbols.find(symbol);
    if (local_symbols.end() == f)
    {
        stringstream errorout;
        errorout << "local symbol " << symbol << " not found.";
        throw runtime_error(errorout.str());
    }

    // calculate the relative location.
    int32_t base = base_address;
    int32_t destination = f->second;
    int32_t relative = destination - base; 
    int8_t rel_byte = (int8_t)relative;

    // bounds check the computed address
    if (base + rel_byte != destination)
    {
        stringstream errorout;
        errorout << "local symbol " << symbol << " at address "
        << uppercase << hex << setw(4) << setfill('0') << f->second
        << " cannot be reached from address "
        << uppercase << hex << setw(4) << setfill('0') << base_address
        << " using a signed 8-bit relative jump.";
        throw runtime_error(errorout.str());
    }

    return rel_byte;
}
