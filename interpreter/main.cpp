#include <iostream>

#include "interpreter.hpp"
#include "reader.hpp"

using BrainFck::Interpreter;
using BrainFck::Reader;

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        Interpreter interpreter;
        return interpreter.interpret();
    }

    Reader reader;
    return reader.read(argv[1]);
}
