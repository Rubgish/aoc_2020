#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day12_input");

    std::pair<int64_t, int64_t> dir = {1, 0};
    std::pair<int64_t, int64_t> location = {0, 0};
    std::pair<int64_t, int64_t> waypoint = {10, 1};

    for (auto x : input)
    {
        auto command = x.substr(0, 1);
        auto value = std::stoi(x.substr(1));

        if (command == "N")
        {
            waypoint.second += value;
        }
        else if (command == "S")
        {
            waypoint.second -= value;
        }
        else if (command == "W")
        {
            waypoint.first -= value;
        }
        else if (command == "E")
        {
            waypoint.first += value;
        }
        else if (command == "L")
        {
            auto turns = (value / 90);
            for (size_t i = 0; i < turns; i++)
            {
                auto new_wp = std::make_pair(-waypoint.second, waypoint.first);
                waypoint = new_wp;
            }
        }
        else if (command == "R")
        {
            auto turns = (value / 90);
            for (size_t i = 0; i < turns; i++)
            {
                auto new_wp = std::make_pair(waypoint.second, -waypoint.first);
                waypoint = new_wp;
            }
        }
        else if (command == "F")
        {
            location.first += (waypoint.first * value);
            location.second += (waypoint.second * value);
        }
        std::cout << location.first << "   " << location.second << "\n";
    }

    std::cout << "x: " << location.first << "\n";
    std::cout << "y: " << location.second << "\n";
    std::cout << "sum: " << (abs(location.first) + abs(location.second)) << "\n";
    return 0;
}