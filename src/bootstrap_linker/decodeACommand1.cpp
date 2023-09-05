/**
 * \file src/bootstrap_linker/decodeACommand1.cpp
 *
 * \brief Decode an A command in the first pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <istream>
#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>
#include <ostream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeACommand1(istream& in, ostream& log)
{
    bool in_loop = true;
    uint8_t byte;
    uint16_t prev_text_address;

    in >> hex >> curr_text_address;
    in_absolute_address = true;

    prev_text_address = curr_text_address;

    auto logflags = log.flags();
    log << "Set current append address to " << hex << setw(4) << setfill('0')
        << curr_text_address << endl;
    log.flags(logflags);

    while (in.good() && in_loop)
    {
        if (readByte(in, in_loop, byte))
        {
            curr_text_address += 1;
        }
    }

    if (curr_text_address != prev_text_address)
    {
        auto logflags = log.flags();
        log << "Incremented current append address to "
            << hex << setw(4) << setfill('0') << curr_text_address << endl;
        log.flags(logflags);
    }
}
