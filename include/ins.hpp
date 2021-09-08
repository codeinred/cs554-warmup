#pragma once
#include <cstdint>

namespace compiler {
using uint = uint32_t;

template <int start, int end>
constexpr uint get_section_of_bits(uint input) {
    uint num_to_get = end - start + 1;
    uint mask = (1 << num_to_get) - 1;
    return (input >> start) & mask;
}
struct ins {
    uint code = 0;

    constexpr uint get_OP() const {
        return get_section_of_bits<28, 31>(code);
    }
    constexpr uint get_A() const {
        return get_section_of_bits<6, 8>(code);
    }
    constexpr uint get_B() const {
        return get_section_of_bits<3, 5>(code);
    }
    constexpr uint get_C() const {
        return get_section_of_bits<0, 2>(code);
    }
};


static_assert(ins{ 0xf0000000u}.get_OP() == 0xf, "get_OP() not working");
}
