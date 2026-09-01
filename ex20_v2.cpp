#include <fmt/core.h>
#include <fstream>
#include <vector>

using std::vector, std::string, std::ifstream, std::ios;
using fmt::println, fmt::print;

int chunk_number(const string& line, size_t start, size_t end) {
  string chunk = line.substr(start, end - start);
  return stoi(chunk);
}

vector<int> parse_line(const string& line) {
  vector<int> result;
  size_t start = 0;
  size_t end = line.find(",", start);

  while(end != string::npos) {
    int as_number = chunk_number(line, start, end);
    result.push_back(as_number);

    start = end + 1;
    end = line.find(",", start);
  }

  // need to get the final chunk
  int as_number = chunk_number(line, start, end);
  result.push_back(as_number);

  return result;
}

int main(int argc, char* argv[]) {
  string filename = {argv[1]};
  ifstream in_file{filename, std::ios::binary};
  vector<vector<int>>table;

  if(!in_file.is_open()) {
    println("failed to open {}", filename);
    return 1;
  }

  string line;

  for (size_t i=0; in_file; ++i) {
    getline(in_file, line);

    if(line == "") break;

    table.push_back(parse_line(line));
  }

  for (vector<int> row : table) {
    for (int cell : row) {
      print("{}\t", cell);
    }
    print("\n");
  }
}
