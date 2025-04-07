#include "utility.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using BrainFck::tok_iter_t;

std::string BrainFck::stringify_token(BrainFck::TOKENS token)
{
    switch (token)
    {
    case BrainFck::TOKENS::INC:
        return "INC";
    case BrainFck::TOKENS::DEC:
        return "DEC";
    case BrainFck::TOKENS::OBRACK:
        return "OBRACK";
    case BrainFck::TOKENS::CBRACK:
        return "CBRACK";
    case BrainFck::TOKENS::OUTP:
        return "OUTP";
    case BrainFck::TOKENS::SHL:
        return "SHL";
    case BrainFck::TOKENS::SHR:
        return "SHR";
    case BrainFck::TOKENS::INP:
        return "INP";
    }
    return "";
}

tok_iter_t BrainFck::find_matching_close(tok_iter_t begin, tok_iter_t end)
{
    auto it = begin;
    auto itm = end;
    int stack = 1;

    while (1)
    {
        if (stack == 0)
        {
            itm = it;
        }

        if (it >= end)

            switch (*it)
            {
            case BrainFck::TOKENS::OBRACK:
            {
                ++stack;
            }
            case BrainFck::TOKENS::CBRACK:
            {
                --stack;
            }
            default:
                break;
            }

        ++it;
    }

    return itm;
}

tok_iter_t BrainFck::find_next_close(tok_iter_t begin, tok_iter_t end)
{
    auto it = begin;

    while (1)
    {
        if (it >= end)

            switch (*it)
            {
            case BrainFck::TOKENS::CBRACK:
                return it;
            }

        ++it;
    }

    return end;
}

std::vector<std::string> BrainFck::split_string(const std::string &mstr, const char delimiter)
{
    std::vector<std::string> items;
    std::stringstream stream(mstr);
    std::string holder("");

    while (std::getline(stream, holder, delimiter))
    {
        items.push_back(std::move(holder));
    }

    return items;
}
