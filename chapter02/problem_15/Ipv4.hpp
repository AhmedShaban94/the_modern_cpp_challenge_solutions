#pragma once
#include <algorithm>
#include <bitset>
#include <exception>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class IpAddressException : public std::runtime_error {
 public:
  explicit IpAddressException(const char* what = "Invalid IPv4 address") : runtime_error{what} {}
};
class IPv4 {
 private:
  std::string ip_;

  std::string validate_ip_addr(const std::string_view ip) const {
    std::stringstream ss{};
    ss << ip;

    std::string token;
    size_t token_counter{0};
    auto is_number = [](const std::string& str) {
      return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    };

    while (std::getline(ss, token, '.')) {
      token_counter++;
      if (!is_number(token) || std::stoi(token) > 255 || std::stoi(token) < 0) throw IpAddressException{};
    }

    if (token_counter != 4) throw IpAddressException{};

    return ss.str();
  }

  std::string to_string(const size_t& decimal) const {
    std::vector<std::string> octets;
    constexpr uint8_t numBits = 32;
    std::bitset<numBits> foo(decimal);
    std::bitset<numBits> mask(0xff);

    for (size_t i = 0; i < numBits / 8; ++i) {
      auto byte = std::to_string(((foo >> (8 * i)) & mask).to_ulong());
      octets.push_back(byte);
    }

    std::reverse(octets.begin(), octets.end());
    return std::accumulate(std::next(octets.begin()), octets.end(), octets[0],
                           [](std::string a, std::string b) { return a + "." + b; });
  }

 public:
  IPv4() = default;
  explicit IPv4(const std::string_view str) : ip_{validate_ip_addr(str)} {}

  explicit IPv4(const size_t& decimal) : ip_(validate_ip_addr(to_string(decimal))) {}

  IPv4(const IPv4&) = default;
  IPv4& operator=(const IPv4&) = default;

  IPv4(IPv4&&) = default;
  IPv4& operator=(IPv4&&) = default;

  ~IPv4() = default;

  friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
    os << ip.ip_;
    return os;
  }

  friend std::istream& operator>>(std::istream& is, IPv4& ip) {
    is >> std::setw(15);
    is.ignore(std::numeric_limits<size_t>::max(), '\n');
    std::getline(is, ip.ip_);
    ip.validate_ip_addr(ip.ip_);
    return is;
  }

  // Added for sake of testing. [iota]
  IPv4& operator++() {
    auto dec = static_cast<uint32_t>(*this);
    dec++;
    *this = IPv4{dec};
    return *this;
  }

  operator uint32_t() const {
    std::istringstream ss{this->ip_};
    std::string token;
    std::string binary_string;
    while (std::getline(ss, token, '.')) binary_string.append(std::bitset<8>(std::stoi(token)).to_string());
    return std::bitset<32>(binary_string).to_ulong();
  }
};