/**
 * \file jlink65c02/bootstrap_linker.h
 *
 * \brief The bootstrap linker for linking the final jlink65c02 linker.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#pragma once

#include <deque>
#include <map>
#include <memory>
#include <string>

namespace jlink65c02
{
    /** \brief Map of symbols to address. */
    typedef std::map<std::string, std::uint16_t> symbol_map;
    /** \brief Map of variable to zeropage offset. */
    typedef std::map<std::string, std::uint8_t> zeropage_map;
    /** \brief Map of object file name to local symbol map. */
    typedef std::map<std::string, std::shared_ptr<symbol_map>> object_local_map;

    struct bootstrap_linker
    {
        symbol_map global_symbols;
        symbol_map local_symbols;
        object_local_map object_locals;
        zeropage_map zeropage;
        std::shared_ptr<std::string> zeropage_alloc[256];
        std::string objname;
        std::deque<std::uint8_t> bytes;
        std::uint16_t deque_address;
        std::uint16_t text_address;
        std::uint16_t curr_text_address;
        std::uint16_t data_address;
        bool text_address_set;
        bool in_absolute_address;
        bool writeAddress;

        /** \brief default constructor. */
        bootstrap_linker();

        /** \brief Utility to read a byte from the input stream. */
        bool readByte(std::istream& in, bool& in_loop, std::uint8_t& byte);
        void writeLine(std::ostream& out);
        void setLineAddress(uint16_t address, std::ostream& out);

        /** \brief Perform the first linker pass using the input stream. */
        void pass1(std::istream& in, std::ostream& log);
        /** \brief Decode a line from the first pass. */
        void decodeLine1(
            char cmd, const std::string& args, bool& in_pass,
            std::ostream& log);
        /** \brief Decode an A command from the first pass. */
        void decodeACommand1(std::istream& in, std::ostream& log);
        /** \brief Decode a D command from the first pass. */
        void decodeDCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode a G command from the first pass. */
        void decodeGCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode a J command from the first pass. */
        void decodeJCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode an L command from the first pass. */
        void decodeLCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode an O command from the first pass. */
        void decodeOCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode a + command from the first pass. */
        void decodePlusCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode a Q command from the first pass. */
        void decodeQCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode an R command from the first pass. */
        void decodeRCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode an X command from the first pass. */
        void decodeXCommand1(std::istream& in, std::ostream& log);
        /** \brief Decode a Z command from the first pass. */
        void decodeZCommand1(std::istream& in, std::ostream& log);
        void pass2(std::istream& in, std::ostream& log, std::ostream& out);
        void decodeLine2(
            char cmd, const std::string& args, bool& in_pass,
            std::ostream& log, std::ostream& out);
        /** \brief Decode an A command from the second pass. */
        void decodeACommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode a D command from the second pass. */
        void decodeDCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode a G command from the second pass. */
        void decodeGCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode a J command from the second pass. */
        void decodeJCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode an L command from the second pass. */
        void decodeLCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode an O command from the second pass. */
        void decodeOCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode a + command from the second pass. */
        void decodePlusCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode a Q command from the second pass. */
        void decodeQCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode an R command from the second pass. */
        void decodeRCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode an X command from the second pass. */
        void decodeXCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
        /** \brief Decode a Z command from the second pass. */
        void decodeZCommand2(
            std::istream& in, std::ostream& log, std::ostream& out);
    };
}
