// AoC 2020 - 2.cpp

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

class line
{
    std::string data;

public:
    friend std::istream &operator>>(std::istream &is, line &l)
    {
        std::getline(is, l.data);
        return is;
    }
    operator std::string() const { return data; }
};

std::vector<std::string> read_input(std::istream &ifs)
{
    std::vector<std::string> lines;
    std::copy(std::istream_iterator<line>(ifs),
              std::istream_iterator<line>(),
              std::back_inserter(lines));
    return lines;
}

std::vector<std::string> read_input(const std::string &f)
{
    auto ifs = std::ifstream(f, std::ifstream::in);
    if (!ifs)
    {
        std::cerr << "Unable to open file: " << f << "\n";
        exit(-1);
    }
    return read_input(ifs);
}

std::vector<int64_t> read_ints(std::istream &ifs)
{
    std::vector<int64_t> lines;
    std::transform(std::istream_iterator<line>(ifs),
                   std::istream_iterator<line>(), std::back_inserter(lines),
                   [&](const line &l) { return std::stol(l); });
    return lines;
}

std::vector<int64_t> read_ints(const std::string &f)
{
    auto ifs = std::ifstream(f, std::ifstream::in);
    if (!ifs)
    {
        std::cerr << "Unable to open file: " << f << "\n";
        exit(-1);
    }
    return read_ints(ifs);
}

int main(int argc, char *argv[])
{
    auto input = read_input("day2_input");
    int64_t result = 0;
    std::string dash = "-";
    std::string colon = ":";
    std::string space = " ";
    for (auto x : input)
    {
        std::cout << x << "!\n";
        auto low = x.substr(0, x.find(dash));
        auto len = low.length() + dash.length();
        auto high = x.substr(len, x.find(space) - len);
        len += high.length() + space.length();
        auto letter = x.substr(len, x.find(colon) - len);
        len += letter.length() + colon.length();
        auto value = x.substr(len + space.length());
        const char letter_char = *letter.c_str();
        std::cout << low << "!" << high << "!" << letter << "!" << value << "!\n";
        auto count = std::count(value.begin(), value.end(), letter_char);
        if (std::stoi(low) <= count && count <= std::stoi(high))
        {
            result += 1;
        }
    }
    std::cout << result << "\n";
}