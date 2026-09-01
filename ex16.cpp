#include <fmt/core.h>
#include <vector>
#include <string>

using namespace fmt;
using std::vector, std::string;

int main() {
  vector<int> ages = {10,34,25,19,87,5};
  vector<string> names = {"Louis", "Bernard", "Ipolite", "Arthur", "Jean", "Max"};

  println("I have {} cousins of different ages:", ages.size());

  size_t i = 0;
  while(i < ages.size()) {
    int cousin_age = ages.at(i);
    println("{} is {} years old.", names[i], cousin_age);
    ++i;
  }
}
