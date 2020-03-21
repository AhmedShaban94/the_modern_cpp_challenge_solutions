#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "problem_01.h"


TEST_CASE("testProblem1", "[single-file]") {
    SECTION("test if function returns expected string")
    {
        REQUIRE("Hello World" == Problem01::testFunc());
    
    }
}
