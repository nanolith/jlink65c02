/**
 * \file src/bootstrap_linker/decodePlusCommand1.cpp
 *
 * \brief Decode a + command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <istream>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodePlusCommand1(istream& in, ostream& log)
{
    (void)log;
    bool in_loop = true;
    uint8_t byte;

    if (!in_absolute_address)
    {
        throw runtime_error("+ command outside of absolute address append.");
    }

    while (in.good() && in_loop)
    {
        if (readByte(in, in_loop, byte))
        {
            curr_text_address += 1;
        }
    }
}
