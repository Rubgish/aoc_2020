#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day13_input");
    std::vector<int> buses = {};

    int wait_time = std::stoi(input[0]);
    std::stringstream cstring(input[1]);
    while (cstring.good())
    {
        std::string section;
        getline(cstring, section, ',');
        if (section == "x")
        {
            continue;
        }
        buses.push_back(std::stoi(section));
    }

    int best_bus;
    int best_time = wait_time;

    for (auto x : buses)
    {
        auto time = x - (wait_time % x);
        if (time < best_time)
        {
            best_time = time;
            best_bus = x;
        }
    }

    std::cout << "Best time: " << best_time << "\n";
    std::cout << "Best bus: " << best_bus << "\n";
    std::cout << "Final value: " << (best_time * best_bus) << "\n";

    return 0;
}