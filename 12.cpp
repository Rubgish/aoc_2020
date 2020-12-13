#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day12_input");

    std::pair<int64_t, int64_t> dir = {1, 0};
    std::pair<int64_t, int64_t> location = {0, 0};

    for (auto x : input)
    {
        auto command = x.substr(0, 1);
        auto value = std::stoi(x.substr(1));

        if (command == "N")
        {
            location.second += value;
        }
        else if (command == "S")
        {
            location.second -= value;
        }
        else if (command == "W")
        {
            location.first -= value;
        }
        else if (command == "E")
        {
            location.first += value;
        }
        else if (command == "L")
        {
            auto turns = (value / 90);
            for (size_t i = 0; i < turns; i++)
            {
                if (dir.first == 1)
                {
                    dir.second = 1;
                    dir.first = 0;
                }
                else if (dir.second == 1)
                {
                    dir.second = 0;
                    dir.first = -1;
                }
                else if (dir.first == -1)
                {
                    dir.second = -1;
                    dir.first = 0;
                }
                else if (dir.second == -1)
                {
                    dir.second = 0;
                    dir.first = 1;
                }
            }
        }
        else if (command == "R")
        {
            auto turns = (value / 90);
            for (size_t i = 0; i < turns; i++)
            {
                if (dir.first == 1)
                {
                    dir.second = -1;
                    dir.first = 0;
                }
                else if (dir.second == -1)
                {
                    dir.second = 0;
                    dir.first = -1;
                }
                else if (dir.first == -1)
                {
                    dir.second = 1;
                    dir.first = 0;
                }
                else if (dir.second == 1)
                {
                    dir.second = 0;
                    dir.first = 1;
                }
            }
        }
        else if (command == "F")
        {
            location.first += (dir.first * value);
            location.second += (dir.second * value);
        }
    }

    std::cout << "x: " << location.first << "\n";
    std::cout << "y: " << location.second << "\n";
    std::cout << "sum: " << (abs(location.first) + abs(location.second)) << "\n";
    return 0;
}