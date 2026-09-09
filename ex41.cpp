#include <fmt/core.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;
using fmt::print, fmt::println;

vector<string> dump_file(istream& in) {
    vector<string> file_content;
    string line;

    while (getline(in, line)) {
        if (!in.eof())
            line += '\n';
        file_content.push_back(line);
    }
    return file_content;
}

void print_file(vector<string>& file_content) {
    for (auto line : file_content) {
        print("{}", line);
    }
}

int main(int argc, char *argv[]) {
    vector<string> file_content;
    ifstream in_file;

    for (auto i = 1; i < argc; ++i) {
        in_file = ifstream(argv[i]);
        if (!in_file.is_open()) {
            println("Can't open {}", argv[i]);
            continue;
        }
        file_content = dump_file(in_file);
        in_file.close();
        sort(file_content.begin(), file_content.end());
        print_file(file_content);
    }
}
