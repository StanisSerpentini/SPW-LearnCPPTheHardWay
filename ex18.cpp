#include <fmt/core.h>
#include <vector>

using std::string, std::vector;
using namespace fmt;

/* This is a function, just get this working for now
 * and we'll cover them soon.
 */
vector<string> bug_maker() {
  return {"Boo! I'm a Bug!"};
}

int main() {
  vector<string> fruit = {
    "Apple", "Orange", "Pear",
    "Grape", "Durian", "Mango"
  };

  // loop through fruit
  for(auto name : fruit) {
    println("Fruit is {}", name);
  }

  // set them all to something else
  vector<string> guitars = {
    "Stratocaster", "Telecaster", "Bass VI",
    "P-Bass", "ASAT Special", "G&L S500"
  };


  // loop through guitars
  for(auto name : guitars) {
    println("Guitar is {}", name);
  }

  /*
  for(auto name : bug_maker()[0]) {
    println("Probably Crashing: {}", name);
  }
  */
  return 0;
}
