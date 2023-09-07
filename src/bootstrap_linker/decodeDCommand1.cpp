/**
 * \file src/bootstrap_linker/decodeDCommand1.cpp
 *
 * \brief Decode a D command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <istream>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeDCommand1(istream& in, ostream& log)
{
    in >> hex >> data_address;

    auto logflags = log.flags();
    log << "Set data offset to "
        << uppercase << hex << setw(4) << setfill('0') << data_address << endl;
    log.flags(logflags);
}
