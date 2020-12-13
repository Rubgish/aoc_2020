#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day13_input");
    std::vector<std::pair<int64_t, int64_t>> buses = {};

    std::stringstream cstring(input[1]);
    int position = 0;
    while (cstring.good())
    {
        std::string section;
        getline(cstring, section, ',');
        if (section == "x")
        {
            std::cout << "pos"
                      << "\n";
            position++;
            continue;
        }
        // std::cout << "apos: " << position << "\n";
        buses.push_back(std::make_pair(std::stoi(section), position));
        position++;
    }

    for (auto x : buses)
    {
        std::cout << x.first << " " << x.second << "\n";
    }

    uint64_t result = 0;
    uint64_t multiplier = 0;
    for (auto x : buses)
    {
        if (multiplier == 0)
        {
            std::cout << "setting multiplier to " << x.first << "\n";
            multiplier = x.first;
            continue;
        }
        else
        {
            auto a = x.first % multiplier;
            // std::cout << a << "\n";
            // std::cout << x.first << "\n";
            // std::cout << x.second << "\n";
            for (size_t i = 0; i < multiplier; i++)
            {
                if ((a * i) % multiplier == (result + x.second))
                {
                    // std::cout << i << "\n";
                    result = (a * i) - x.second;
                    multiplier *= x.first;
                    std::cout << "multi: " << multiplier << "\n";
                    break;
                }
            }
        }
    }
    std::cout << result << "\n";

    return 0;
}