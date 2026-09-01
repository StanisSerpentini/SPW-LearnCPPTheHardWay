#include <fmt/core.h>

using namespace fmt;

int main() {
  println("I will run.");

  goto skipped;

  println("I will NOT run.");

skipped:
  println("I will also run.");

  return 0;
}
