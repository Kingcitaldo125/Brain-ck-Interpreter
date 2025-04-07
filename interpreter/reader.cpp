#include <fstream>
#include <iostream>
#include <sstream>

#include "reader.hpp"
#include "utility.hpp"

using BrainFck::Parser;
using BrainFck::Reader;

Reader::Reader()
{
    parser = std::make_unique<Parser>();
}

int Reader::read(const std::string &filepath)
{
    if (filepath.empty())
        return 1; // the runner shell script should handle this case

    if (BrainFck::split_string(filepath, '.').back() != "bf")
    {
        // emit warning about the file suffix
        std::cout << "WARNING: File does not end in suffix '.bf': " << filepath << std::endl;
    }

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
