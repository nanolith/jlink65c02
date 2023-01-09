JEMU 65C02 Linker
=================

The JEMU 65C02 Linker is a stream linker that takes hex object streams and links
them into a hex stream over two passes. This linker is written in 65C02
machine code and can be run using the JEMU65C02 emulator.

Hex Streams
-----------

A hex stream is a sequence of hexadecimal pairs. This stream can be any number
of hexadecimal pairs long, but a line must start with `AXXXX`, which denotes the
starting address for the sequence in hex, or `+`, which means that the sequence
should continue from the previous line. A line that begins with `;` is a
comment, and all characters up to the next newline sequence are ignored. All
whitespace is ignored, so that hex pairs can be whitespace delimited or may run
together. Likewise, a comment may start in the middle of the line, after which
point, all subsequent bytes until the next newline are ignored.  A line that
starts with `Q` ends the hex sequence.

For example, the following hex sequence sets the A register to `27` hex and
stops the 65C02 processor (This works on WDC 65C02 or 65816 processors).

    A1000 A927              ; LDA #27
    +     DB                ; STP
    AFFFE 0010              ; 1000 is the reset vector
    Q

Object Streams
--------------

TODO ADD

Passes
------

The linker goes through two passes. In each pass, the entire object stream
should be emitted to the linker, in the same order. During the first pass, all
relocations will be computed. During the second pass, the linked hex stream will
be output.
