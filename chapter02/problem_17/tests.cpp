#include "Array2D.hpp"
#include "catch2/catch.hpp"

TEST_CASE("testing", "[Array2D]")
{
    // [1, 2, 3]
    // [4, 5, 6]
    // [7, 8 ,9]

    SECTION("Testing non-const Array2D")
    {
        Array2D<std::size_t, 3, 3> arr{{1, 2, 3, 4, 5, 6, 7, 8, 9}};

        SECTION("Testing at()")
        {
            SECTION("testing equality")
            {
                REQUIRE(1 == arr.at(0, 0));
                REQUIRE(2 == arr.at(0, 1));
                REQUIRE(3 == arr.at(0, 2));
                REQUIRE(4 == arr.at(1, 0));
                REQUIRE(5 == arr.at(1, 1));
                REQUIRE(6 == arr.at(1, 2));
                REQUIRE(7 == arr.at(2, 0));
                REQUIRE(8 == arr.at(2, 1));
                REQUIRE(9 == arr.at(2, 2));
            }

            SECTION("testing changing values")
            {
                arr.at(0, 0) = 11;
                REQUIRE(11 == arr.at(0, 0));

                arr.at(0, 1) = 12;
                REQUIRE(12 == arr.at(0, 1));

                arr.at(0, 2) = 13;
                REQUIRE(13 == arr.at(0, 2));

                arr.at(1, 0) = 14;
                REQUIRE(14 == arr.at(1, 0));

                arr.at(1, 1) = 15;
                REQUIRE(15 == arr.at(1, 1));

                arr.at(1, 2) = 16;
                REQUIRE(16 == arr.at(1, 2));

                arr.at(2, 0) = 17;
                REQUIRE(17 == arr.at(2, 0));

                arr.at(2, 1) = 18;
                REQUIRE(18 == arr.at(2, 1));

                arr.at(2, 2) = 19;
                REQUIRE(19 == arr.at(2, 2));
            }

            SECTION("Testing out-of-range")
            {
                REQUIRE_THROWS_AS(arr.at(2, 3), std::out_of_range);
            }
        }
    }

    SECTION("Testing const Array2D")
    {
        const Array2D<std::size_t, 3, 3> const_arr{{1, 2, 3, 4, 5, 6, 7, 8, 9}};
    }
}