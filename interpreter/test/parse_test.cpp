#include "interpreter.hpp"
#include <catch2/catch_test_macros.hpp>

const char *test1 = "This is a test Brainf*ck script written"
                    "for Coding Challenges!"
                    "++++++++++[>+>+++>+++++++>++++++++++<<<"
                    "<-]>>>++.>+.+++++++..+++.<<++++++++++++"
                    "++.------------.>-----.>.-----------.++"
                    "+++.+++++.-------.<<.>.>+.-------.+++++"
                    "++++++..-------.+++++++++.-------.--.++"
                    "++++++++++++. What does it do?";

const char *test2 = "++++++++++[>+>+++>+++++++>++++++++++<<<<-]>>>++.>+.+++++++..+++.<<+++.";
const char *test3 = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]"
                    ">>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";

TEST_CASE("Empty Parse", "[parse]")
{
    BrainFck::Parser parser;
    REQUIRE(0 == parser.parse(""));
}

TEST_CASE("Hello Coding Challenges", "[parse]")
{
    BrainFck::Parser parser;
    REQUIRE(0 == parser.parse(test1));
}

TEST_CASE("Hello!", "[parse]")
{
    BrainFck::Parser parser;
    REQUIRE(0 == parser.parse(test2));
}

TEST_CASE("Hello World!", "[parse]")
{
    BrainFck::Parser parser;
    REQUIRE(0 == parser.parse(test3));
}
