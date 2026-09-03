#include <fmt/core.h>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::string filename{argv[1]};

    fs::path fp{filename};

    if (!fp.has_parent_path()) {
        fp = "./" / fp;
    }
    fmt::println("{}", fp.parent_path().string());
}
