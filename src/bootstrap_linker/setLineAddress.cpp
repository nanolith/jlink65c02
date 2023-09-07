/**
 * \file src/bootstrap_linker/setLineAddress.cpp
 *
 * \brief Set the line address, triggering the writeAddress flag.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::setLineAddress(uint16_t address, ostream& out)
{
    while (!bytes.empty())
    {
        writeLine(out);
    }

    writeAddress = true;
    deque_address = address;
}
