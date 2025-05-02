#pragma once

#include <fstream>
#include <list>
#include <vector>

#include "token.hpp"

namespace BrainFck
{
class Compiler final
{
  public:
    Compiler();

    void add_tokens(const std::vector<BrainFck::TOKENS> &tokens);
    void reset();
    int compile();

  protected:
    void initialize();

    void write_main_start();
    void write_main_end();
    void write_loop_start();
    void write_loop_end();
    void write_inc();
    void write_dec();
    void write_shl();
    void write_shr();
    void write_outp();
    void write_newline();
    std::string write_tab();

  private:
    std::ofstream writer;
    std::string token_arr_name;
    std::string compiler_invocation;
    int tab_tracker;
};
} // namespace BrainFck
