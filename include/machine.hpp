#pragma once

#include <array>
#include <fmt/core.h>
#include <ins.hpp>
#include <iostream>
#include <vector>

namespace compiler {
using word_array = std::vector<uint>;
using array_space = std::vector<word_array>;

struct new_state {
    uint counter = 0;
    bool halted = false;

    operator bool() const { return !halted; }
};

constexpr new_state halt_state = new_state {0, true};

class machine {
    array_space arrays;
    std::vector<uint> deallocated;
    std::array<uint, 8> registers {};

   public:
    machine() = default;
    /**
     * @brief Construct a new machine object with the given program
     *
     * @param program the list of instructions this machine will execute
     */
    machine(word_array program) { arrays.push_back(std::move(program)); }

    /**
     * @brief Allocation works by:
     *
     * - checking if there are any deallocated spaces
     * - Creating an array in the formerly deallocated space (if there was one)
     * - Otherwise, we allocate a new array at the end of the list of arrays
     * - Either way, we return the index.
     *
     * @param size The size of the new array to allocate
     * @return uint The index of the newly allocated array
     */
    uint allocate(uint size) {
        if (deallocated.empty()) {
            arrays.push_back(word_array(size, 0));
            return arrays.size() - 1;
        } else {
            uint index = deallocated.back();
            deallocated.pop_back();
            arrays.at(index) = word_array(size, 0);
            return index;
        }
    }
    void deallocate(uint index) {
        if (index == arrays.size() - 1) {
            arrays.pop_back();
        } else {
            arrays.at(index) = word_array();
            deallocated.push_back(index);
        }
    }
    uint get_A_register(instruction i) const { return registers[i.get_A()]; }
    uint get_B_register(instruction i) const { return registers[i.get_B()]; }
    uint get_C_register(instruction i) const { return registers[i.get_C()]; }

    void set_A_register(instruction i, uint value) {
        registers[i.get_A()] = value;
    }
    void set_B_register(instruction i, uint value) {
        registers[i.get_B()] = value;
    }
    void set_C_register(instruction i, uint value) {
        registers[i.get_C()] = value;
    }
    void set_special_register(instruction i, uint value) {
        registers[i.get_special()] = value;
    }
    instruction get_instruction(uint counter) {
        return instruction {arrays[0][counter]};
    }
    new_state run(uint counter) {
        instruction i = get_instruction(counter);
        uint opcode = i.get_OP();
        switch (opcode) {
            case 0:
                // Opcode 0: The register A receives the value in register B,
                // unless the register C contains 0.

                if (!get_C_register(i)) {
                    set_A_register(i, get_B_register(i));
                }
                break;
            case 1: {
                // Opcode 1: The register A receives the value stored at offset
                // in register C in the array identified by B.

                uint offset = get_C_register(i);
                uint array_index = get_B_register(i);
                set_A_register(i, arrays[array_index][offset]);
            } break;
            case 2: {
                // Opcode 2: The array identified by A is updated at the offset
                // in register B to store the value in register C

                uint array_index = get_A_register(i);
                uint offset = get_B_register(i);
                arrays[array_index][offset] = get_C_register(i);
            } break;
            case 3:
                // Opcode 3: The register A receives the value in register B
                // plus the value in register C, modulo 2^32.

                set_A_register(i, (get_B_register(i) + get_C_register(i)));
                break;
            case 4:
                // Opcode 4: The register A receives the value in register B
                // times the value in register C, modulo 2^32

                set_A_register(i, (get_B_register(i) * get_C_register(i)));
                break;
            case 5:
                // Opcode 5: The register A receives the value in register B
                // divided by the value in register C, where each quantity is
                // treated as an unsigned 32-bit number

                set_A_register(i, (get_B_register(i) / get_C_register(i)));
                break;
            case 6: {
                // Opcode 6: Each bit in the register A receives the 1 bit if
                // either register B or register C has a 0 bit in that position.
                // Otherwise the bit in register A receives the 0 bit.

                set_A_register(i, ~(get_B_register(i) & get_C_register(i)));
            } break;
            case 7:
                // Opcode 7: The machine stops computation
                return halt_state;
            case 8:
                // Opcode 8: A new array is created; the value in the register C
                // gives the number of words in the new array. This new array is
                // zero-initialized. A bit pattern not consisting of exclusively
                // the 0 bit, and that identifies no other active allocated
                // array, is placed in the B register, and it identifies the new
                // array.

                set_B_register(i, allocate(get_C_register(i)));
                break;
            case 9:
                // Opcode 9: The array identified by the register C is
                // deallocated (freed). Future allocations may then reuse that
                // identifier.

                deallocate(get_C_register(i));
                break;
            case 10: {
                // Opcode 10: Output. The value in the register C is displayed
                // on the console. Only values in the range 0–255 are allowed.

                fmt::print("{}", char(get_C_register(i)));
            } break;
            case 11: {
                // Opcode 11: Input. The machine waits for input on the console.
                // When input arrives, the register C is loaded with the input,
                // which must be in the range 0–255. If the end of input has
                // been signaled, then the register C is filled with all 1’s.

                char c;
                if (std::cin >> c) {
                    set_C_register(i, c);
                } else {
                    set_C_register(i, ~0u);
                }
            } break;
            case 12: {
                // Opcode 12: The array identified by the B register is
                // duplicated and the duplicate replaces the ‘0’ array,
                // regardless of size. The program counter is updated to
                // indicate the word of this array that is described by the
                // offset given in C, where the value 0 denotes the first word,
                // 1 the second, etc.

                uint array_index = get_B_register(i);
                arrays[0] = arrays[array_index];
                return new_state {get_C_register(i), false};
            } break;
            case 13: {
                // Opcode 13: The value in bits 0:24 is loaded into the register
                // A (given by bits 25:27)

                set_special_register(i, i.get_special_value());
            } break;
        }
        return new_state {counter + 1, false};
    }

    void run_loop(uint initial_counter = 0) {
        uint counter = initial_counter;
        while (new_state state = run(counter)) {
            counter = state.counter;

            // If counter is at the end of the instruction array, halt
            if (counter == arrays[0].size())
                break;
        }
    }
};
} // namespace compiler
