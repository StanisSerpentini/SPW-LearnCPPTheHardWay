#include <iostream>
#include <fmt/core.h>

using namespace std;
using namespace fmt;

int main() {
  int x = 0; // initializer

  do { // start of loop
    println("X={}", x); // code
    ++x; // incrementer
  } while(x < 20); // test

  return 0;
}
