/**
 * \file jlink65c02/config.h
 *
 * \brief Generated configuration file data for jlink65c02.
 *
 * \copyright 2023 Justin Handville.  Please see license.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#define MAKE_C_VERSION(X,Y) V ## X ## _ ## Y
#define JLINK_VERSION_SYM \
    MAKE_C_VERSION(@JLINK_VERSION_MAJOR@, @JLINK_VERSION_MINOR@)

#define JLINK_VERSION_STRING \
    "@JLINK_VERSION_MAJOR@.@JLINK_VERSION_MINOR@.@JLINK_VERSION_REL@"
