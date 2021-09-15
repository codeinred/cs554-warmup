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
    void run_loop_vectorized() {
        uint counter = 0;
        uint const* instruction_ptr = arrays[0].data();
        for (;;) {
            instruction i1 = instruction {instruction_ptr[counter]};
            instruction i2 = instruction {instruction_ptr[counter + 1]};
            counter += 2;
            uint opcode = i1.get_OP() * 16 + i2.get_OP();
            switch (opcode) {
                case 0:
                    OPCODE_0(i1);
                    OPCODE_0(i2);
                    break;
                case 1:
                    OPCODE_0(i1);
                    OPCODE_1(i2);
                    break;
                case 2:
                    OPCODE_0(i1);
                    OPCODE_2(i2);
                    break;
                case 3:
                    OPCODE_0(i1);
                    OPCODE_3(i2);
                    break;
                case 4:
                    OPCODE_0(i1);
                    OPCODE_4(i2);
                    break;
                case 5:
                    OPCODE_0(i1);
                    OPCODE_5(i2);
                    break;
                case 6:
                    OPCODE_0(i1);
                    OPCODE_6(i2);
                    break;
                case 7:
                    OPCODE_0(i1);
                    OPCODE_7(i2);
                    break;
                case 8:
                    OPCODE_0(i1);
                    OPCODE_8(i2);
                    break;
                case 9:
                    OPCODE_0(i1);
                    OPCODE_9(i2);
                    break;
                case 10:
                    OPCODE_0(i1);
                    OPCODE_10(i2);
                    break;
                case 11:
                    OPCODE_0(i1);
                    OPCODE_11(i2);
                    break;
                case 12:
                    OPCODE_0(i1);
                    OPCODE_12(i2);
                    break;
                case 13:
                    OPCODE_0(i1);
                    OPCODE_13(i2);
                    break;
                case 14:
                    OPCODE_0(i1);
                    OPCODE_14(i2);
                    break;
                case 15:
                    OPCODE_0(i1);
                    OPCODE_15(i2);
                    break;
                case 16:
                    OPCODE_1(i1);
                    OPCODE_0(i2);
                    break;
                case 17:
                    OPCODE_1(i1);
                    OPCODE_1(i2);
                    break;
                case 18:
                    OPCODE_1(i1);
                    OPCODE_2(i2);
                    break;
                case 19:
                    OPCODE_1(i1);
                    OPCODE_3(i2);
                    break;
                case 20:
                    OPCODE_1(i1);
                    OPCODE_4(i2);
                    break;
                case 21:
                    OPCODE_1(i1);
                    OPCODE_5(i2);
                    break;
                case 22:
                    OPCODE_1(i1);
                    OPCODE_6(i2);
                    break;
                case 23:
                    OPCODE_1(i1);
                    OPCODE_7(i2);
                    break;
                case 24:
                    OPCODE_1(i1);
                    OPCODE_8(i2);
                    break;
                case 25:
                    OPCODE_1(i1);
                    OPCODE_9(i2);
                    break;
                case 26:
                    OPCODE_1(i1);
                    OPCODE_10(i2);
                    break;
                case 27:
                    OPCODE_1(i1);
                    OPCODE_11(i2);
                    break;
                case 28:
                    OPCODE_1(i1);
                    OPCODE_12(i2);
                    break;
                case 29:
                    OPCODE_1(i1);
                    OPCODE_13(i2);
                    break;
                case 30:
                    OPCODE_1(i1);
                    OPCODE_14(i2);
                    break;
                case 31:
                    OPCODE_1(i1);
                    OPCODE_15(i2);
                    break;
                case 32:
                    OPCODE_2(i1);
                    OPCODE_0(i2);
                    break;
                case 33:
                    OPCODE_2(i1);
                    OPCODE_1(i2);
                    break;
                case 34:
                    OPCODE_2(i1);
                    OPCODE_2(i2);
                    break;
                case 35:
                    OPCODE_2(i1);
                    OPCODE_3(i2);
                    break;
                case 36:
                    OPCODE_2(i1);
                    OPCODE_4(i2);
                    break;
                case 37:
                    OPCODE_2(i1);
                    OPCODE_5(i2);
                    break;
                case 38:
                    OPCODE_2(i1);
                    OPCODE_6(i2);
                    break;
                case 39:
                    OPCODE_2(i1);
                    OPCODE_7(i2);
                    break;
                case 40:
                    OPCODE_2(i1);
                    OPCODE_8(i2);
                    break;
                case 41:
                    OPCODE_2(i1);
                    OPCODE_9(i2);
                    break;
                case 42:
                    OPCODE_2(i1);
                    OPCODE_10(i2);
                    break;
                case 43:
                    OPCODE_2(i1);
                    OPCODE_11(i2);
                    break;
                case 44:
                    OPCODE_2(i1);
                    OPCODE_12(i2);
                    break;
                case 45:
                    OPCODE_2(i1);
                    OPCODE_13(i2);
                    break;
                case 46:
                    OPCODE_2(i1);
                    OPCODE_14(i2);
                    break;
                case 47:
                    OPCODE_2(i1);
                    OPCODE_15(i2);
                    break;
                case 48:
                    OPCODE_3(i1);
                    OPCODE_0(i2);
                    break;
                case 49:
                    OPCODE_3(i1);
                    OPCODE_1(i2);
                    break;
                case 50:
                    OPCODE_3(i1);
                    OPCODE_2(i2);
                    break;
                case 51:
                    OPCODE_3(i1);
                    OPCODE_3(i2);
                    break;
                case 52:
                    OPCODE_3(i1);
                    OPCODE_4(i2);
                    break;
                case 53:
                    OPCODE_3(i1);
                    OPCODE_5(i2);
                    break;
                case 54:
                    OPCODE_3(i1);
                    OPCODE_6(i2);
                    break;
                case 55:
                    OPCODE_3(i1);
                    OPCODE_7(i2);
                    break;
                case 56:
                    OPCODE_3(i1);
                    OPCODE_8(i2);
                    break;
                case 57:
                    OPCODE_3(i1);
                    OPCODE_9(i2);
                    break;
                case 58:
                    OPCODE_3(i1);
                    OPCODE_10(i2);
                    break;
                case 59:
                    OPCODE_3(i1);
                    OPCODE_11(i2);
                    break;
                case 60:
                    OPCODE_3(i1);
                    OPCODE_12(i2);
                    break;
                case 61:
                    OPCODE_3(i1);
                    OPCODE_13(i2);
                    break;
                case 62:
                    OPCODE_3(i1);
                    OPCODE_14(i2);
                    break;
                case 63:
                    OPCODE_3(i1);
                    OPCODE_15(i2);
                    break;
                case 64:
                    OPCODE_4(i1);
                    OPCODE_0(i2);
                    break;
                case 65:
                    OPCODE_4(i1);
                    OPCODE_1(i2);
                    break;
                case 66:
                    OPCODE_4(i1);
                    OPCODE_2(i2);
                    break;
                case 67:
                    OPCODE_4(i1);
                    OPCODE_3(i2);
                    break;
                case 68:
                    OPCODE_4(i1);
                    OPCODE_4(i2);
                    break;
                case 69:
                    OPCODE_4(i1);
                    OPCODE_5(i2);
                    break;
                case 70:
                    OPCODE_4(i1);
                    OPCODE_6(i2);
                    break;
                case 71:
                    OPCODE_4(i1);
                    OPCODE_7(i2);
                    break;
                case 72:
                    OPCODE_4(i1);
                    OPCODE_8(i2);
                    break;
                case 73:
                    OPCODE_4(i1);
                    OPCODE_9(i2);
                    break;
                case 74:
                    OPCODE_4(i1);
                    OPCODE_10(i2);
                    break;
                case 75:
                    OPCODE_4(i1);
                    OPCODE_11(i2);
                    break;
                case 76:
                    OPCODE_4(i1);
                    OPCODE_12(i2);
                    break;
                case 77:
                    OPCODE_4(i1);
                    OPCODE_13(i2);
                    break;
                case 78:
                    OPCODE_4(i1);
                    OPCODE_14(i2);
                    break;
                case 79:
                    OPCODE_4(i1);
                    OPCODE_15(i2);
                    break;
                case 80:
                    OPCODE_5(i1);
                    OPCODE_0(i2);
                    break;
                case 81:
                    OPCODE_5(i1);
                    OPCODE_1(i2);
                    break;
                case 82:
                    OPCODE_5(i1);
                    OPCODE_2(i2);
                    break;
                case 83:
                    OPCODE_5(i1);
                    OPCODE_3(i2);
                    break;
                case 84:
                    OPCODE_5(i1);
                    OPCODE_4(i2);
                    break;
                case 85:
                    OPCODE_5(i1);
                    OPCODE_5(i2);
                    break;
                case 86:
                    OPCODE_5(i1);
                    OPCODE_6(i2);
                    break;
                case 87:
                    OPCODE_5(i1);
                    OPCODE_7(i2);
                    break;
                case 88:
                    OPCODE_5(i1);
                    OPCODE_8(i2);
                    break;
                case 89:
                    OPCODE_5(i1);
                    OPCODE_9(i2);
                    break;
                case 90:
                    OPCODE_5(i1);
                    OPCODE_10(i2);
                    break;
                case 91:
                    OPCODE_5(i1);
                    OPCODE_11(i2);
                    break;
                case 92:
                    OPCODE_5(i1);
                    OPCODE_12(i2);
                    break;
                case 93:
                    OPCODE_5(i1);
                    OPCODE_13(i2);
                    break;
                case 94:
                    OPCODE_5(i1);
                    OPCODE_14(i2);
                    break;
                case 95:
                    OPCODE_5(i1);
                    OPCODE_15(i2);
                    break;
                case 96:
                    OPCODE_6(i1);
                    OPCODE_0(i2);
                    break;
                case 97:
                    OPCODE_6(i1);
                    OPCODE_1(i2);
                    break;
                case 98:
                    OPCODE_6(i1);
                    OPCODE_2(i2);
                    break;
                case 99:
                    OPCODE_6(i1);
                    OPCODE_3(i2);
                    break;
                case 100:
                    OPCODE_6(i1);
                    OPCODE_4(i2);
                    break;
                case 101:
                    OPCODE_6(i1);
                    OPCODE_5(i2);
                    break;
                case 102:
                    OPCODE_6(i1);
                    OPCODE_6(i2);
                    break;
                case 103:
                    OPCODE_6(i1);
                    OPCODE_7(i2);
                    break;
                case 104:
                    OPCODE_6(i1);
                    OPCODE_8(i2);
                    break;
                case 105:
                    OPCODE_6(i1);
                    OPCODE_9(i2);
                    break;
                case 106:
                    OPCODE_6(i1);
                    OPCODE_10(i2);
                    break;
                case 107:
                    OPCODE_6(i1);
                    OPCODE_11(i2);
                    break;
                case 108:
                    OPCODE_6(i1);
                    OPCODE_12(i2);
                    break;
                case 109:
                    OPCODE_6(i1);
                    OPCODE_13(i2);
                    break;
                case 110:
                    OPCODE_6(i1);
                    OPCODE_14(i2);
                    break;
                case 111:
                    OPCODE_6(i1);
                    OPCODE_15(i2);
                    break;
                case 112:
                    OPCODE_7(i1);
                    OPCODE_0(i2);
                    break;
                case 113:
                    OPCODE_7(i1);
                    OPCODE_1(i2);
                    break;
                case 114:
                    OPCODE_7(i1);
                    OPCODE_2(i2);
                    break;
                case 115:
                    OPCODE_7(i1);
                    OPCODE_3(i2);
                    break;
                case 116:
                    OPCODE_7(i1);
                    OPCODE_4(i2);
                    break;
                case 117:
                    OPCODE_7(i1);
                    OPCODE_5(i2);
                    break;
                case 118:
                    OPCODE_7(i1);
                    OPCODE_6(i2);
                    break;
                case 119:
                    OPCODE_7(i1);
                    OPCODE_7(i2);
                    break;
                case 120:
                    OPCODE_7(i1);
                    OPCODE_8(i2);
                    break;
                case 121:
                    OPCODE_7(i1);
                    OPCODE_9(i2);
                    break;
                case 122:
                    OPCODE_7(i1);
                    OPCODE_10(i2);
                    break;
                case 123:
                    OPCODE_7(i1);
                    OPCODE_11(i2);
                    break;
                case 124:
                    OPCODE_7(i1);
                    OPCODE_12(i2);
                    break;
                case 125:
                    OPCODE_7(i1);
                    OPCODE_13(i2);
                    break;
                case 126:
                    OPCODE_7(i1);
                    OPCODE_14(i2);
                    break;
                case 127:
                    OPCODE_7(i1);
                    OPCODE_15(i2);
                    break;
                case 128:
                    OPCODE_8(i1);
                    OPCODE_0(i2);
                    break;
                case 129:
                    OPCODE_8(i1);
                    OPCODE_1(i2);
                    break;
                case 130:
                    OPCODE_8(i1);
                    OPCODE_2(i2);
                    break;
                case 131:
                    OPCODE_8(i1);
                    OPCODE_3(i2);
                    break;
                case 132:
                    OPCODE_8(i1);
                    OPCODE_4(i2);
                    break;
                case 133:
                    OPCODE_8(i1);
                    OPCODE_5(i2);
                    break;
                case 134:
                    OPCODE_8(i1);
                    OPCODE_6(i2);
                    break;
                case 135:
                    OPCODE_8(i1);
                    OPCODE_7(i2);
                    break;
                case 136:
                    OPCODE_8(i1);
                    OPCODE_8(i2);
                    break;
                case 137:
                    OPCODE_8(i1);
                    OPCODE_9(i2);
                    break;
                case 138:
                    OPCODE_8(i1);
                    OPCODE_10(i2);
                    break;
                case 139:
                    OPCODE_8(i1);
                    OPCODE_11(i2);
                    break;
                case 140:
                    OPCODE_8(i1);
                    OPCODE_12(i2);
                    break;
                case 141:
                    OPCODE_8(i1);
                    OPCODE_13(i2);
                    break;
                case 142:
                    OPCODE_8(i1);
                    OPCODE_14(i2);
                    break;
                case 143:
                    OPCODE_8(i1);
                    OPCODE_15(i2);
                    break;
                case 144:
                    OPCODE_9(i1);
                    OPCODE_0(i2);
                    break;
                case 145:
                    OPCODE_9(i1);
                    OPCODE_1(i2);
                    break;
                case 146:
                    OPCODE_9(i1);
                    OPCODE_2(i2);
                    break;
                case 147:
                    OPCODE_9(i1);
                    OPCODE_3(i2);
                    break;
                case 148:
                    OPCODE_9(i1);
                    OPCODE_4(i2);
                    break;
                case 149:
                    OPCODE_9(i1);
                    OPCODE_5(i2);
                    break;
                case 150:
                    OPCODE_9(i1);
                    OPCODE_6(i2);
                    break;
                case 151:
                    OPCODE_9(i1);
                    OPCODE_7(i2);
                    break;
                case 152:
                    OPCODE_9(i1);
                    OPCODE_8(i2);
                    break;
                case 153:
                    OPCODE_9(i1);
                    OPCODE_9(i2);
                    break;
                case 154:
                    OPCODE_9(i1);
                    OPCODE_10(i2);
                    break;
                case 155:
                    OPCODE_9(i1);
                    OPCODE_11(i2);
                    break;
                case 156:
                    OPCODE_9(i1);
                    OPCODE_12(i2);
                    break;
                case 157:
                    OPCODE_9(i1);
                    OPCODE_13(i2);
                    break;
                case 158:
                    OPCODE_9(i1);
                    OPCODE_14(i2);
                    break;
                case 159:
                    OPCODE_9(i1);
                    OPCODE_15(i2);
                    break;
                case 160:
                    OPCODE_10(i1);
                    OPCODE_0(i2);
                    break;
                case 161:
                    OPCODE_10(i1);
                    OPCODE_1(i2);
                    break;
                case 162:
                    OPCODE_10(i1);
                    OPCODE_2(i2);
                    break;
                case 163:
                    OPCODE_10(i1);
                    OPCODE_3(i2);
                    break;
                case 164:
                    OPCODE_10(i1);
                    OPCODE_4(i2);
                    break;
                case 165:
                    OPCODE_10(i1);
                    OPCODE_5(i2);
                    break;
                case 166:
                    OPCODE_10(i1);
                    OPCODE_6(i2);
                    break;
                case 167:
                    OPCODE_10(i1);
                    OPCODE_7(i2);
                    break;
                case 168:
                    OPCODE_10(i1);
                    OPCODE_8(i2);
                    break;
                case 169:
                    OPCODE_10(i1);
                    OPCODE_9(i2);
                    break;
                case 170:
                    OPCODE_10(i1);
                    OPCODE_10(i2);
                    break;
                case 171:
                    OPCODE_10(i1);
                    OPCODE_11(i2);
                    break;
                case 172:
                    OPCODE_10(i1);
                    OPCODE_12(i2);
                    break;
                case 173:
                    OPCODE_10(i1);
                    OPCODE_13(i2);
                    break;
                case 174:
                    OPCODE_10(i1);
                    OPCODE_14(i2);
                    break;
                case 175:
                    OPCODE_10(i1);
                    OPCODE_15(i2);
                    break;
                case 176:
                    OPCODE_11(i1);
                    OPCODE_0(i2);
                    break;
                case 177:
                    OPCODE_11(i1);
                    OPCODE_1(i2);
                    break;
                case 178:
                    OPCODE_11(i1);
                    OPCODE_2(i2);
                    break;
                case 179:
                    OPCODE_11(i1);
                    OPCODE_3(i2);
                    break;
                case 180:
                    OPCODE_11(i1);
                    OPCODE_4(i2);
                    break;
                case 181:
                    OPCODE_11(i1);
                    OPCODE_5(i2);
                    break;
                case 182:
                    OPCODE_11(i1);
                    OPCODE_6(i2);
                    break;
                case 183:
                    OPCODE_11(i1);
                    OPCODE_7(i2);
                    break;
                case 184:
                    OPCODE_11(i1);
                    OPCODE_8(i2);
                    break;
                case 185:
                    OPCODE_11(i1);
                    OPCODE_9(i2);
                    break;
                case 186:
                    OPCODE_11(i1);
                    OPCODE_10(i2);
                    break;
                case 187:
                    OPCODE_11(i1);
                    OPCODE_11(i2);
                    break;
                case 188:
                    OPCODE_11(i1);
                    OPCODE_12(i2);
                    break;
                case 189:
                    OPCODE_11(i1);
                    OPCODE_13(i2);
                    break;
                case 190:
                    OPCODE_11(i1);
                    OPCODE_14(i2);
                    break;
                case 191:
                    OPCODE_11(i1);
                    OPCODE_15(i2);
                    break;
                case 192:
                    OPCODE_12(i1);
                    OPCODE_0(i2);
                    break;
                case 193:
                    OPCODE_12(i1);
                    OPCODE_1(i2);
                    break;
                case 194:
                    OPCODE_12(i1);
                    OPCODE_2(i2);
                    break;
                case 195:
                    OPCODE_12(i1);
                    OPCODE_3(i2);
                    break;
                case 196:
                    OPCODE_12(i1);
                    OPCODE_4(i2);
                    break;
                case 197:
                    OPCODE_12(i1);
                    OPCODE_5(i2);
                    break;
                case 198:
                    OPCODE_12(i1);
                    OPCODE_6(i2);
                    break;
                case 199:
                    OPCODE_12(i1);
                    OPCODE_7(i2);
                    break;
                case 200:
                    OPCODE_12(i1);
                    OPCODE_8(i2);
                    break;
                case 201:
                    OPCODE_12(i1);
                    OPCODE_9(i2);
                    break;
                case 202:
                    OPCODE_12(i1);
                    OPCODE_10(i2);
                    break;
                case 203:
                    OPCODE_12(i1);
                    OPCODE_11(i2);
                    break;
                case 204:
                    OPCODE_12(i1);
                    OPCODE_12(i2);
                    break;
                case 205:
                    OPCODE_12(i1);
                    OPCODE_13(i2);
                    break;
                case 206:
                    OPCODE_12(i1);
                    OPCODE_14(i2);
                    break;
                case 207:
                    OPCODE_12(i1);
                    OPCODE_15(i2);
                    break;
                case 208:
                    OPCODE_13(i1);
                    OPCODE_0(i2);
                    break;
                case 209:
                    OPCODE_13(i1);
                    OPCODE_1(i2);
                    break;
                case 210:
                    OPCODE_13(i1);
                    OPCODE_2(i2);
                    break;
                case 211:
                    OPCODE_13(i1);
                    OPCODE_3(i2);
                    break;
                case 212:
                    OPCODE_13(i1);
                    OPCODE_4(i2);
                    break;
                case 213:
                    OPCODE_13(i1);
                    OPCODE_5(i2);
                    break;
                case 214:
                    OPCODE_13(i1);
                    OPCODE_6(i2);
                    break;
                case 215:
                    OPCODE_13(i1);
                    OPCODE_7(i2);
                    break;
                case 216:
                    OPCODE_13(i1);
                    OPCODE_8(i2);
                    break;
                case 217:
                    OPCODE_13(i1);
                    OPCODE_9(i2);
                    break;
                case 218:
                    OPCODE_13(i1);
                    OPCODE_10(i2);
                    break;
                case 219:
                    OPCODE_13(i1);
                    OPCODE_11(i2);
                    break;
                case 220:
                    OPCODE_13(i1);
                    OPCODE_12(i2);
                    break;
                case 221:
                    OPCODE_13(i1);
                    OPCODE_13(i2);
                    break;
                case 222:
                    OPCODE_13(i1);
                    OPCODE_14(i2);
                    break;
                case 223:
                    OPCODE_13(i1);
                    OPCODE_15(i2);
                    break;
                case 224:
                    OPCODE_14(i1);
                    OPCODE_0(i2);
                    break;
                case 225:
                    OPCODE_14(i1);
                    OPCODE_1(i2);
                    break;
                case 226:
                    OPCODE_14(i1);
                    OPCODE_2(i2);
                    break;
                case 227:
                    OPCODE_14(i1);
                    OPCODE_3(i2);
                    break;
                case 228:
                    OPCODE_14(i1);
                    OPCODE_4(i2);
                    break;
                case 229:
                    OPCODE_14(i1);
                    OPCODE_5(i2);
                    break;
                case 230:
                    OPCODE_14(i1);
                    OPCODE_6(i2);
                    break;
                case 231:
                    OPCODE_14(i1);
                    OPCODE_7(i2);
                    break;
                case 232:
                    OPCODE_14(i1);
                    OPCODE_8(i2);
                    break;
                case 233:
                    OPCODE_14(i1);
                    OPCODE_9(i2);
                    break;
                case 234:
                    OPCODE_14(i1);
                    OPCODE_10(i2);
                    break;
                case 235:
                    OPCODE_14(i1);
                    OPCODE_11(i2);
                    break;
                case 236:
                    OPCODE_14(i1);
                    OPCODE_12(i2);
                    break;
                case 237:
                    OPCODE_14(i1);
                    OPCODE_13(i2);
                    break;
                case 238:
                    OPCODE_14(i1);
                    OPCODE_14(i2);
                    break;
                case 239:
                    OPCODE_14(i1);
                    OPCODE_15(i2);
                    break;
                case 240:
                    OPCODE_15(i1);
                    OPCODE_0(i2);
                    break;
                case 241:
                    OPCODE_15(i1);
                    OPCODE_1(i2);
                    break;
                case 242:
                    OPCODE_15(i1);
                    OPCODE_2(i2);
                    break;
                case 243:
                    OPCODE_15(i1);
                    OPCODE_3(i2);
                    break;
                case 244:
                    OPCODE_15(i1);
                    OPCODE_4(i2);
                    break;
                case 245:
                    OPCODE_15(i1);
                    OPCODE_5(i2);
                    break;
                case 246:
                    OPCODE_15(i1);
                    OPCODE_6(i2);
                    break;
                case 247:
                    OPCODE_15(i1);
                    OPCODE_7(i2);
                    break;
                case 248:
                    OPCODE_15(i1);
                    OPCODE_8(i2);
                    break;
                case 249:
                    OPCODE_15(i1);
                    OPCODE_9(i2);
                    break;
                case 250:
                    OPCODE_15(i1);
                    OPCODE_10(i2);
                    break;
                case 251:
                    OPCODE_15(i1);
                    OPCODE_11(i2);
                    break;
                case 252:
                    OPCODE_15(i1);
                    OPCODE_12(i2);
                    break;
                case 253:
                    OPCODE_15(i1);
                    OPCODE_13(i2);
                    break;
                case 254:
                    OPCODE_15(i1);
                    OPCODE_14(i2);
                    break;
                case 255:
                    OPCODE_15(i1);
                    OPCODE_15(i2);
                    break;
            }
        }
    }
};
} // namespace compiler
