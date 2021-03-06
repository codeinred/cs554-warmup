#pragma once

#include <filesystem>
#include <fstream>
#include <machine.hpp>
#include <string_view>

namespace compiler {
namespace fs = std::filesystem;

auto read_all_bytes(fs::path filename) {
    // Get the size
    auto filesize_bytes = fs::file_size(filename);

    // CReate a buffer for the bytes
    std::vector<std::byte> bytes(filesize_bytes);

    // Open the file
    auto file = std::ifstream(filename, std::ios::binary);

    // Read the bytes
    file.read((char*)bytes.data(), bytes.size());

    return bytes;
}

uint32_t read_one_word(std::byte* bytes) {
    // When the program file is read, each consecutively read four bytes A, B,
    // C, D should be interpreted with A as the most significant byte, etc. (The
    // program file size as reported by Unix ls will always be divisible by 4.)
    uint32_t word = uint32_t(bytes[0]) << 24 // Byte A
                  | uint32_t(bytes[1]) << 16 // Byte B
                  | uint32_t(bytes[2]) << 8  // Byte C
                  | uint32_t(bytes[3]);      // Byte D
    return word;
}
std::vector<uint> read_words_from_bytes(std::vector<std::byte> bytes) {
    auto words = std::vector<uint32_t>(bytes.size() / 4);
    for (size_t i = 0; i < words.size(); i++) {
        size_t byte_offset = i * 4;
        words[i] = read_one_word(bytes.data() + byte_offset);
    }
    return words;
}

machine load_from_file(fs::path filename) {
    auto words = read_words_from_bytes(read_all_bytes(filename));
    return machine(words);
}
} // namespace compiler
