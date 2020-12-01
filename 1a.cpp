// AoC 2020 - 1a.cpp

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

#include "1a.hpp"


class line {
    std::string data;
public:
    friend std::istream &operator>>(std::istream &is, line &l) {
        std::getline(is, l.data);
        return is;
    }
    operator std::string() const { return data; }    
};

std::vector<int64_t> read_ints(std::istream &ifs) {
  std::vector<int64_t> lines;
  std::transform(std::istream_iterator<line>(ifs),
                 std::istream_iterator<line>(), std::back_inserter(lines),
                 [&](const line &l) { return std::stol(l); });
  return lines;
}

std::vector<int64_t> read_ints(const std::string& f)
{
    auto ifs = std::ifstream(f,std::ifstream::in);
    if (!ifs) {
        std::cerr << "Unable to open file: " << f << "\n";
        exit(-1);
    }
    return read_ints(ifs);
}

int main(int argc, char *argv[]) {
  auto input = read_ints("day1_input");
  for (const auto i : input) {
    for (const auto j : input) {
      for (const auto k : input){
        if ((i + j + k) == 2020) {
          std::cout << i * j * k << "\n";
          return 0;
        }
      }
    }
  }
}