/**
 * \file src/bootstrap_linker/bootstrap_linker.cpp
 *
 * \brief Constructor for the bootstrap linker.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jlink65c02/bootstrap_linker.h>

using namespace jlink65c02;
using namespace std;

bootstrap_linker::bootstrap_linker()
    : text_address(0x0000)
    , curr_text_address(0x0000)
    , data_address(0x0000)
    , text_address_set(false)
    , in_absolute_address(false)
    , writeAddress(false)
{
}
