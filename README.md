JEMU 65C02 Linker
=================

The JEMU 65C02 Linker is a stream linker that takes hex object streams and links
them into a hex stream over two passes. This linker is written in 65C02
machine code and can be run using the JEMU65C02 emulator.

The linker is actually written in the object stream format below. In order to
link this object stream into a binary that can be run in a 65c02 emulator, a
partial C implementation has also been written. This C implementation allows us
to bootstrap the linker using a C compiler and the jemu65c02 emulator.

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
starts with `X` ends the hex sequence.

For example, the following hex sequence sets the A register to `27` hex and
stops the 65C02 processor (This works on WDC 65C02 or 65816 processors).

    A1000 A927              ; LDA #27
    +     DB                ; STP
    AFFFE 0010              ; 1000 is the reset vector
    X

Object Streams
--------------

Much can be done with an hex stream, but the downside is that absolute addresses
must be precomputed and it's impossible to reuse functions between projects. An
object stream provides some symbolic linkage to make it easier to deal with both
address computation and function re-use.

The first added feature is the `J` prefix. This is the "start obJect" prefix.
When this prefix is encountered, the linker resets for the given object
sequence. Globals are remembered between resets, but locals are not. Object
sequences are kept in memory one at a time, and due to the limited memory in a
65C02 processor, each object sequence must be kept short, on the order of a few
kilobytes.

The next added feature is the `OXXXX` prefix. This represents the origin for a
given sequence. Typically, only one object in a stream will have this prefix. It
works much like `AXXXX`, only this position is "sticky", meaning that future
functions can be appended to this area. There is also the `DXXXX` prefix, which
provides a "sticky" location for data. Sequences that don't care about where
they are linked can use the `Q` prefix, which will cause the sequence to be
appended somewhere after the origin, and the `E` prefix, which will cause the
sequence to be appened somewhere after the last `D` prefix. Both the `O` and `D`
prefixes are global, meaning that they stick around between object sequences.
The very first object sequence in a stream should define both.

Labels provide a means of locating a sequence in the object stream. There are
two kinds of labels: global labels and local labels. A label starts with the `G`
prefix or `L` prefix, followed by optional whitespace, and then the symbol name.
A global label is saved in the label tree, however, all local labels are
"forgotten" when the next start object sequence prefix is encountered.

Labels can be referenced using the `RA` and `RR` prefixes. Both label references
should include the symbol being referenced. The `RA` prefix emits an absolute
address for the given symbol, and the `RR` prefix emits a signed 8-bit relative
address for the given symbol. As such, `RR` prefixes are generally relegated to
`L` labels in a given object sequence.

Zero-page labels are used to reference zero-page addresses. They are denoted
using the `ZXX` prefix, followed by optional whitespace and a symbolic name. The
`RZ` prefix can be used to reference this zero-page label, at which point, the
exact byte used to denote this zero-page reference will be emitted. Zero-page
labels are global.

The `X` command should be used at the end of all object streams to note the end
of a pass.

