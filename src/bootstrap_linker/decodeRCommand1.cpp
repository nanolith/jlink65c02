/**
 * \file src/bootstrap_linker/decodeRCommand1.cpp
 *
 * \brief Decode a R command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <istream>
#include <jlink65c02/bootstrap_linker.h>
#include <ostream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeRCommand1(istream& in, ostream& log)
{
    char reference_type;
    string symbol;

    in >> reference_type;
    in >> symbol;

    switch (reference_type)
    {
        case 'A':
        case 'a':
            log << "absolute reference for " << symbol << "." << endl;
            if (in_absolute_address)
                curr_text_address += 2;
            else
                text_address += 2;
            break;

        case 'Z':
        case 'z':
            log << "zeropage reference for " << symbol << "." << endl;
            if (in_absolute_address)
                curr_text_address += 1;
            else
                text_address += 1;
            break;

        default:
            throw runtime_error("unknown reference type");
    }
}
