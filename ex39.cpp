#include <fmt/core.h>
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using fmt::println, fmt::print;

char last_char(string& s) {
    return s.at(s.size() - 1);
}

chrono::duration<long double> parse_time(string user_input) {
    long double num_val = stold(user_input);
    long double seconds = 1;
    chrono::duration<long double>timeskip;

    switch (last_char(user_input)) {
        case 'd':
            seconds *= 24.0;
        case 'h':
            seconds *= 60.0;
        case 'm':
            seconds *= 60.0;
        case 's':
            seconds *= num_val;
            break;
        default:
            seconds *= num_val;
            break;
    }
    timeskip = chrono::duration<long double>(seconds);
    return timeskip;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        println("USAGE: my_sleep [seconds]");
        return 1;
    }

    auto wait_for = parse_time(argv[1]);

    this_thread::sleep_for(wait_for);
}