Here is an example of an object stream consisting of a main program (with `O`
and `D` prefixes) that calls a library function. The library function adds two
32-bit numbers. This function is inefficient, but the point is to show what an
object stream looks like.

    J main
    O0200
    D2000
    Z00 NUMA0               ; start of NUMA -- 32-bit number.
    Z01 NUMA1
    Z02 NUMA2
    Z03 NUMA3
    Z04 NUMB0               ; start of NUMB -- 32-bit number.
    Z05 NUMB1
    Z06 NUMB2
    Z07 NUMB3
    AFFFE                   ; The reset vector starts at main
    RA main
    G main                  ; main program starts at origin
    Q     A901              ; LDA #01 -- make NUMA0 equal to 1
    Q     B5                ; STA $NUMA0
    RZ    NUMA0
    Q     64                ; STZ $NUMA1
    RZ    NUMA1
    Q     64                ; STZ $NUMA2
    RZ    NUMA2
    Q     64                ; STZ $NUMA3
    RZ    NUMA3
    Q     A902              ; LDA #02 -- make NUMB0 equal to 2
    Q     B5                ; STA $NUMB0
    RZ    NUMB0
    Q     64                ; STZ $NUMB1
    RZ    NUMB1
    Q     64                ; STZ $NUMB2
    RZ    NUMB2
    Q     64                ; STZ $NUMB3
    RZ    NUMB3
    Q     A9                ; LDA #NUMA0 -- NUMA0 is our first argument
    RZ    NUMA0
    Q     48                ; PHA
    Q     A9                ; LDA #NUMB0 -- NUMB0 is our second argument
    RZ    NUMB0
    Q     48                ; PHA
    Q     20                ; JSR add32
    RA    add32
    Q     DB                ; STP
    J add32                 ; start of add32 object
    G add32                 ; add32 function starts here.
    Q     D8                ; CLD -- treat this as a binary addition
    Q     FA                ; PLY -- Y is set to our second argument
    Q     B600              ; LDX $00,Y -- read the num B digit 0
    Q     8A                ; TXA -- save it to A
    Q     FA                ; PLX -- X is set to our first argument
    Q     18                ; CLC -- at the start of addition, clear the carry.
    Q     7500              ; ADC $00,X -- add num B and num A digit 0
    Q     9500              ; STA $00,X -- save the result to num A digit 0
    Q     DA                ; PHX -- save X
    Q     B601              ; LDX $01,Y -- read num B digit 1
    Q     8A                ; TXA -- save it to A
    Q     FA                ; PLX -- restore X
    Q     7501              ; ADC $01,X -- add num B and num A digit 1
    Q     9501              ; STA $01,X -- save the result to num A digit 1
    Q     DA                ; PHX -- save X
    Q     B602              ; LDX $02,Y -- read num B digit 2
    Q     8A                ; TXA -- save it to A
    Q     FA                ; PLX -- restore X
    Q     7502              ; ADC $02,X -- add num B and num A digit 2
    Q     9502              ; STA $02,X -- save the result to num A digit 2
    Q     DA                ; PHX -- save X
    Q     B603              ; LDX $03,Y -- read num B digit 3
    Q     8A                ; TXA -- save it to A
    Q     FA                ; PLX -- restore X
    Q     7503              ; ADC $03,X -- add num B and num A digit 3
    Q     9503              ; STA $03,X -- save the result to num A digit 3
    Q     60                ; RTS -- return from subroutine
    X

The output of this stream looks like this (remember to feed it to the linker
twice):

    AFFFE 0002
    A0200 A901B500640164026403A902B504640564066407A90048A90448201E02DB1E02
    +     D8FAB6008AFA1875009500DAB6018AFA75019501DAB6028AFA75029502DAB603
    +     8AFA7503950360

Passes
------

The linker goes through two passes. In each pass, the entire object stream
should be emitted to the linker, in the same order. During the first pass, all
relocations will be computed. During the second pass, the linked hex stream will
be output.

Program Runner
--------------

The program runner is a simple C program that reads the linker as a hex stream
and converts it into a 65C02 image, which is run using the JEMU65c02 emulator.

Standard I/O Device
-------------------

The program runner creates a simple virtual device that it attaches to the 65C02
emulator, which acts as a standard I/O interface. This device provides three
registers: a latched read register, a latched write register, and a status
register. Reads from the latched read register will perform a blocking read of
standard input. Writes to the latched write register will perform a blocking
write to standard output.  Reads from the status register will indicate whether
the standard input stream has reached EOF. The Standard I/O device is attached
at memory location `FFE0`, with the read register at `FFE0`, the write register
at `FFE1`, and the status register at `FFE2`.

The status register sets bit 0 to 1 if the last read was successful and to 0 if
the last read was unsuccessful. This register should be checked after each read
to detect an EOF or error condition.
