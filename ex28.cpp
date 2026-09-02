#include <fmt/core.h>
#include <fstream>
#include <iostream>

using namespace std;
using fmt::print, fmt::println;

int print_file(string filename, size_t& line_count) {
    ifstream in_file{filename, ios::binary};
    string line;

    if(!in_file.is_open()) return 1;

    while (getline(in_file, line)) {
        if (line == "") {
            print("\n");
            continue;
        }

        ++line_count;
        print("\t{}  {}\n", line_count, line);
    }

    return 0;
}

int main(int argc, char* argv[]) {
    size_t line_count = 0;

    if (argc == 1) {
        cerr << "nl: Not enought arguments.\n";
        return 1;
    }
    for (auto i = 1; i < argc; ++i) {
        switch (print_file(argv[i], line_count)) {
            case 1:
                cerr << fmt::format("nl: {}: No file or directory with that name\n", argv[i]);
                return 1;
            default:
                break;
        }
    }
    return 0;
}
