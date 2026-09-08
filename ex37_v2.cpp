#include <fmt/core.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;
using fmt::print, fmt::println;

vector<string> split(string s, const string& delimiter) {
    vector<string> tokens;
    size_t pos = 0;
    string token;

    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

void format_line(string& line, vector<string>& spaces) {
    string tab = "\t";

    for (auto sep : spaces) {
        if (line.find(sep) != string::npos)
            line.replace(line.find(sep), sep.size(), tab);
    }
}

void unexpand(string file, string spaces) {
    ifstream infile{file};
    ofstream outfile{".my_unexpand"};
    vector<string> spaces_list = split(spaces, ",");
    string line;

    if (outfile.is_open() && infile.is_open()) {
        while (getline(infile, line)) {
            format_line(line, spaces_list);
            outfile << line << endl;
        }
        outfile.close();
        infile.close();
        rename(".my_unexpand", file.c_str());
    } else
        cerr << "Unable to open file";
}

int main(int argc, char* argv[]) {
    string spaces = "    ";
    int opt;

    while((opt = getopt(argc, argv, "t:")) != -1) {
        switch(opt) {
            case 't':
                spaces = optarg;
                break;
            default:
                return 1;
        }
    }

    if (argc - optind != 1)
        return 1;
    unexpand(argv[optind], spaces);
}
