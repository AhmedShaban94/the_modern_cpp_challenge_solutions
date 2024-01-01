#include "Ipv4.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("IPv4 Address class constructor validation", "[IPv4]") {
  const std::unordered_map<std::string, uint32_t> valid_ip_addresses{
      {"255.255.255.255", 4294967295}, {"128.147.0.1", 2157117441},  {"123.70.50.1", 2068197889},
      {"128.107.20.1", 2154501121},    {"128.107.30.1", 2154503681}, {"128.107.20.10", 2154501130},
      {"128.107.10.15", 2154498575}};

  const std::vector<std::string> invalid_ip_addresses{"",
                                                    "some string",
                                                    "360.255.255.255",
                                                    "255.360.255.255",
                                                    "255.255.360.255",
                                                    "255.255.255.360",
                                                    "255,255,255,255",
                                                    "255.-255.255.255",
                                                    "255.255.255.255.255"};

  SECTION("IPv4 Address class string constructor validation") {
    for (const auto& [str, dec] : valid_ip_addresses) {
      REQUIRE_NOTHROW(IPv4{str});
      REQUIRE_NOTHROW(IPv4{dec});
      REQUIRE(dec == static_cast<uint32_t>(IPv4{str}));
    }

    for (const auto& addr : invalid_ip_addresses) REQUIRE_THROWS_AS(IPv4{addr}, IpAddressException);
  }

  SECTION("testing input stream operator") {
    std::stringstream ss;
    IPv4 ip{};

    for (const auto& addr : valid_ip_addresses) {
      ss << addr.first;
      CHECK_NOTHROW(ss >> ip);
    }

    ss.clear();

    for (const auto& addr : invalid_ip_addresses) {
      ss << addr;
      REQUIRE_THROWS_AS(ss >> ip, IpAddressException);
    }
  }
}