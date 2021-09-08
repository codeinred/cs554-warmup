#pragma once

#include <array>
#include <ins.hpp>
#include <vector>
#include <fmt/core.h>

namespace compiler {

using word_array = std::vector<uint>;
using array_space = std::vector<word_array>;
class machine {
    array_space arrays;
    std::vector<uint> deallocated;
    std::array<uint, 8> registers {};

   public:
    machine() = default;

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

    bool run(instruction i) {
        uint opcode = i.get_OP();
        switch (opcode) {
            case 0:
                if (!get_C_register(i)) {
                    set_A_register(i, get_B_register(i));
                }
                break;
            case 1: {
                // Opcode 1: The register A receives the value stored at offset
                // in
                // register C in the array identified by B.
                uint offset = get_C_register(i);
                uint array_index = get_B_register(i);
                set_A_register(i, arrays[array_index][offset]);
            } break;
            case 2: {
                // The array identified by A is updated at the offset in
                // register B to store the value in register C
                uint array_index = get_A_register(i);
                uint offset = get_B_register(i);
                set_C_register(i, arrays[array_index][offset]);
            } break;
            case 3:
                // The register A receives the value in register B plus the
                // value in register C, modulo 2^32.
                set_A_register(i, (get_B_register(i) + get_C_register(i)));
                break;
            case 4:
                // The register A receives the value in register B times the
                // value in register C, modulo 2^32
                set_A_register(i, (get_B_register(i) * get_C_register(i)));
                break;
            case 5:
                // The register A receives the value in register B divided by
                // the value in register C, where each quantity is treated as an
                // unsigned 32-bit number
                set_A_register(i, (get_B_register(i) / get_C_register(i)));
                break;
            case 6: {
                // Each bit in the register A receives the 1 bit if either
                // register B or register C has a 0 bit in that position.
                // Otherwise the bit in register A receives the 0 bit.

                set_A_register(i, ~(get_B_register(i) & get_C_register(i)));
            } break;
            case 7: return false;
            case 8: set_B_register(i, allocate(get_C_register(i))); break;
            case 9: deallocate(get_C_register(i)); break;
        }
        return true;
    }
};
} // namespace compiler
