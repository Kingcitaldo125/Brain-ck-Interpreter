#pragma once

#include "token.hpp"
#include <string>
#include <vector>

namespace BrainFck
{
std::string stringify_token(BrainFck::TOKENS token);
tok_iter_t find_next_close(tok_iter_t begin, tok_iter_t end);
std::vector<std::string> split_string(const std::string &mstr, const char delimiter);
} // namespace BrainFck
