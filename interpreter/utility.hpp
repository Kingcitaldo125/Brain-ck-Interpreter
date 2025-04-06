#pragma once

#include <string>
#include "token.hpp"

namespace BrainFck
{
std::string stringify_token(BrainFck::TOKENS token);
tok_iter_t find_matching_close(tok_iter_t begin, tok_iter_t end);
tok_iter_t find_next_close(tok_iter_t begin, tok_iter_t end);
} // namespace BrainFck
