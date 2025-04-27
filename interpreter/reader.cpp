#include <fstream>
#include <iostream>
#include <sstream>

#include "reader.hpp"
#include "utility.hpp"

using BrainFck::Reader;

std::string Reader::read(const std::string &filepath)
{
    if (filepath.empty())
        return ""; // the runner shell script should handle this case

    if (BrainFck::split_string(filepath, '.').back() != "bf")
    {
        // emit warning about the file suffix
        std::cout << "WARNING: File does not end in suffix '.bf': " << filepath << std::endl;
    }

    std::ifstream iff(filepath);
    std::stringstream stream;
    std::string holder = "";

    while (iff >> holder)
    {
        stream << holder;
        holder = "";
#ifdef DEBUG
        std::cout << "stream: " << stream.str() << std::endl;
#endif // DEBUG
    }

    return stream.str();
}
