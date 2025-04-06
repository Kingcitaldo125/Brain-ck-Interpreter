#include <fstream>
#include <iostream>
#include <sstream>

#include "reader.hpp"

using BrainFck::Parser;
using BrainFck::Reader;

Reader::Reader()
{
    parser = std::make_unique<Parser>();
}

int Reader::read(const std::string &filepath)
{
    std::ifstream iff(filepath);
    std::stringstream stream;
    std::string holder;

    while (iff >> holder)
    {
        stream << holder;
        holder = "";
#ifdef DEBUG
        std::cout << "stream: " << stream << std::endl;
#endif // DEBUG
    }

    const int parse_res = parser->parse(stream.str());
    if (!parse_res)
    {
        std::cout << parser->output() << std::endl;
    }
    parser->reset_output();

    return parse_res;
}
