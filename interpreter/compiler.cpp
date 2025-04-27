#include <cstdlib>

#include "compiler.hpp"
#include "reader.hpp"

// 30'000 byte array
#define ARRAY_LENGTH 0x7530
#define BYTE_END 0xFF

using BrainFck::Reader;
using BrainFck::Compiler;

Compiler::Compiler()
{
    reset();
}

void Compiler::reset()
{
    // reset vars tracking outputs and C compiler invocations
    writer = std::ofstream("out.c", std::ios::out);
    token_arr_name = std::string("TOK_ARR");
    // might need to make the choice of compiler variable
    // go with 'gcc' for now
    compiler_invocation = std::string("gcc -o out out.c");

    // reset loop bookeeping vars
    loop_contents.clear();
    in_loop = false;
}

void Compiler::add_tokens(const std::vector<BrainFck::TOKENS>& tokens)
{
    for(const auto& tok : tokens)
    {
        switch (tok)
        {
            case BrainFck::TOKENS::OBRACK:
            {
                write_loop_start();
                in_loop = true;
                break;
            }
            case BrainFck::TOKENS::CBRACK:
            {
                write_loop_end();
                loop_contents.clear();
                in_loop = false;
                break;
            }
            case BrainFck::TOKENS::INC:
            {
                write_inc();
                break;
            }
            case BrainFck::TOKENS::DEC:
            {
                write_dec();
                break;
            }
            default:
                break;
        }
    }
}

int Compiler::compile()
{
    writer.flush();
    const int retc = system(compiler_invocation.c_str());
    reset();
    return retc;
}

void Compiler::initialize()
{
    writer << "#include <stdio.h>\n";
    writer << "#include <stdlib.h>\n";
    writer << "\n";
}

void Compiler::write_main_start()
{
    const int byte_arr_len = ARRAY_LENGTH;

    writer << "int main()\n{\n";

    // write out the C version of the array of bytes
    writer << "int marr[" << (std::to_string(byte_arr_len)) << "]" << token_arr_name << ";\n";
    writer << "int* marr_ptr = marr";
}

void Compiler::write_main_end()
{
    writer << "\n}\n";
}

void Compiler::write_loop_start()
{
    writer << "while(1)\n{";
    writer << "if marr";
}

void Compiler::write_loop_end()
{
    writer << "\n}\n";
}

void Compiler::write_inc()
{
    writer << "marr_ptr++;\n";
}

void Compiler::write_dec()
{
    writer << "marr_ptr--;\n";
}

int main()
{
    return 0;
}
