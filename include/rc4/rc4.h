#ifndef RC4_H
#define RC4_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include "ksa.h"
#include "prga.h"
#include "hex.h"

namespace rc4 {

// API mức thấp: chạy RC4 trên buffer
inline std::vector<uint8_t> rc4_apply(const std::vector<uint8_t>& key,
                                      const std::vector<uint8_t>& data) {
    if (key.empty()) return {};
    State st = ksa(key.data(), key.size());
    std::vector<uint8_t> out(data.size());
    prga_apply(st, data.data(), out.data(), out.size());
    return out;
}

// API tiện dụng cho std::string
inline std::vector<uint8_t> encrypt_raw(const std::string& plaintext, const std::string& key) {
    std::vector<uint8_t> k(key.begin(), key.end());
    std::vector<uint8_t> p(plaintext.begin(), plaintext.end());
    return rc4_apply(k, p);
}

inline std::string encrypt_to_hex(const std::string& plaintext, const std::string& key) {
    return to_hex(encrypt_raw(plaintext, key));
}

// RC4: giải mã = mã hoá (XOR với cùng keystream)
inline std::string decrypt_from_hex(const std::string& hex_cipher, const std::string& key) {
    std::vector<uint8_t> k(key.begin(), key.end());
    std::vector<uint8_t> c = from_hex(hex_cipher);
    std::vector<uint8_t> p = rc4_apply(k, c);
    return std::string(p.begin(), p.end());
}

} // namespace rc4

#endif // RC4_H
