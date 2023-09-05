/**
 * \file src/bootstrap_linker/decodeJCommand1.cpp
 *
 * \brief Decode a J command in the first linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iomanip>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeJCommand1(istream& in, ostream& log)
{
    if ("" != objname)
    {
        log << "Caching locals for " << objname << "." << endl;
        object_locals[objname] = make_shared<symbol_map>(local_symbols);
    }

    in >> objname;
    log << "Starting object stream " << objname << "." << endl;

    local_symbols.clear();
}
