#include <iostream>

#include "interpreter.hpp"
#include "parser.hpp"

using BrainFck::Interpreter;
using BrainFck::Parser;

Interpreter::Interpreter()
{
    parser = std::make_unique<Parser>();
    parser->set_tokenize_verbose();
    int_prefix = "BF>";
}

int Interpreter::interpret()
{
    int res = 0;

    while (1)
    {
        std::string holder;
        const std::string data_location = std::to_string(parser->get_data_location());
        const std::string int_val = int_prefix + "(" + data_location + ") ";

        std::cout << int_val;
        std::cin >> holder;
#ifdef DEBUG
        std::cout << "holder " << holder << "\n";
#endif // DEBUG
       // break;

        if (holder.empty())
            break;

        bool is_ascii = true;
        for (const auto &itm : holder)
        {
            if (!isascii(itm))
            {
                is_ascii = false;
                break;
            }
        }

        if (!is_ascii)
            continue;

        res |= parser->parse(holder);

        if (res != 0)
            break;
        if (holder == ".")
        {
            std::cout << parser->output() << std::endl;
        }

        parser->reset_output();
    }

    return res;
}
