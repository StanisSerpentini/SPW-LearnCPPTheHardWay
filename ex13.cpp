#include <iostream>
#include <fmt/core.h>

using namespace std;
using namespace fmt;

enum color { RED, GREEN, BLUE};

int main() {
  int which_door = 4;

  switch(which_door) {
    case 1:
      println("DOOR #1");
      break;
    case 2:
      println("DOOR #2");
      // fallthrough
    case 3:
      println("DOOR #3");
      break;
    case 4:
      println("DOOR #4");
      break;
    default:
      println("BAD DOOR YOU DIED!");
  }

  color what_color = RED;

  switch(what_color) {
    case color::RED:
      println("COLOR IS RED");
      break;
    case color::BLUE:
      println("COLOR IS BLUE");
      break;
    case color::GREEN:
      println("COLOR IS GREEN");
      break;
    default:
      // how can you hit this?
      println("BAD COLOR");
  }

  return 0;
}
