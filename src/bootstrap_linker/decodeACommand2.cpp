/**
 * \file src/bootstrap_linker/decodeACommand2.cpp
 *
 * \brief Decode an A command in the second pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeACommand2(
    std::istream& in, std::ostream& log, std::ostream& out)
{
    bool in_loop = true;
    uint8_t byte;
    uint16_t prev_text_address;

    in >> hex >> curr_text_address;
    in_absolute_address = true;

    setLineAddress(curr_text_address, out);
    prev_text_address = curr_text_address;

    auto logflags = log.flags();
    log << "Set current append address to " << hex << setw(4) << setfill('0')
        << curr_text_address << endl;
    log.flags(logflags);

    while (in.good() && in_loop)
    {
        if (readByte(in, in_loop, byte))
        {
            bytes.push_back(byte);
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

    while (bytes.size() > 32)
    {
        writeLine(out);
    }
}
