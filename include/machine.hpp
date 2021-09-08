#pragma once

#include <array>
#include <ins.hpp>
#include <vector>

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

    void run(instruction i) {
        uint opcode = i.get_OP();
        switch (opcode) {
            case 0:
                if (!get_C_register(i)) {
                    set_A_register(i, get_B_register(i));
                }
                break;
            case 3: set_A_register(i, (get_B_register(i) + get_C_register(i))); break;
            case 4: set_A_register(i, (get_B_register(i) * get_C_register(i))); break;
            case 5: set_A_register(i, (get_B_register(i) / get_C_register(i))); break;
            case 8: set_B_register(i, allocate(get_C_register(i))); break;
            case 9: deallocate(get_C_register(i)); break;
        }
    }
};
} // namespace compiler
