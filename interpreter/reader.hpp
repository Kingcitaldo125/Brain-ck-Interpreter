#pragma once

#include <memory>
#include <string>

#include "parser.hpp"

namespace BrainFck
{
class Reader
{
  public:
    Reader();

    int read(const std::string &filepath);

  private:
    std::unique_ptr<Parser> parser;
};
} // namespace BrainFck
