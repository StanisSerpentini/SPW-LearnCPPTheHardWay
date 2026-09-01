#include <iostream>
#include <fmt/core.h>

using namespace std;

int main() {
  int a_int = 1234;
  long a_long = 37812394;
  long long a_long_long = -68354647782938476;
  float a_float = 0.1234;
  double a_double = 3.23499;

  fmt::println("Here's an int {}", a_int);

  string msg = fmt::format(
    "An int {}\n"
    "A long {}\n"
    "A long long {}\n"
    "A float {}\n"
    "A double {}",
    a_int, a_long, a_long_long, a_float, a_double);

  fmt::println("The result is:");
  fmt::println("{}", msg);

  return 0;
}
