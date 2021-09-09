#pragma once
#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <ins.hpp>

template <>
struct fmt::formatter<compiler::instruction> : fmt::formatter<uint32_t> {
    using base = fmt::formatter<uint32_t>;
    template <typename FormatContext>
    auto format(compiler::instruction i, FormatContext& ctx)
        -> decltype(ctx.out()) {

        fmt::format_to(ctx.out(), "[ op: ");

        base::format(i.get_OP(), ctx);
        if (i.get_OP() == 13) {
            int padding = 8;
            fmt::format_to(ctx.out(), ", A: ");
            base::format(i.get_special(), ctx);

            fmt::format_to(ctx.out(), ", v: ");
            base::format(i.get_special_value(), ctx);

            for(int i = 0; i < padding; i++)
                fmt::format_to(ctx.out(), " ");
        } else {
            fmt::format_to(ctx.out(), ", A: ");
            base::format(i.get_A(), ctx);

            fmt::format_to(ctx.out(), ", B: ");
            base::format(i.get_B(), ctx);

            fmt::format_to(ctx.out(), ", C: ");
            base::format(i.get_C(), ctx);
        }
        fmt::format_to(ctx.out(), " ]");
        return ctx.out();
    }
};
