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

    void add_tokens(const std::vector<BrainFck::TOKENS>& tokens);
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

private:
    std::ofstream writer;
    std::list<BrainFck::TOKENS> loop_contents;
    bool in_loop;
    std::string token_arr_name;
    std::string compiler_invocation;
};
}
