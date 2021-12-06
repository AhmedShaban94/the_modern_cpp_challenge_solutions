#include "Array2D.hpp"
#include "catch2/catch.hpp"

TEST_CASE("testing Array2D class", "[Array2D]")
{
    // [1, 2, 3]
    // [4, 5, 6]
    // [7, 8 ,9]

    SECTION("Testing constructors")
    {
        // vector of vectors ctor.
        REQUIRE_NOTHROW((Array2D<std::size_t, 3, 3>{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}}));

        //  vector ctor.
        REQUIRE_NOTHROW((Array2D<std::size_t, 3, 3>{{1, 2, 3, 4, 5, 6, 7, 8, 9}}));

        // initializer list ctor.
        REQUIRE_NOTHROW((Array2D<std::size_t, 3, 3>{1, 2, 3, 4, 5, 6, 7, 8, 9}));
    }

    SECTION("Testing Array2D")
    {
        Array2D<std::size_t, 3, 3> arr{1, 2, 3, 4, 5, 6, 7, 8, 9};
        const auto [ROWS, COLS] = arr.size();

        SECTION("Testing at()")
        {
            SECTION("testing equality")
            {
                std::size_t value{1};
                for (std::size_t i{0}; i < ROWS; i++)
                {
                    for (std::size_t j{0}; j < COLS; j++)
                    {
                        REQUIRE(value++ == arr.at(i, j));
                    }
                }
            }

            SECTION("testing changing values")
            {
                std::size_t new_value{10};
                for (std::size_t i{0}; i < ROWS; i++)
                {
                    for (std::size_t j{0}; j < COLS; j++)
                    {
                        arr.at(i, j) = new_value;
                        REQUIRE(new_value == arr.at(i, j));
                        new_value++;
                    }
                }
            }

            SECTION("Testing out-of-range")
            {
                REQUIRE_THROWS_AS(arr.at(2, 3), std::out_of_range);
                REQUIRE_THROWS_AS(arr.at(3, 3), std::out_of_range);
                REQUIRE_THROWS_AS(arr.at(4, 3), std::out_of_range);
                REQUIRE_THROWS_AS(arr.at(4, 4), std::out_of_range);
                REQUIRE_THROWS_AS(arr.at(-1, -2), std::out_of_range);
            }
        }

        SECTION("Testing () operator")
        {
            SECTION("testing equality")
            {
                std::size_t value{1};
                for (std::size_t i{0}; i < ROWS; i++)
                {
                    for (std::size_t j{0}; j < COLS; j++)
                    {
                        REQUIRE(value++ == arr(i, j));
                    }
                }
            }

            SECTION("testing changing values")
            {
                std::size_t new_value{10};
                for (std::size_t i{0}; i < ROWS; i++)
                {
                    for (std::size_t j{0}; j < COLS; j++)
                    {
                        arr.at(i, j) = new_value;
                        REQUIRE(new_value == arr(i, j));
                        new_value++;
                    }
                }
            }

            SECTION("Testing out-of-range")
            {
                REQUIRE_THROWS_AS(arr(2, 3), std::out_of_range);
                REQUIRE_THROWS_AS(arr(3, 3), std::out_of_range);
                REQUIRE_THROWS_AS(arr(4, 3), std::out_of_range);
                REQUIRE_THROWS_AS(arr(4, 4), std::out_of_range);
                REQUIRE_THROWS_AS(arr(-1, -2), std::out_of_range);
            }
        }

        SECTION("Testing data(), begin() & end()")
        {
            REQUIRE_NOTHROW(arr.data());
            REQUIRE_NOTHROW(arr.begin());
            REQUIRE_NOTHROW(arr.end());
        }

        SECTION("Testing fill()")
        {
            constexpr auto VALUE{10};
            arr.fill(VALUE);
            std::for_each(arr.begin(), arr.end(), [VALUE](const auto &ele) { REQUIRE(ele == VALUE); });
        }

        SECTION("Testing swap()")
        {
            Array2D<std::size_t, 3, 3> other{{11, 12, 13, 14, 15, 16, 17, 18, 19}};
            arr.swap(other);

            std::size_t value{11};
            std::for_each(arr.begin(), arr.end(), [&value](const auto &ele) { REQUIRE(ele == value++); });
        }

        SECTION("Testing dimension mismatch")
        {
            REQUIRE_THROWS_AS((Array2D<std::size_t, 3, 3>{{1, 2, 3}}), std::runtime_error);
            REQUIRE_THROWS_AS((Array2D<std::size_t, 1, 1>{{1, 2, 3, 4, 5, 6, 7, 8}}), std::runtime_error);
            REQUIRE_THROWS_AS((Array2D<std::size_t, 1, 1>{{{1, 2, 3}, {4, 5, 6}, {7, 8}}}), std::runtime_error);
        }

        SECTION("Testing print()")
        {
            REQUIRE_NOTHROW(arr.print());
        }
    }
}