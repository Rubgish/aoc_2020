#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day7_input");

    std::string bc = " bags contain";
    std::map<std::string, std::vector<std::string>> parse_map = {};
    for (auto x : input)
    {
        // Example key: "light plum"
        auto key = x.substr(0, x.find(" bags"));
        // std::cout << key << "\n";
        // Example value_str " 2 bright indigo bags, 3 plaid cyan bags, 1 light gold bag."
        auto value_str = x.substr(key.length() + bc.length());
        // std::cout << value_str << "\n";
        // Example cs_val_str "2 bright indigo bags, 3 plaid cyan bags, 1 light gold bag"
        auto cs_val_str = value_str.substr(1, value_str.length() - 2);
        // std::cout << cs_val_str << "\n";
        size_t pos = 0;
        while ((pos = cs_val_str.find(",")) != std::string::npos)
        {
            // avoid first two digits, they are num + " ".
            auto val = cs_val_str.substr(2, cs_val_str.find(" bag") - 2);
            parse_map[key].push_back(val);
            cs_val_str.erase(0, pos + 2);
        }
        // Here's the gross add the end value to the loop thing again.
        parse_map[key].push_back(cs_val_str.substr(2, cs_val_str.find(" bag") - 2));
    }

    int matches = 0;
    std::string initial_bag = "shiny gold";
    std::map<std::string, int> valid_bags = {};
    valid_bags[initial_bag]++;
    while (true)
    {
        for (auto x : parse_map)
        {
            for (auto y : valid_bags)
            {
                if (std::find(x.second.begin(), x.second.end(), y.first) != x.second.end())
                {
                    valid_bags[x.first]++;
                }
            }
        }
        if (matches == valid_bags.size())
        {
            break;
        }
        else
        {
            matches = valid_bags.size();
        }
    }
    // Remove the gold bag itself!!
    std::cout << (matches - 1) << "\n";
    return 0;
}