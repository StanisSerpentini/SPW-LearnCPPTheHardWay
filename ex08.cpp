#include <sstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  // CHALLENGE 1 HERE
  int a_int = stoi("1");
  long a_long = stol("1");
  long long a_long_long = stoll("1");
  unsigned long a_unsigned_long = stoul("1");
  unsigned long long a_unsigned_long_long = stoull("1");
  float a_float = stof("1.1");
  double a_double = stod("1.1");
  long double a_long_double = stold("1.1");

  string from_number = std::to_string(123456);
  string from_float = std::to_string(1.1000f);

  ostringstream msg;

  // CHALLENGE 2 HERE
  msg << "An int " << a_int << endl;
  msg << "A long " << a_long << endl;
  msg << "A long long " << a_long_long << endl;
  msg << "An unsigned long " << a_unsigned_long << endl;
  msg << "An unsigned long long " << a_unsigned_long_long << endl;
  msg << "An float " << a_float << endl;
  msg << "An double " << a_double << endl;
  msg << "An long double " << a_long_double << endl;

  msg << "From number " << from_number << endl;
  msg << "From float " << from_float << endl;

  cout << "The result is: " << endl << msg.str();

  return 0;
}
