#include <iostream>

#include "interpreter.hpp"
#include "reader.hpp"
#include "parser.hpp"

using BrainFck::Interpreter;
using BrainFck::Parser;
using BrainFck::Reader;

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        Interpreter interpreter;
        return interpreter.interpret();
    }

    Reader reader;
    Parser parser;

    const int parse_res = parser.parse(reader.read(argv[1]));
    if (!parse_res)
    {
        std::cout << parser.output();// << std::endl;
    }
    parser.reset_output();

    return parse_res;
}
