/**
 * \file src/bootstrap_linker/decodeXCommand2.cpp
 *
 * \brief Decode an X command in the second linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <ostream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeXCommand2(istream& in, ostream& log, ostream& out)
{
    (void)in;

    log << "Finalizing link." << endl;

    while (!bytes.empty())
    {
        writeLine(out);
    }
}
