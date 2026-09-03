#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;
using fmt::print, fmt::println;

void count (istream& in, size_t& nb_line, size_t& nb_word, size_t& nb_byte) {
    string line;
    auto nb_sep = 0;

    while (getline(in, line)) {
        if (!in.eof())
            line += '\n';
        
        if (line.find('\n') != std::string::npos)
            ++nb_line;
        nb_sep += count(line.begin(), line.end(), ' ');
        nb_sep += count(line.begin(), line.end(), '\n');
        nb_word += (nb_sep > 0) ? (nb_sep + 1) : (0);
        nb_byte += line.size();
    }
}

int main(int argc, char *argv[]) {
    ifstream in_file;
    size_t nb_line = 0, nb_word = 0, nb_byte = 0;
    size_t total_line = 0, total_word = 0, total_byte = 0;

    if ((argc - 1) == 1) {
        in_file = ifstream(argv[1]);
        if (!in_file.is_open()) {
            cerr << fmt::format("wc: {}: No file or directory with that name\n", argv[1]);
            return 1;
        }
        count(in_file, nb_line, nb_word, nb_byte);
        println("{:>2} {:>2} {:>2} {}", nb_line, nb_word, nb_byte, argv[1]);
    } else if ((argc - 1) > 0) {
        for (auto i = 1; i < argc; ++i) {
            in_file = ifstream(argv[i]);
            if (!in_file.is_open()) {
                cerr << fmt::format("wc: {}: No file or directory with that name\n", argv[i]);
                return 1;
            }
            count(in_file, nb_line, nb_word, nb_byte);
            println("{:>2} {:>2} {:>2} {}", nb_line, nb_word, nb_byte, argv[i]);
            total_line += nb_line, total_word += nb_word, total_byte += nb_byte;
            nb_line = 0, nb_word = 0, nb_byte = 0;
        }
        println("{:>2} {:>2} {:>2} total", total_line, total_word, total_byte);
    } else {
        count(cin, nb_line, nb_word, nb_byte);
        println("{:>7} {:>7} {:>7}", nb_line, nb_word, nb_byte);
    }
    return 0;
}
    
