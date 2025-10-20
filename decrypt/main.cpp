#include <iostream>
#include <string>
#include "../include/rc4/rc4.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: decrypt <key> <hex_ciphertext>\n";
        return 1;
    }
    const std::string key = argv[1];
    const std::string hex_cipher = argv[2];
    const std::string plaintext = rc4::decrypt_from_hex(hex_cipher, key);
    std::cout << plaintext << std::endl;
    return 0;
}
