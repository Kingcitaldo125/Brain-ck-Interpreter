#pragma once

#include <array>
#include <list>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>

#include "token.hpp"

// 30'000 byte array
#define ARRAY_LENGTH 0x7530
#define BYTE_END 0xFF

namespace BrainFck
{
class Parser final
{
  public:
    Parser();
    Parser(const Parser &) = delete;
    Parser(Parser &&) = delete;
    Parser &operator=(const Parser &) = delete;
    Parser &operator=(Parser &&) = delete;

    int parse(const std::string &mstr);
    std::string output();

  protected:
    tok_arr_t tokenize(const std::string &mstr);
    int handle_instruction(BrainFck::tok_arr_t &contents, BrainFck::TOKENS instruction);

  private:
    int64_t xpointer;
    tok_iter_t token_pointer;
    std::list<std::pair<int64_t, tok_iter_t>> brack_stack;
    std::array<int, ARRAY_LENGTH> elements;
    std::unordered_set<char> lexemes;
    std::stringstream xoutput;
};
} // namespace BrainFck
