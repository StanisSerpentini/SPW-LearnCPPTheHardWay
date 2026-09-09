#include <fmt/core.h>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace std;
using fmt::print, fmt::println;

void uniq(istream& in, bool& inverted) {
    string line;
    string previous;

    getline(in, previous);
    if (!inverted)
        println("{}", previous);
    while (getline(in, line)) {
        if ((inverted) ? (line == previous) : (line != previous))
            println("{}", line);
        if (line != previous)
            previous = line;
    }
}

int main(int argc, char *argv[]) {
    bool inverted = false;
    int opt;

    while((opt = getopt(argc, argv, "hd")) != -1) {
        switch(opt) {
            case 'd':
                inverted = true;
                break;
            case 'h':
                println("USAGE: my_uniq [-d|-h]... [FILE]...");
                return 0;
            default:
                return 1;
        }
    }
    if (argc - optind > 0) {
        for (auto i = optind; i < argc; ++i) {
            ifstream infile{argv[i]};
            uniq(infile, inverted);
        }
    } else
        uniq(cin, inverted);
}
