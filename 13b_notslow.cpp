#include "utils.hpp"
#include "numeric"

int quick_maths(int64_t x, int64_t y, int64_t mod)
{
    if (y == 0)
        return 1;
    auto power = quick_maths(x, y / 2, mod) % mod;
    power = (power * power) % mod;
    return (y % 2 == 0) ? power : (x * power) % mod;
}

int main(int argc, char *argv[])
{
    auto input = read_input("day13_input");
    std::vector<std::pair<uint64_t, uint64_t>> buses = {};

    std::stringstream cstring(input[1]);
    int position = 0;
    while (cstring.good())
    {
        std::string section;
        getline(cstring, section, ',');
        if (section == "x")
        {
            position++;
            continue;
        }
        buses.push_back(std::make_pair(std::stoi(section), position));
        position++;
    }
    uint64_t result = 0;
    uint64_t multiplier = 0;
    uint64_t product = 1;
    for (auto x : buses)
    {
        product *= x.first;
    }
    std::cout << product << "\n";

    for (auto x : buses)
    {
        auto remainder = (x.first - x.second % x.first) % x.first;
        auto input = product / x.first;
        auto output = quick_maths(input, (x.first - 2), x.first);
        result += remainder * input * output;
    }
    std::cout << result % product << "\n";

    return 0;
}