#ifndef RC4_PRGA_H
#define RC4_PRGA_H

#include <cstddef>
#include <cstdint>
#include "ksa.h"

namespace rc4 {

inline uint8_t prga_next(State& st) {
    st.i = static_cast<uint8_t>(st.i + 1);
    st.j = static_cast<uint8_t>(st.j + st.S[st.i]);
    std::swap(st.S[st.i], st.S[st.j]);
    uint8_t K = st.S[static_cast<uint8_t>(st.S[st.i] + st.S[st.j])];
    return K;
}

inline void prga_apply(State& st, const uint8_t* in, uint8_t* out, std::size_t len) {
    for (std::size_t n = 0; n < len; ++n) {
        out[n] = static_cast<uint8_t>(in[n] ^ prga_next(st));
    }
}

} // namespace rc4

#endif // RC4_PRGA_H
