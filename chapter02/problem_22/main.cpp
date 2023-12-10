#include <iostream>
#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

using Catch::Approx;

enum class TEMP_CONVERT_UNITS { TO_KELVIN, TO_FAHRENHEIT };

long double operator""_deg(long double temp) {
    return temp;
}
long double operator""_k(long double temp) {
    return temp - 273.15;
}
long double operator""_f(long double temp) {
    return (temp - 32) * 0.5556;
}

long double convert_temp(const long double& degree,
                         const TEMP_CONVERT_UNITS& unit) {
    switch (unit) {
        case TEMP_CONVERT_UNITS::TO_FAHRENHEIT:
            return (degree / 0.5556) + 32;
        case TEMP_CONVERT_UNITS::TO_KELVIN:
            return degree + 273.15;
        default:
            return degree;
    }
}

TEST_CASE("temperature conversion and user-defined literals",
          "[temp_conversion]") {
    SECTION("Testing (_deg) user-defined literal operator") {
        REQUIRE(33.0_deg == Approx(33.0).margin(1e-2));
        REQUIRE(10.0_deg == Approx(10.0).margin(1e-2));
        REQUIRE(33.5_deg == Approx(33.5).margin(1e-2));
        REQUIRE(10.5_deg == Approx(10.5).margin(1e-2));
    }

    SECTION("Testing (_f) user-defined literal operator") {
        REQUIRE(33.0_f == Approx(0.5556).margin(1e-2));
        REQUIRE(10.0_f == Approx(-12.2222).margin(1e-2));
        REQUIRE(33.5_f == Approx(0.8333).margin(1e-2));
        REQUIRE(10.5_f == Approx(-11.9444).margin(1e-2));
    }

    SECTION("Testing (_k) user-defined literal operator") {
        REQUIRE(33.0_k == Approx(-240.0).margin(1e-0));
        REQUIRE(10.0_k == Approx(-263.0).margin(1e-0));
        REQUIRE(10.5_k == Approx(-262.6).margin(1e-0));
    }
}