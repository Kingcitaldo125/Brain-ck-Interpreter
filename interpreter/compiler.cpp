#include <cstdlib>

#include <iostream>

#include "compiler.hpp"
#include "reader.hpp"
#include "tokenizer.hpp"

// 30'000 byte array
#define ARRAY_LENGTH 0x7530
#define TAB_LIMIT 10
// This appears to remove some necessary code -- remove optimization flags for now.
// #define COMPILER_FLAGS "-O2"
#define C_OUTFILE "out.c"

using BrainFck::Compiler;
using BrainFck::Reader;
using BrainFck::Tokenizer;

Compiler::Compiler()
{
    reset();
}

void Compiler::reset()
{
    // reset vars tracking outputs and C compiler invocations
    writer = std::ofstream(C_OUTFILE, std::ios::out);
    token_arr_name = std::string("TOK_ARR");

// might need to make the choice of compiler variable
// go with 'gcc' for now
#ifdef SHOW_ASM
    compiler_invocation = std::string("gcc -S " C_OUTFILE "; gcc -o out " C_OUTFILE);
#else
    // compiler_invocation = std::string("gcc -o out " COMPILER_FLAGS " " C_OUTFILE);
    compiler_invocation = std::string("gcc -o out " C_OUTFILE);
#endif

    // reset loop bookeeping vars
    tab_tracker = 0;

    initialize();
    write_main_start();
}

void Compiler::add_tokens(const std::vector<BrainFck::TOKENS> &tokens)
{
    for (const auto &tok : tokens)
    {
        switch (tok)
        {
        case BrainFck::TOKENS::OBRACK:
        {
            write_loop_start();
            break;
        }
        case BrainFck::TOKENS::CBRACK:
        {
            write_loop_end();
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
        case BrainFck::TOKENS::SHL:
        {
            write_shl();
            break;
        }
        case BrainFck::TOKENS::SHR:
        {
            write_shr();
            break;
        }
        case BrainFck::TOKENS::INP:
        {
            // skip for now
            break;
        }
        case BrainFck::TOKENS::OUTP:
        {
            write_outp();
            break;
        }
        default:
            break;
        }
    }
}

int Compiler::compile()
{
    write_main_end();
    writer.flush();
    const int retc = system(compiler_invocation.c_str());
    if (!retc)
    {
        std::cout << "Wrote to '" << C_OUTFILE << "'\n";
#ifdef SHOW_ASM
        const auto coutfile_str = std::string(C_OUTFILE);
        auto dot = coutfile_str.find('.');
        std::cout << "Wrote to '" << (coutfile_str.substr(0, dot) + ".s") << "'\n";
#endif
    }
    return retc;
}

void Compiler::initialize()
{
    writer << "#include <stdio.h>\n";
    writer << "#include <stdlib.h>\n";
    writer << "\n";
}

void Compiler::write_newline()
{
    writer << "\n";
}

std::string Compiler::write_tab()
{
    if (tab_tracker < 0 || tab_tracker >= TAB_LIMIT)
        return "";

    std::string tabout = "";
    for (int i = 0; i < tab_tracker; ++i)
        tabout += '\t';
    return tabout;
}

void Compiler::write_main_start()
{
    writer << "int main()\n{\n";
    ++tab_tracker;

    // write out the C version of the array of bytes
    writer << write_tab() << "int " << token_arr_name << "[" << (std::to_string(ARRAY_LENGTH))
           << "];\n";
    writer << write_tab() << "int xregister = 0;\n";
    write_newline();
}

void Compiler::write_main_end()
{
    writer << write_tab() << "\n}\n";
}

void Compiler::write_loop_start()
{
    writer << write_tab() << "while(1)\n" << write_tab() << "{\n";
    ++tab_tracker;

    // write the shell of the 'if'
    writer << write_tab() << "if(0 == " << token_arr_name << "[xregister])\n";
    writer << write_tab() << "{\n";

    // write the break
    ++tab_tracker;
    writer << write_tab() << "break;\n";
    --tab_tracker;

    // finish the 'if'
    writer << write_tab() << "}\n";
}

void Compiler::write_loop_end()
{
    --tab_tracker;
    writer << "\n" << write_tab() << "}\n";
}

void Compiler::write_inc()
{
    writer << write_tab() << token_arr_name << "[xregister]++;\n";
    writer << write_tab() << "if(" << token_arr_name << "[xregister] > 255) " << token_arr_name
           << "[xregister] = 0;\n";
    write_newline();
}

void Compiler::write_dec()
{
    writer << write_tab() << token_arr_name << "[xregister]--;\n";
    writer << write_tab() << "if(" << token_arr_name << "[xregister] < 0) " << token_arr_name
           << "[xregister] = 255;\n";
    write_newline();
}

void Compiler::write_shl()
{
    writer << write_tab() << "if(xregister - 1 >= 0) xregister--;\n";
    write_newline();
}

void Compiler::write_shr()
{
    writer << write_tab() << "if(xregister + 1 < " << std::to_string(ARRAY_LENGTH)
           << ") xregister++;\n";
    write_newline();
}

void Compiler::write_outp()
{
    writer << write_tab() << "printf(\"%c\"," << token_arr_name << "[xregister]);\n";
    write_newline();
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        puts("No source given.");
        return 1;
    }

    Reader reader;
    Tokenizer tokenizer;
    Compiler compiler;

    std::string input_filename(argv[1]);
    const auto tokens = tokenizer.tokenize(reader.read(input_filename));
    compiler.add_tokens(tokens);
    const auto cres = compiler.compile();
    if (cres)
    {
        std::cout << "Could not compile '" << input_filename << "'\n";
    }
    return cres;
}
