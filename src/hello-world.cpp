#include <fmt/core.h>
#include <ins.hpp>

int main() {
    using namespace compiler;

    fmt::print("test.get_OP(): {}\n", ins {0xf000'0000u}.get_OP());
    fmt::print("test.get_A(): {}\n", ins {0b111'000'000u}.get_A());
    fmt::print("test.get_B(): {}\n", ins {0b000'111'000u}.get_B());
    fmt::print("test.get_C(): {}\n", ins {0b000'000'111u}.get_C());
}
