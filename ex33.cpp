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

// seekg with one arg -> move to absolute position
// seekg with two args -> move to relative position
// seekg(10, in.end) -> move 10 bytes from the end

void display_n_line(istream& in, size_t &n) {
    in.seekg(0, in.end);
    streampos file_size = in.tellg();
    streampos pos = file_size;
    size_t lines_found = 0;
    string line;
    char c;

    if (n == 0) return;

    while (pos > 0 && lines_found < n) {
        pos -= 1;
        in.seekg(pos);
        in.get(c);

        if (c == '\n' && (pos != file_size - streamoff(1)))
            lines_found++;
    }

    if (pos > 0) {
        in.seekg(pos + streamoff(1));
    } else {
        in.seekg(0, in.beg);
    }

    while (getline(in, line)) {
        if (!in.eof())
            line += '\n';
        print("{}", line);
    }
}

int main(int argc, char* argv[]) {
    vector<char> opts;
    ifstream in_file;
    int opt;
    size_t nb_line = 10;

    while((opt = getopt(argc, argv, "n:")) != -1) {
        switch(opt) {
            case 'n':
                nb_line = std::stoi(optarg);
                break;
            default:
                return 1;
        }
    }

    if (count_args(argc, argv) > 0) {
        in_file = ifstream(first_arg(argc, argv));
        test_file_open(in_file, first_arg(argc, argv));
        display_n_line(in_file, nb_line);
    }
}
