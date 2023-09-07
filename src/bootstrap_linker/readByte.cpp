/**
 * \file src/bootstrap_linker/readByte.cpp
 *
 * \brief Read a hex byte from the input stream.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <istream>
#include <jlink65c02/bootstrap_linker.h>
#include <sstream>

using namespace jlink65c02;
using namespace std;

bool bootstrap_linker::readByte(istream& in, bool& in_loop, uint8_t& byte)
{
    char val1, val2;
    unsigned int readVal;

    in >> val1;

    // skip spaces.
    if (isspace(val1))
    {
        return false;
    }
    // ignore comments.
    else if (';' == val1)
    {
        in_loop = false;
        return false;
    }
    // decode hex digits into bytes and increment address.
    else if (isxdigit(val1))
    {
        in >> val2;
        if (!isxdigit(val2))
        {
            throw runtime_error("malformed byte.");
        }

        //decode byte
        char str[] = { val1, val2, '0' };
        stringstream sin(str);
        sin >> hex >> readVal;
        byte = readVal;

        return true;
    }
    else
    {
        throw runtime_error("invalid character sequence.");
    }
}
