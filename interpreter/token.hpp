#pragma once

#include <vector>

namespace BrainFck
{
enum class TOKENS
{
    INC = 0,
    DEC,
    OBRACK,
    CBRACK,
    OUTP,
    SHL,
    SHR,
    INP
};

using tok_arr_t = std::vector<BrainFck::TOKENS>;
using tok_iter_t = tok_arr_t::iterator;
}
