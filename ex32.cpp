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

size_t get_nb_line(int& argc, char**& argv) {
    auto i = 1;

    for (; i < argc && strcmp(argv[i], "-n") != 0; ++i);
    return stoull(argv[i + 1]);
}

void test_file_open(ifstream& in_file, string filename) {
    if (!in_file.is_open()) {
        cerr << fmt::format("head: {}: ", filename) 
            << "No file or directory with that name" << endl;
        exit(1);
    }
}

string first_arg(int& argc, char**& argv) {
    auto i = 1;
    string arg;

    for (; i < argc && argv[i][0] == '-'; ++i) {
        if (strcmp(argv[i], "-n") == 0)
            ++i;
    }
    arg = string(argv[i]);
    return arg;
}

void display_n_line(istream& in, size_t &n) {
    string line;

    for (size_t i = 0; i < n && getline(in, line); ++i) {
        if (!in.eof())
            line += '\n';
        print("{}", line);
    }
}

int main(int argc, char* argv[]) {
    vector<char> opts;
    ifstream in_file;
    char opt_char = getopt(argc, argv, "n");
    size_t nb_line = 10;

    while (opt_char != -1) {
        opts.push_back(opt_char);
        opt_char = getopt(argc, argv, "n");
    }

    if (find(opts.begin(), opts.end(), 'n') != opts.end()) {
        nb_line = get_nb_line(argc, argv);
    }

    if (count_args(argc, argv) > 0) {
        in_file = ifstream(first_arg(argc, argv));
        test_file_open(in_file, first_arg(argc, argv));
        display_n_line(in_file, nb_line);
    }
}
