/**
 * \file src/main.c
 *
 * \brief Main entry point for jlink utility.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#include <jemu65c02/jemu65c02.h>
#include <stdio.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

/* forward decls for mem read / mem write callbacks. */
static status mem_read(void* varr, uint16_t addr, uint8_t* val);
static status mem_write(void* varr, uint16_t addr, uint8_t val);

/**
 * \brief Main entry point for jlink.
 *
 * \param argc      The number of arguments passed to this binary.
 * \param argv      The argument vector.
 *
 * \returns 0 on success and non-zero on error.
 */
int main(int argc, char* argv[])
{
    j65c02* inst;
    status retval;
    uint8_t mem[65536];

    (void)argc;
    (void)argv;

    /* clear memory. */
    memset(mem, 0, sizeof(mem));

    /* TODO - read linker program. */
    mem[0xFFFC] = 0x00;
    mem[0xFFFD] = 0x10;
    mem[0x1000] = 0xDB;

    /* create the j65c02 instance. */
    retval =
        j65c02_create(
            &inst, &mem_read, &mem_write, mem,
            JEMU_65c02_PERSONALITY_WDC,
            JEMU_65c02_EMULATION_MODE_STRICT);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error initializing emulator instance.\n");
        return 1;
    }

    /* reset the processor. */
    retval = j65c02_reset(inst);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error resetting emulator instance.\n");
        return 1;
    }

    /* run the program. */
    while (!j65c02_stopped_flag_get(inst))
    {
        /* run the program for 10k cycles. */
        retval = j65c02_run(inst, 10000);
        if (STATUS_SUCCESS != retval)
        {
            fprintf(stderr, "Error running emulator instance.\n");
            return 1;
        }
    }

    /* release the emulator instance. */
    retval = j65c02_release(inst);
    if (STATUS_SUCCESS != retval)
    {
        fprintf(stderr, "Error releasing emulator instance.\n");
        return 1;
    }

    /* program ran successfully. */
    return 0;
}

/**
 * \brief Simulate a memory read for the 65C02 emulator.
 *
 * Use global stdin for the standard I/O device.
 *
 * \param varr      The memory array for the memory read.
 * \param addr      The address to read.
 * \param val       Pointer to receive the read value.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static status mem_read(void* varr, uint16_t addr, uint8_t* val)
{
    const uint8_t* arr = (const uint8_t*)varr;

    *val = arr[addr];

    return STATUS_SUCCESS;
}

/**
 * \brief Simulate a memory write for the 65C02 emulator.
 *
 * Use global stdout for the standard I/O device.
 *
 * \param varr      The memory array for the memory write.
 * \param addr      The address to write.
 * \param val       The value to write to memory.
 *
 * \returns a status code indicating success or failure.
 *      - STATUS_SUCCESS on success.
 *      - a non-zero error code on failure.
 */
static status mem_write(void* varr, uint16_t addr, uint8_t val)
{
    uint8_t* arr = (uint8_t*)varr;

    arr[addr] = val;

    return STATUS_SUCCESS;
}
