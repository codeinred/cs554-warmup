#include <files.hpp>
#include <formatting.hpp>

int main(int argc, char** argv) {

    namespace fs = std::filesystem;
    using namespace compiler;

    // Check that a filename was provided as input
    if (argc == 1) {
        fmt::print(
            stderr,
            "Missing filename. Usage: \n\n\t{} <filename>\n\n",
            argv[0]);
        return 0;
    }

    // Get the name of the file from the first argument
    fs::path filename = argv[1];

    // Execute the file as a program if it exists.
    if (fs::exists(filename)) {

        std::vector<uint> instructions =
            read_words_from_bytes(read_all_bytes(filename));

        for(uint i : instructions) {
            fmt::print("{}\n", instruction{i});
        }
    } else {
        fmt::print("Couldn't find '{}'\n", filename.c_str());
    }
}
