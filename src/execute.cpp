#include <files.hpp>
#include <fmt/core.h>

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

        // fmt::print("Loading '{}'\n", filename.c_str());
        // Load the machine from a file
        machine m = load_from_file(filename);

        // fmt::print("Running '{}'\n", filename.c_str());
        // Run the machine
        m.run_loop_vectorized();
    } else {
        fmt::print("Couldn't find '{}'\n", filename.c_str());
    }
}
