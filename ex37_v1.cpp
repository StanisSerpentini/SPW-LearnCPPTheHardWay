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

void format_line(string& line, vector<string>& tab_stops) {
    string spaces = "    ";

    for (auto sep : tab_stops) {
        if (line.find(sep) != string::npos)
            line.replace(line.find(sep), sep.size(), spaces);
    }
}

void expand(string file, string tab_stop) {
    ifstream infile{file};
    ofstream outfile{".my_expand"};
    vector<string> tab_stops = split(tab_stop, ",");
    string line;

    if (outfile.is_open() && infile.is_open()) {
        while (getline(infile, line)) {
            format_line(line, tab_stops);
            outfile << line << endl;
        }
        outfile.close();
        infile.close();
        rename(".my_expand", file.c_str());
    } else
        cerr << "Unable to open file";
}

int main(int argc, char* argv[]) {
    string tab_stop = "\t";
    int opt;

    while((opt = getopt(argc, argv, "t:")) != -1) {
        switch(opt) {
            case 't':
                tab_stop = optarg;
                break;
            default:
                return 1;
        }
    }

    if (argc - optind != 1)
        return 1;
    expand(argv[optind], tab_stop);
}
