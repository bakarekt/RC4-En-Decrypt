#include <iostream>
#include <string>
#include "../include/rc4/rc4.h"

int main(int argc, char** argv) {
    const std::string key = (argc >= 2) ? argv[1] : "HUST-2025";
    const std::string plaintext = (argc >= 3) ? argv[2]
        : "Hanoi University of Science and Technology";
    const std::string hex_cipher = rc4::encrypt_to_hex(plaintext, key);
    std::cout << hex_cipher << std::endl;
    return 0;
}
