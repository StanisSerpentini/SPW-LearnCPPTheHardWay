#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;
using fmt::print, fmt::println;

int count_args(int& argc, char**& argv) {
    size_t count = 0;

    for (auto i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') ++count;
    }
    return count;
}

void concat(ifstream& in_file, vector<char>& opts, size_t& line_count) {
    string line;

    while (getline(in_file, line)) {
        if (find(opts.begin(), opts.end(), 's') != opts.end() && line == "")
            continue;
        ++line_count;
        if (find(opts.begin(), opts.end(), 'n') != opts.end())
            println("{:>6}  {}", line_count, line);
        else
            println("{}", line);
    }
}

int main(int argc, char* argv[]) {
    size_t line_count = 0;
    vector<char> opts;
    char opt_char = getopt(argc, argv, "ns");

    while (opt_char != -1) {
        opts.push_back(opt_char);
        opt_char = getopt(argc, argv, "ns");
    }

    if (count_args(argc, argv) > 0) {
        for (auto i = 1; i < argc; ++i) {
            if (argv[i][0] == '-')
                continue;
            ifstream in_file{argv[i]};
            if (!in_file.is_open()) {
                cerr << fmt::format("cat: {}: No file or directory with that name\n", argv[i]);
                return 1;
            }
            concat(in_file, opts, line_count);
        }
    } else {
        ifstream in_file{"/dev/stdin"};
        concat(in_file, opts, line_count);
    }
    return 0;
}
