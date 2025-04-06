#pragma once

#include <memory>
#include <string>

#include "parser.hpp"

namespace BrainFck
{
class Interpreter
{
  public:
    Interpreter();

    int interpret();

  private:
    std::unique_ptr<Parser> parser;
    std::string int_prefix;
};
} // namespace BrainFck
