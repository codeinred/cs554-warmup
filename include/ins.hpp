#pragma once
#include <cstdint>

namespace compiler {
using uint = uint32_t;

template <int start, int end>
constexpr uint get_section_of_bits(uint input) {
    static_assert(
        0 <= start && start <= 31, "start should be between 0 and 31");
    static_assert(0 <= end && end <= 31, "end should be between 0 and 31");
    static_assert(start < end, "start should be smaller than end");

    constexpr uint num_to_get = end - start + 1;
    constexpr uint mask = (1 << num_to_get) - 1;
    return (input >> start) & mask;
}
struct instruction {
    uint code = 0;

    constexpr uint get_OP() const { return get_section_of_bits<28, 31>(code); }
    constexpr uint get_A() const { return get_section_of_bits<6, 8>(code); }
    constexpr uint get_B() const { return get_section_of_bits<3, 5>(code); }
    constexpr uint get_C() const { return get_section_of_bits<0, 2>(code); }
    constexpr uint get_special() const {
        return get_section_of_bits<25, 27>(code);
    }
    constexpr uint get_special_value() const {
        return get_section_of_bits<0, 24>(code);
    }
};


static_assert(
    instruction {0xf0000000u}.get_OP() == 0xf, "get_OP() not working");
} // namespace compiler
