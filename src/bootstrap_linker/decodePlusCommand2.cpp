/**
 * \file src/bootstrap_linker/decodePlusCommand2.cpp
 *
 * \brief Decode a + command in the second pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodePlusCommand2(
    std::istream& in, std::ostream& log, std::ostream& out)
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
            bytes.push_back(byte);
            curr_text_address += 1;
        }
    }

    while (bytes.size() > 32)
    {
        writeLine(out);
    }
}
