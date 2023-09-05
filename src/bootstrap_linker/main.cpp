/**
 * \file src/main.cpp
 *
 * \brief Partial implementation of jlink to link the real implementation.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <iostream>
#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

/**
 * \brief Main entry point for the partial implementation of jlink.
 *
 * \param argc      The number of arguments passed to this binary.
 * \param argv      The argument vector.
 *
 * \returns 0 on success and non-zero on error.
 */
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    bootstrap_linker inst;

    try
    {
        inst.pass1(cin, cerr);
    } catch (runtime_error& e)
    {
        cerr << "ERROR: " << e.what() << endl;
        return 1;
    }

    return 0;
}
