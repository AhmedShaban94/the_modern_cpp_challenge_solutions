#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"
#include <algorithm>
#include <bitset>
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

class IPv4
{
private:
    std::string ip_;

public:
    IPv4() = default;
    explicit IPv4(const std::string_view str) : ip_{ validate_ip_addr(str) }
    {
    }

    IPv4(const IPv4&) = default;
    IPv4& operator=(const IPv4&) = default;

    IPv4(IPv4&&)  = default;
    IPv4& operator=(IPv4&&) = default;

    ~IPv4() = default;

    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip)
    {
        os << ip.ip_;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IPv4& ip)
    {
        is >> std::setw(15);
        is.ignore(std::numeric_limits<std::size_t>::max(), '\n');
        std::getline(is, ip.ip_);
        ip.validate_ip_addr(ip.ip_);
        return is;
    }

    operator int32_t() const
    {
        std::istringstream ss{ this->ip_};
        std::string token;
        std::string binary_string;
        while (std::getline(ss, token, '.'))
            binary_string.append(std::bitset<8>(std::stoi(token)).to_string());
        return std::bitset<32>(binary_string).to_ulong();
    }

    std::string validate_ip_addr(const std::string_view ip)
    {
        std::stringstream ss{};
        ss << ip;

        std::string token;
        std::size_t token_counter{ 0 };
        auto is_number = [](const std::string& str) {
            return !str.empty()
                && std::all_of(str.begin(), str.end(), ::isdigit);
        };

        while (std::getline(ss, token, '.'))
        {
            token_counter++;
            if (!is_number(token) || std::stoi(token) > 255
                || std::stoi(token) < 0)
                throw IpAddressException{};
        }

        if (token_counter != 4)
            throw IpAddressException{};

        return ss.str();
    }

    class IpAddressException : public std::runtime_error
    {
    public:
        explicit IpAddressException(const char* what = "Invalid IPv4 address")
            : runtime_error{ what }
        {
        }
    };
};

TEST_CASE("IPv4 Address class constructor validation", "[IPv4]")
{
    const std::vector<std::string> validIpAddresses{
        "255.255.255.255", "128.147.0.1",   "123.70.50.1",  "128.107.20.1",
        "128.107.30.1",    "128.107.20.10", "128.107.10.15"
    };

    const std::vector<std::string> invalidIpAddresses{ "",
                                                       "some string",
                                                       "360.255.255.255",
                                                       "255.360.255.255",
                                                       "255.255.360.255",
                                                       "255.255.255.360",
                                                       "255,255,255,255",
                                                       "255.-255.255.255",
                                                       "255.255.255.255.255" };

    SECTION("IPv4 Address class constructor validation")
    {
        for (const auto& addr : validIpAddresses)
            REQUIRE_NOTHROW(IPv4{ addr });

        for (const auto& addr : invalidIpAddresses)
            REQUIRE_THROWS_AS(IPv4{ addr }, IPv4::IpAddressException);
    }

    SECTION("testing input stream operator")
    {
        std::stringstream ss;
        IPv4 ip{};

        for (const auto& addr : validIpAddresses)
        {
            ss << addr;
            CHECK_NOTHROW(ss >> ip);
        }

        ss.clear();

        for (const auto& addr : invalidIpAddresses)
        {
            ss << addr;
            REQUIRE_THROWS_AS(ss >> ip, IPv4::IpAddressException);
        }
    }
}

int main(int argc, char* argv[])
{
    const std::string ip_str = "10.0.10.10";
    std::cout << int32_t(IPv4{ip_str}) << '\n';
    return EXIT_SUCCESS;
    // // run tests
    // int result_ = Catch::Session().run(argc, argv);
    // // global clean-up...
    // return result_;
}