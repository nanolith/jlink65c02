/**
 * \file src/bootstrap_linker/decodeQCommand1.cpp
 *
 * \brief Decode a Q command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <istream>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeQCommand1(istream& in, ostream& log)
{
    (void)log;
    bool in_loop = true;
    uint8_t byte;

    in_absolute_address = false;

    while (in.good() && in_loop)
    {
        if (readByte(in, in_loop, byte))
        {
            text_address += 1;
        }
    }
}
