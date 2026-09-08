#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;
using fmt::print, fmt::println;

vector<string> read_stdin() {
    vector<string>content;
    string linebuff;

    while (getline(cin, linebuff))
        content.push_back(linebuff);
    return content;
}

void tee(int argc, char **& argv, bool& append) {
    ofstream out_file;
    ios_base::openmode openmode = (append) ? ios_base::app : ios_base::trunc;
    vector<string>buffer = read_stdin();

    for (auto i = optind; i < argc; ++i) {
        out_file = ofstream(argv[i], openmode);
        if (!out_file.is_open()) {
            println("Can't open {}", argv[i]);
            continue;
        }
        for (auto line : buffer) {
            out_file << line << endl;
        }
    }
    for (auto line : buffer) {
        println("{}", line);
    }
}

int main(int argc, char *argv[]) {
    int opt;
    bool append_mode = false;

    while((opt = getopt(argc, argv, "ha")) != -1) {
        switch(opt) {
            case 'a':
                append_mode = true;
                break;
            case 'h':
                println("USAGE: my_tee [-a|-h]... [FILE]...");
                return 0;
            default:
                return 1;
        }
    }

    if (argc - optind < 1)
        return 1;
    tee(argc, argv, append_mode);
}