#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <unistd.h>

using namespace std;
using fmt::print, fmt::println;

namespace fs = std::filesystem;

bool got_options(vector<char>& opts, string opts_string) {
    for (long unsigned int i = 0; i < opts_string.size(); ++i) {
        if (find(opts.begin(), opts.end(), opts_string[i]) != opts.end())
            return true;
    }
    return false;
}

fs::file_type get_filetype(const fs::path& path) {
    fs::file_status status = fs::status(path);

    return status.type();
}

void list_dir(fs::path& filepath, vector<char>& opts) {
    if (got_options(opts, "a"))
        print(".\t..\t");
    for (auto const& dir_entry : fs::directory_iterator{filepath}) {
        if (!got_options(opts, "aA") &&
                dir_entry.path().stem().string().at(0) == '.')
            continue;
        if (got_options(opts, "d") &&
                !(get_filetype(dir_entry) == fs::file_type::directory))
            continue;
        print("{}\t", dir_entry.path().filename().string());
    }
    print("\n");
}

int main(int argc, char* argv[]) {
    fs::path path;
    vector<char> opts;
    int opt;

    while((opt = getopt(argc, argv, "aAd")) != -1) {
        switch(opt) {
            case 'a':
                opts.push_back('a');
                break;
            case 'A':
                opts.push_back('A');
                break;
            case 'd':
                opts.push_back('d');
                break;
            default:
                return 1;
        }
    }

    if (optind < argc) {
        for (auto i = optind; i < argc; i++) {
            path = argv[i];
            list_dir(path, opts);
            println("");
        }
    } else {
        path = ".";
        list_dir(path, opts);
    }
}
