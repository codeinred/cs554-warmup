#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <ins.hpp>

template <>
struct fmt::formatter<compiler::instruction> : fmt::formatter<uint32_t> {
    using base = fmt::formatter<uint32_t>;
    using instruction = compiler::instruction;

    void print_halt(auto& ctx, instruction i, std::string_view hint) {
        fmt::format_to(ctx.out(), "{}\t\t(op {})", hint, i.get_OP());
    }
    void print_abc(auto& ctx, instruction i, std::string_view hint) {
        fmt::format_to(
            ctx.out(),
            "{} A={} B={} C={}\t\t(op {})",
            hint,
            i.get_A(),
            i.get_B(),
            i.get_C(),
            i.get_OP());
    }
    void print_bc(auto& ctx, instruction i, std::string_view hint) {
        fmt::format_to(
            ctx.out(),
            "{} B={} C={}\t\t(op {})",
            hint,
            i.get_B(),
            i.get_C(),
            i.get_OP());
    }
    void print_c(auto& ctx, instruction i, std::string_view hint) {
        fmt::format_to(
            ctx.out(), "{} C={}\t\t(op {})", hint, i.get_C(), i.get_OP());
    }
    void print_special(auto& ctx, instruction i, std::string_view hint) {
        fmt::format_to(
            ctx.out(),
            "{} S={} {}\t\t(op {})",
            hint,
            i.get_special(),
            i.get_special_value(),
            i.get_OP());
    }
    template <typename FormatContext>
    auto format(compiler::instruction i, FormatContext& ctx)
        -> decltype(ctx.out()) {

        uint32_t opcode = i.get_OP();

        switch (opcode) {
            case 0:
                // Opcode 0: The register A receives the value in register B,
                // unless the register C contains 0.

                print_abc(ctx, i, "cmov  ");
                break;
            case 1:
                // Opcode 1: The register A receives the value stored at offset
                // in register C in the array identified by B.

                print_abc(ctx, i, "load  ");
                break;
            case 2:
                // Opcode 2: The array identified by A is updated at the offset
                // in register B to store the value in register C

                print_abc(ctx, i, "store ");
                break;
            case 3:
                // Opcode 3: The register A receives the value in register B
                // plus the value in register C, modulo 2^32.

                print_abc(ctx, i, "add   ");
                break;

            case 4:
                // Opcode 4: The register A receives the value in register B
                // times the value in register C, modulo 2^32

                print_abc(ctx, i, "mul   ");
                break;

            case 5:
                // Opcode 5: The register A receives the value in register B
                // divided by the value in register C, where each quantity is
                // treated as an unsigned 32-bit number

                print_abc(ctx, i, "div   ");
                break;

            case 6:
                // Opcode 6: Each bit in the register A receives the 1 bit if
                // either register B or register C has a 0 bit in that position.
                // Otherwise the bit in register A receives the 0 bit.

                print_abc(ctx, i, "xor   ");
                break;
            case 7: print_halt(ctx, i, "halt  "); break;
            case 8:
                // Opcode 8: A new array is created; the value in the register C
                // gives the number of words in the new array. This new array is
                // zero-initialized. A bit pattern not consisting of exclusively
                // the 0 bit, and that identifies no other active allocated
                // array, is placed in the B register, and it identifies the new
                // array.

                print_bc(ctx, i, "alloc ");
                break;
            case 9:
                // Opcode 9: The array identified by the register C is
                // deallocated (freed). Future allocations may then reuse that
                // identifier.

                print_c(ctx, i, "free  ");
                break;
            case 10:
                // Opcode 10: Output. The value in the register C is displayed
                // on the console. Only values in the range 0–255 are allowed.

                print_c(ctx, i, "output");
                break;
            case 11:
                // Opcode 11: Input. The machine waits for input on the console.
                // When input arrives, the register C is loaded with the input,
                // which must be in the range 0–255. If the end of input has
                // been signaled, then the register C is filled with all 1’s.

                print_c(ctx, i, "input ");
                break;
            case 12:
                // Opcode 12: The array identified by the B register is
                // duplicated and the duplicate replaces the ‘0’ array,
                // regardless of size. The program counter is updated to
                // indicate the word of this array that is described by the
                // offset given in C, where the value 0 denotes the first word,
                // 1 the second, etc.

                print_bc(ctx, i, "load program");
                break;
            case 13:
                // Opcode 13: The value in bits 0:24 is loaded into the register
                // A (given by bits 25:27)

                print_special(ctx, i, "load  ");
                break;
            default:
                // Used for operations that aren't recognized
                fmt::format_to(
                    ctx.out(),
                    "[unknown] 0x{:x}\t\t(op {})",
                    i.code,
                    i.get_OP());
                break;
        }
        return ctx.out();
    }
};
