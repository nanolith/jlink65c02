/**
 * \file src/bootstrap_linker/decodeZCommand1.cpp
 *
 * \brief Decode a Z command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeZCommand1(istream& in, ostream& log)
{
    uint16_t zeroref;
    string symbol;
    stringstream errorout;

    in >> hex >> zeroref;
    zeroref &= 0xFF;

    if (!!(zeropage_alloc[zeroref]))
    {
        errorout << "zeropage reference "
                 << uppercase << hex << setw(2) << setfill('0') << zeroref
                 << " already defined.";
        throw runtime_error(errorout.str());
    }

    in >> symbol;

    if ("" == symbol || ';' == symbol[0])
    {
        throw runtime_error("invalid symbol name.");
    }

    if (zeropage.count(symbol) > 0)
    {
        errorout << "symbol " << symbol << " already defined in zeropage.";
        throw runtime_error(errorout.str());
    }

    zeropage[symbol] = zeroref;
    zeropage_alloc[zeroref] = make_shared<string>(symbol);

    auto logflags = log.flags();
    log << "zeropage reference " << symbol << " defined at "
        << uppercase << hex << setw(2) << setfill('0') << zeroref << "."
        << endl;
    log.flags(logflags);
}
