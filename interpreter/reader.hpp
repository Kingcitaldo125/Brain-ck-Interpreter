#pragma once

#include <string>

namespace BrainFck
{
class Reader
{
  public:
    Reader() = default;

    std::string read(const std::string &filepath);
};
} // namespace BrainFck
