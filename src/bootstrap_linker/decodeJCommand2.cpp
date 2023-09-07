/**
 * \file src/bootstrap_linker/decodeJCommand2.cpp
 *
 * \brief Decode a J command in the second linker pass.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

void bootstrap_linker::decodeJCommand2(istream& in, ostream& log, ostream& out)
{
    in >> objname;
    log << "Linking object stream " << objname << "." << endl;

    auto f = object_locals.find(objname);
    if (object_locals.end() == f || !f->second)
    {
        stringstream errorout;
        errorout << "Could not find references for " << objname << ".";
        throw runtime_error(errorout.str());
    }

    local_symbols = *f->second;
}
