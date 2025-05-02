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

    const int cli_param = std::stoi(std::string(argv[2]));

    int parse_res = 0;
    if (cli_param == 1)
    {
        parse_res = parser.parse(reader.read(argv[1]));
    }
    else if (cli_param == 2)
    {
        parse_res = parser.parse(argv[1]);
    }
    else
    {
        std::cout << "Cannot interpret CLI command option" << std::endl;
        return -1;
    }

    if (!parse_res)
    {
        std::cout << parser.output();
    }
    parser.reset_output();

    return parse_res;
}
