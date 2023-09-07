/**
 * \file src/bootstrap_linker/writeLine.cpp
 *
 * \brief Write a line of bytes to the output stream.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::writeLine(std::ostream& out)
{
    auto outflags = out.flags();

    if (writeAddress)
    {
        out << "A" << hex << setw(4) << setfill('0') << deque_address << " ";
        writeAddress = false;
    }
    else
    {
        out << "+     ";
    }

    for (size_t i = 0; i < 32 && !bytes.empty(); ++i)
    {
        out << hex << setw(2) << setfill('0') << bytes.front();
        bytes.pop_front();
        ++deque_address;
    }
    out << endl;
    out.flags(outflags);
}
