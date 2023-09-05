/**
 * \file src/bootstrap_linker/decodeXCommand1.cpp
 *
 * \brief Decode a X command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <ostream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeXCommand1(istream& in, ostream& log)
{
    (void)in;

    log << "End of pass." << endl;
}
