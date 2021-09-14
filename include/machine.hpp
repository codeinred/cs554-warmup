#pragma once

#include <array>
#include <cstdio>
#include <definitions.hpp>
#include <ins.hpp>
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

    void print_char(char c) { putchar(c); }

   public:
    machine() = default;
    /**
     * @brief Construct a new machine object with the given program
     *
     * @param program the list of instructions this machine will execute
     */
    machine(word_array program) {
        arrays.push_back(std::move(program));
        // Ensure there's an extra value padding the end
        arrays[0].push_back(0);
    }

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
            arrays[index].resize(size, 0);
            return index;
        }
    }
    void deallocate(uint index) {
        arrays[index].clear();
        deallocated.push_back(index);
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

    void run_loop() {
        uint counter = 0;
        uint const* instruction_ptr = arrays[0].data();
        for (;;) {
            instruction i1 = instruction {instruction_ptr[counter++]};
            uint opcode = i1.get_OP();
            switch (opcode) {
                case 0: OPCODE_0(i1); break;
                case 1: OPCODE_1(i1); break;
                case 2: OPCODE_2(i1); break;
                case 3: OPCODE_3(i1); break;
                case 4: OPCODE_4(i1); break;
                case 5: OPCODE_5(i1); break;
                case 6: OPCODE_6(i1); break;
                case 7: OPCODE_7(i1); break;
                case 8: OPCODE_8(i1); break;
                case 9: OPCODE_9(i1); break;
                case 10: OPCODE_10(i1); break;
                case 11: OPCODE_11(i1); break;
                case 12: OPCODE_12(i1); break;
                case 13: OPCODE_13(i1); break;
            }
        }
    }
};
} // namespace compiler
