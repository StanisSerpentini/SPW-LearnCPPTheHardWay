#include <fmt/core.h>
#include <fstream>
#include <iostream>

using namespace std;
using fmt::print, fmt::println;

int print_file(ifstream& in_file, size_t& line_count) {
    string line;

    if(!in_file.is_open()) return 1;

    while (getline(in_file, line)) {
        if (line == "") {
            print("\n");
            continue;
        }

        ++line_count;
        println("{:>6}  {}", line_count, line);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    size_t line_count = 0;

    if (argc > 1) {
        for (auto i = 1; i < argc; ++i) {
            ifstream in_file{argv[i]};

            if (!in_file.is_open()) {
                cerr << fmt::format("nl: {}: No file or directory with that name\n", argv[i]);
                return 1;
            }

            print_file(in_file, line_count);
        }
    } else {
        ifstream in_file{"/dev/stdin"};
        print_file(in_file, line_count);
    }
    return 0;
}
