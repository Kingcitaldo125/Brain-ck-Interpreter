#include <iostream>

#include "parser.hpp"
#include "utility.hpp"

using namespace BrainFck;

Parser::Parser()
{
    xpointer = 0;
    elements.fill(0);
    lexemes = std::unordered_set<char>{'<', '>', '[', ']', '.', '+', '-', ','};
    tokenizer = Tokenizer();
    tokenizer.unset_tokenize_verbose();
#ifdef DEBUG
    tokenizer.set_tokenize_verbose();
#endif // DEBUG
}

int Parser::handle_instruction(BrainFck::tok_arr_t &contents, BrainFck::TOKENS instruction)
{
    switch (instruction)
    {
    case BrainFck::TOKENS::SHL:
    {
        if (xpointer - 1 < 0)
            break;
        --xpointer;
        break;
    }
    case BrainFck::TOKENS::SHR:
    {
        if (xpointer + 1 >= ARRAY_LENGTH)
            break;
        ++xpointer;
        break;
    }
    case BrainFck::TOKENS::OBRACK:
    {
        if (token_pointer + 1 >= contents.end())
            break; // Open bracket is final element in the input (discard)

        brack_stack.push_back(std::make_pair(xpointer, token_pointer + 1));
#ifdef DEBUG
        std::cout << "Pushed bracket context to stack";
        std::cout << "(xpointer = " << xpointer << " token_pointer = ";
        std::cout << stringify_token(*(token_pointer + 1));
        std::cout << ")\n";
#endif // DEBUG

        break;
    }
    case BrainFck::TOKENS::CBRACK:
    {
        if (!brack_stack.empty())
        {
            auto &top = brack_stack.back();
            const auto &[tpointer, ttoken] = top;

            if (!elements.at(tpointer) || !elements.at(xpointer))
            {
                // we've hit the end condition for the loop
#ifdef DEBUG
                std::cout << "hit end condition for loop starting at xpointer: " << xpointer
                          << "\n";
#endif // DEBUG
                brack_stack.pop_back();
                break;
            }

            // go back to the start of the loop
#ifdef DEBUG
            std::cout << "looping back to: " << stringify_token(*ttoken) << "\n";
#endif // DEBUG

            token_pointer = ttoken - 1;
        } // else, we may have a parse error here.
        break;
    }
    case BrainFck::TOKENS::INC:
    {
        ++elements.at(xpointer);

        if (elements.at(xpointer) > BYTE_END)
            elements.at(xpointer) = 0;
        break;
    }
    case BrainFck::TOKENS::DEC:
    {
        --elements.at(xpointer);
        if (elements.at(xpointer) < 0)
            elements.at(xpointer) = BYTE_END;
        break;
    }
    case BrainFck::TOKENS::OUTP:
    {
        const auto &el = static_cast<char>(elements.at(xpointer));
        xoutput << el;
        break;
    }
    case BrainFck::TOKENS::INP:
    {
        char xbyte;
        std::cin >> xbyte;
        elements.at(xpointer) = static_cast<int>(xbyte);
        break;
    }
    default:
        break;
    }

    return 0;
}

int Parser::parse(const std::string &mstr)
{
    if (mstr.empty())
        return 0;

#ifdef DEBUG
    std::cout << "Input: " << mstr << "\n";
#endif // DEBUG

    BrainFck::tok_arr_t tokens = tokenizer.tokenize(mstr);
    token_pointer = tokens.begin();
    int res = 0;

    for (; token_pointer < tokens.end(); ++token_pointer)
    {
#ifdef DEBUG
        std::cout << "next token: ";
        std::cout << stringify_token(*token_pointer);
        std::cout << "\n";
#endif // DEBUG

        res |= handle_instruction(tokens, *token_pointer);
    }

    return res;
}

std::string Parser::output()
{
    return xoutput.str();
}

void Parser::reset_output()
{
    xoutput.str("");
    xoutput.clear();
}

int64_t Parser::get_data_location() const
{
    return xpointer;
}
