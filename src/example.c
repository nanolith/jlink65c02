/**
 * \file src/main.c
 *
 * \brief Main entry point for jlink utility.
 *
 * \copyright 2023 Justin Handville.  Please see LICENSE.txt in this
 * distribution for the license terms under which this software is distributed.
 */

#if 0

#include <jemu65c02/jemu65c02.h>
#include <stdio.h>
#include <string.h>

JEMU_IMPORT_jemu65c02;

/* forward decls for mem read / mem write callbacks. */
static status mem_read(void* varr, uint16_t addr, uint8_t* val);
static status mem_write(void* varr, uint16_t addr, uint8_t val);

uint8_t flags_FFE2 = 0;

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
    mem[0x1000] = 0xA2; /* LDX #00 */
    mem[0x1001] = 0x00;
    mem[0x1002] = 0xBD; /* LDA $2000, X */
    mem[0x1003] = 0x00;
    mem[0x1004] = 0x20;
    mem[0x1005] = 0xC9; /* CMP A, #00 */
    mem[0x1006] = 0x00;
    mem[0x1007] = 0xF0; /* BEQ #06 */
    mem[0x1008] = 0x06;
    mem[0x1009] = 0x8D; /* STA $FFE1 */
    mem[0x100A] = 0xE1;
    mem[0x100B] = 0xFF;
    mem[0x100C] = 0xE8; /* INX */
    mem[0x100D] = 0x80; /* BRA -13. */
    mem[0x100E] = -13;
    mem[0x100F] = 0xDB; /* STP */

    /* string output by program. */
    const char* hellostr = "Not yet implemented.\n";
    strcpy((char*)(mem + 0x2000), hellostr);

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
    int ch;
    const uint8_t* arr = (const uint8_t*)varr;

    switch (addr)
    {
        case 0xFFE0:
            /* read a character from standard input. */
            ch = fgetc(stdin);

            /* handle the status register. */
            if (EOF == ch)
            {
                flags_FFE2 &= ~1;
            }
            else
            {
                flags_FFE2 |= 1;
            }

            /* write the low part of this value to the read value. */
            *val = ch;
            break;

        case 0xFFE1:
            *val = 0x00;
            break;

        case 0xFFE2:
            *val = flags_FFE2;
            break;

        default:
            *val = arr[addr];
            break;
    }

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

    switch (addr)
    {
        case 0xFFE0:
        case 0xFFE2:
            break;

        case 0xFFE1:
            fputc(val, stdout);
            break;

        default:
            arr[addr] = val;
            break;
    }

    return STATUS_SUCCESS;
}
#endif
