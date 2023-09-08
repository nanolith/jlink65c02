/**
 * \file src/bootstrap_linker/decodeRCommand2.cpp
 *
 * \brief Decode an R command in the second linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeRCommand2(istream& in, ostream& log, ostream& out)
{
    char reference_type;
    string symbol;
    uint16_t absolute_address;
    uint16_t addr;
    uint8_t zeropage_address;
    int8_t relative_address;
    auto logflags = log.flags();

    in >> reference_type;
    in >> symbol;

    // compute the current address.
    if (in_absolute_address)
        addr = curr_text_address;
    else
        addr = text_address;

    switch (reference_type)
    {
        case 'A':
        case 'a':
            absolute_address = lookupSymbol(symbol);

            log << "absolute reference for " << symbol << " is "
                << setw(4) << setfill('0') << uppercase << hex
                << absolute_address << "." << endl;

            bytes.push_back(absolute_address & 0x00FF);
            bytes.push_back(absolute_address >> 8);

            if (in_absolute_address)
                curr_text_address += 2;
            else
                text_address += 2;
            break;

        case 'R':
        case 'r':
            relative_address = lookupRelativeAddress(symbol, addr + 1);

            log << "relative reference for " << symbol << " is "
                << (int)relative_address << " bytes." << endl;

            bytes.push_back(relative_address);

            if (in_absolute_address)
                curr_text_address += 1;
            else
                text_address += 1;
            break;

        case 'Z':
        case 'z':
            zeropage_address = lookupZeroPageSymbol(symbol);

            log << "zeropage reference for " << symbol << " is "
                << setw(2) << setfill('0') << uppercase << hex
                << zeropage_address << "." << endl;

            bytes.push_back(zeropage_address);

            if (in_absolute_address)
                curr_text_address += 1;
            else
                text_address += 1;
            break;

        default:
            throw runtime_error("unknown reference type");
    }

    while (bytes.size() > 32)
    {
        writeLine(out);
    }

    log.flags(logflags);
}
