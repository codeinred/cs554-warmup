#include <fmt/core.h>

int main() {
    constexpr int base = 16;
    for (int i = 0; i < base; i++) {
        for (int j = 0; j < base; j++) {
            fmt::print(
                "case {}: OPCODE_{}(i1); OPCODE_{}(i2); break;\n",
                i * base + j,
                i,
                j);
        }
    }
}
