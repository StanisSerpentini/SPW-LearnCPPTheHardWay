#include <vector>
#include <fmt/core.h>
#include <iostream>
#include <fstream>

using namespace std;
using fmt::println;

int main(int argc, char *argv[]) {
    string filename;
    string line;
    vector<string> names;

    //Ask for file name
    println("Enter the name of the file:");
    getline(cin, filename);

    //Load data from the file
    ifstream infile{filename.c_str(), std::ios::binary};

    if(!infile.is_open()) {
        println("failed to open {}", filename);
        return 1;
    }

    while (infile) {
        getline(infile, line);
        if(line == "") break;
        names.push_back(line);
    }


    //Ask for names list
    ofstream outfile{filename.c_str()};
    while (1) {
        line.clear();
        println("Enter a name to add to the list (empty for exit):");
        getline(cin, line);
        if (line == "") break;
        names.push_back(line);
    }

    for(auto& name : names) {
        outfile.write(name.c_str(), name.size());
        outfile.put('\n');
    }
}
