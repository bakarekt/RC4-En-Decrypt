#ifndef RC4_HEX_H
#define RC4_HEX_H

#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>

namespace rc4 {

inline std::string to_hex(const std::vector<uint8_t>& data) {
    static const char* digits = "0123456789ABCDEF";
    std::string out; out.reserve(data.size() * 2);
    for (auto b : data) {
        out.push_back(digits[b >> 4]);
        out.push_back(digits[b & 0x0F]);
    }
    return out;
}

inline uint8_t hex_val(char c) {
    if ('0' <= c && c <= '9') return static_cast<uint8_t>(c - '0');
    if ('a' <= c && c <= 'f') return static_cast<uint8_t>(c - 'a' + 10);
    if ('A' <= c && c <= 'F') return static_cast<uint8_t>(c - 'A' + 10);
    throw std::invalid_argument("Invalid hex digit");
}

inline std::vector<uint8_t> from_hex(const std::string& hex) {
    if (hex.size() % 2 != 0) throw std::invalid_argument("Hex string length must be even");
    std::vector<uint8_t> out; out.reserve(hex.size() / 2);
    for (std::size_t i = 0; i < hex.size(); i += 2) {
        uint8_t hi = hex_val(hex[i]);
        uint8_t lo = hex_val(hex[i + 1]);
        out.push_back(static_cast<uint8_t>((hi << 4) | lo));
    }
    return out;
}

} // namespace rc4

#endif // RC4_HEX_H
