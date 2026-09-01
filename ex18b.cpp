#include <fmt/core.h>
#include <vector>
#include <algorithm>

using std::string, std::vector;
using namespace fmt;

int main() {
  vector<string> fruit = {
    "Apple", "Orange", "Pear",
    "Grape", "Durian", "Mango"
  };

  std::string target = "Orange";

  auto found = std::find(fruit.begin(), fruit.end(), target);

  if(found == std::end(fruit)) {
    println("DIDN'T FIND IT");
  } else {
    println("FOUND: {}", *found);
  }
}
