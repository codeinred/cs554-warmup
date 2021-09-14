

// Opcode 0: The register A receives the value in register
// B, unless the register C contains 0.
#define OPCODE_0(INS)                                                          \
    {                                                                          \
        if (get_C_register(INS)) {                                             \
            set_A_register(INS, get_B_register(INS));                          \
        }                                                                      \
    }


// Opcode 1: The register A receives the value stored at
// offset in register C in the array identified by B.
#define OPCODE_1(INS)                                                          \
    {                                                                          \
        uint offset = get_C_register(INS);                                     \
        uint array_index = get_B_register(INS);                                \
        set_A_register(INS, arrays[array_index][offset]);                      \
    }


// Opcode 2: The array identified by A is updated at the
// offset in register B to store the value in register C
#define OPCODE_2(INS)                                                          \
    {                                                                          \
        uint array_index = get_A_register(INS);                                \
        uint offset = get_B_register(INS);                                     \
        arrays[array_index][offset] = get_C_register(INS);                     \
    }


// Opcode 3: The register A receives the value in register B
// plus the value in register C, modulo 2^32.
#define OPCODE_3(INS)                                                          \
    { set_A_register(INS, (get_B_register(INS) + get_C_register(INS))); }


// Opcode 4: The register A receives the value in register B
// times the value in register C, modulo 2^32
#define OPCODE_4(INS)                                                          \
    { set_A_register(INS, (get_B_register(INS) * get_C_register(INS))); }


// Opcode 5: The register A receives the value in register B
// divided by the value in register C, where each quantity
// is treated as an unsigned 32-bit number
#define OPCODE_5(INS)                                                          \
    { set_A_register(INS, (get_B_register(INS) / get_C_register(INS))); }

// Opcode 6: Each bit in the register A receives the 1 bit
// if either register B or register C has a 0 bit in that
// position. Otherwise the bit in register A receives the 0
// bit.

#define OPCODE_6(INS)                                                          \
    { set_A_register(INS, ~(get_B_register(INS) & get_C_register(INS))); }


// Opcode 7: The machine stops computation
#define OPCODE_7(INS)                                                          \
    { return; }

// Opcode 8: A new array is created; the value in the
// register C gives the number of words in the new array.
// This new array is zero-initialized. A bit pattern not
// consisting of exclusively the 0 bit, and that identifies
// no other active allocated array, is placed in the B
// register, and it identifies the new array.
#define OPCODE_8(INS)                                                          \
    { set_B_register(INS, allocate(get_C_register(INS))); }


// Opcode 9: The array identified by the register C is
// deallocated (freed). Future allocations may then reuse
// that identifier.
#define OPCODE_9(INS)                                                          \
    { deallocate(get_C_register(INS)); }


// Opcode 10: Output. The value in the register C is
// displayed on the console. Only values in the range 0–255
// are allowed.
#define OPCODE_10(INS)                                                         \
    { print_char(char(get_C_register(INS))); }


// Opcode 11: Input. The machine waits for input on the
// console. When input arrives, the register C is loaded
// with the input, which must be in the range 0–255. If the
// end of input has been signaled, then the register C is
// filled with all 1’s.
#define OPCODE_11(INS)                                                         \
    {                                                                          \
        int ch = getchar();                                                    \
        if (ch == EOF) {                                                       \
            set_C_register(INS, ~0u);                                          \
        } else {                                                               \
            set_C_register(INS, uint(ch) & 0xffu);                             \
        }                                                                      \
    }


// Opcode 12: The array identified by the B register is
// duplicated and the duplicate replaces the ‘0’ array,
// regardless of size. The program counter is updated to
// indicate the word of this array that is described by the
// offset given in C, where the value 0 denotes the first
// word, 1 the second, etc.
#define OPCODE_12(INS)                                                         \
    {                                                                          \
        uint array_index = get_B_register(INS);                                \
        if (array_index != 0) {                                                \
            arrays[0] = arrays[array_index];                                   \
            instruction_ptr = arrays[0].data();                                \
        }                                                                      \
        counter = get_C_register(INS);                                         \
    }


// Opcode 13: The value in bits 0:24 is loaded into the
// register A (given by bits 25:27)
#define OPCODE_13(INS)                                                         \
    { set_special_register(INS, INS.get_special_value()); }

#define OPCODE_14(INS)
#define OPCODE_15(INS)
