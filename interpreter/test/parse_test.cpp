#include <catch2/catch_test_macros.hpp>
#include "interpreter.hpp"

TEST_CASE("Empty Parse", "[parse]")
{
    BrainFck::Parser parser;
    REQUIRE(0 == parser.parse(""));
}
