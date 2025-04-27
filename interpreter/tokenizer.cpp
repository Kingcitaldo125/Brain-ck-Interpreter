#include <iostream>

#include "tokenizer.hpp"

using BrainFck::Tokenizer;

Tokenizer::Tokenizer()
{
    lexemes = std::unordered_set<char>{'<', '>', '[', ']', '.', '+', '-', ','};
}

void Tokenizer::set_tokenize_verbose()
{
    tokenize_verbose = true;
}

void Tokenizer::unset_tokenize_verbose()
{
    tokenize_verbose = false;
}

BrainFck::tok_arr_t Tokenizer::tokenize(const std::string &mstr)
{
    BrainFck::tok_arr_t tokens;

    for (const auto &chr : mstr)
    {
        // If we found a token that's not in the language, discard
        if (lexemes.find(chr) == lexemes.end())
            continue;

        // Otherwise, tokenize the char
        if (chr == '+')
            tokens.push_back(BrainFck::TOKENS::INC);
        else if (chr == '-')
            tokens.push_back(BrainFck::TOKENS::DEC);
        else if (chr == '[')
            tokens.push_back(BrainFck::TOKENS::OBRACK);
        else if (chr == ']')
            tokens.push_back(BrainFck::TOKENS::CBRACK);
        else if (chr == '.')
            tokens.push_back(BrainFck::TOKENS::OUTP);
        else if (chr == '<')
            tokens.push_back(BrainFck::TOKENS::SHL);
        else if (chr == '>')
            tokens.push_back(BrainFck::TOKENS::SHR);
        else if (chr == ',')
            tokens.push_back(BrainFck::TOKENS::INP);
        else
        {
            if (tokenize_verbose)
                std::cout << "Not a valid token: '" << chr << "' -- skipping...";
        }
    }

    return tokens;
}
