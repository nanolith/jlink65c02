/**
 * \file src/bootstrap_linker/decodeQCommand2.cpp
 *
 * \brief Decode a Q command in the second linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <istream>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeQCommand2(istream& in, ostream& log, ostream& out)
{
    (void)log;
    bool in_loop = true;
    uint8_t byte;

    if (in_absolute_address)
    {
        in_absolute_address = false;
        setLineAddress(text_address, out);
    }

    while (in.good() && in_loop)
    {
        if (readByte(in, in_loop, byte))
        {
            bytes.push_back(byte);
            text_address += 1;
        }
    }

    while (bytes.size() > 32)
    {
        writeLine(out);
    }
}
