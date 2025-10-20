#ifndef RC4_KSA_H
#define RC4_KSA_H

#include <cstddef>
#include <cstdint>
#include <array>

namespace rc4 {

struct State {
    std::array<uint8_t, 256> S{};
    uint8_t i = 0;
    uint8_t j = 0;
};

inline State ksa(const uint8_t* key, std::size_t key_len) {
    State st;
    for (int i = 0; i < 256; ++i) st.S[static_cast<std::size_t>(i)] = static_cast<uint8_t>(i);
    uint8_t j = 0;
    for (int i = 0; i < 256; ++i) {
        j = static_cast<uint8_t>(j + st.S[static_cast<std::size_t>(i)] + key[i % key_len]);
        std::swap(st.S[static_cast<std::size_t>(i)], st.S[static_cast<std::size_t>(j)]);
    }
    st.i = 0; st.j = 0;
    return st;
}

} // namespace rc4

#endif // RC4_KSA_H
