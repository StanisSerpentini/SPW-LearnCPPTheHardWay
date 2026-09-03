#include <fmt/core.h>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string filename{argv[1]};

    fs::path fp{filename};

    fmt::println("{}", fp.filename().string());
}
