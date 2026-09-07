#include <fmt/core.h>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;
using fmt::print, fmt::println;

void print_date(string format_string) {
    auto time = system_clock::to_time_t(system_clock::now());

    cout << put_time(localtime(&time), format_string.c_str()) << endl;
}

int main(int argc, char* argv[]) {
    string format_string = "%a %d %b %Y %X %Z";

    if (argc != 1 && argc != 2) {
        println("USAGE: date [+FORMAT]");
        return 1;
    }

    if (argc == 2)
        format_string = argv[1];
    print_date(format_string);
}
