#pragma once

#include <string>
#include <unordered_set>

#include "token.hpp"

namespace BrainFck
{
class Tokenizer final
{
  public:
    Tokenizer();

    void set_tokenize_verbose();
    void unset_tokenize_verbose();
    tok_arr_t tokenize(const std::string &mstr);

  private:
    bool tokenize_verbose;
    std::unordered_set<char> lexemes;
};
} // namespace BrainFck
