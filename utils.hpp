#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>
#include <string>

class line {
    std::string data;
public:
    friend std::istream &operator>>(std::istream &is, line &l) {
        std::getline(is, l.data);
        return is;
    }
    operator std::string() const { return data; }    
};

std::vector<std::string> read_input(std::istream& ifs)
{
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<line>(ifs), 
            std::istream_iterator<line>(),
            std::back_inserter(lines));
    return lines;
}

std::vector<std::string> read_input(const std::string& f)
{
    auto ifs = std::ifstream(f,std::ifstream::in);
    if (!ifs) {
        std::cerr << "Unable to open file: " << f << "\n";
        exit(-1);
    }
    return read_input(ifs);
}

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