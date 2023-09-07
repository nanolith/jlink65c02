/**
 * \file src/bootstrap_linker/decodeOCommand2.cpp
 *
 * \brief Decode an O command in the second linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeOCommand2(istream& in, ostream& log, ostream& out)
{
    (void)out;

    in >> hex >> text_address;
    text_address_set = true;

    auto logflags = log.flags();
    log << "Set origin to " << hex << setw(4) << setfill('0') << text_address
        << endl;
    log.flags(logflags);
}
