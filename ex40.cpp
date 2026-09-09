#include <fmt/core.h>
#include <unordered_map>
#include <unistd.h>

using namespace std;
using fmt::print, fmt::println;

unordered_map<string, string> init_map() {
    unordered_map<string, string> escape_sequences_map = {
        {"\\'", "\n"},
        {"\\\"", "\""},
        {"\\?", "\?"},
        {"\\\\", "\\"},
        {"\\a", "\a"},
        {"\\b", "\b"},
        {"\\f", "\f"},
        {"\\n", "\n"},
        {"\\r", "\r"},
        {"\\t", "\t"},
        {"\\v", "\v"},
    };

    return escape_sequences_map;
}

string format_string(string s, unordered_map<string,string>& escape_seq_map) {
    for (auto [key, value] : escape_seq_map) {
        if (s.find(key) != string::npos) {
            s.replace(s.find(key), key.size(), value);
        }
    }
    return s;
}

int main(int argc, char *argv[]) {
    int opt;
    auto umap = init_map();
    string s;
    bool interpret = false;

    while((opt = getopt(argc, argv, "he")) != -1) {
        switch(opt) {
            case 'e':
                interpret = true;
                break;
            case 'h':
                println("USAGE: my_echo [-e|-h]... <string>");
                return 0;
            default:
                return 1;
        }
    }
    s = (interpret) ? format_string(argv[optind], umap) : argv[optind];
    println("{}", s);
}
