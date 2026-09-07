#include <fmt/core.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
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

void my_copy(string file1, string file2, vector<char> opts) {
    string tmp_src, tmp_dest;

    if (!got_options(opts, "r")) {
        fs::copy_file(file1, file2);
        return;
    }
    fs::create_directory(file2);
    for (auto const& dir_entry : fs::recursive_directory_iterator{file1}) {
        tmp_src = dir_entry.path().string();
        tmp_dest = tmp_src;
        if (tmp_dest.find(file1) != string::npos)
            tmp_dest.replace(tmp_dest.find(file1), file1.size(), file2);
        if (dir_entry.is_directory())
            fs::create_directory(tmp_dest);
        else
            fs::copy_file(tmp_src, tmp_dest);
    }
}

int main(int argc, char* argv[]) {
    vector<char> opts;
    int opt;

    while((opt = getopt(argc, argv, "r")) != -1) {
        switch(opt) {
            case 'r':
                opts.push_back('r');
                break;
            default:
                return 1;
        }
    }

    if(argc - (optind - 1) != 3) {
        fmt::println("USAGE: cp <from_file> <to_file>");
        return 1;
    }

    try {
        my_copy(argv[optind], argv[optind + 1], opts);
    } catch(fs::filesystem_error &e) {
        fmt::println("failed to copy: {}", e.what());
        return 1;
    }
}
