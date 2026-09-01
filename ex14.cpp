#include <fmt/core.h>

using namespace fmt;

int main() {
    int i = 0;

    display_i:
        println("{}",i);
    ++i;
    if (i < 20)
        goto display_i;
    
    return 0;
}
