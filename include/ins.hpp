#pragma once

namespace compiler {
using uint = unsigned int;

struct ins {
    uint code = 0;

    uint get_OP() {
        return 0;
    }
    uint get_A() {
        return 0;
    }
    uint get_C() {
        return 0;
    }
};
}
