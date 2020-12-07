#include "utils.hpp"

int bag_count(std::string name, std::map<std::string, std::vector<std::pair<std::string, int>>> &p)
{
    std::vector<std::pair<std::string, int>> empty_vec = {};
    if (p[name] == empty_vec)
    {
        return 1;
    }
    else
    {
        int b_c = 0;
        for (auto x : p[name])
        {
            b_c += (bag_count(x.first, p) * x.second);
        }
        b_c += 1;
        return b_c;
    }
};

int main(int argc, char *argv[])
{
    auto input = read_input("day7_input");

    std::string bc = " bags contain";
    std::map<std::string, std::vector<std::pair<std::string, int>>> parse_map = {};
    for (auto x : input)
    {
        // Example key: "light plum"
        auto key = x.substr(0, x.find(" bags"));
        if (x.find("no other bags") != std::string::npos)
        {
            parse_map[key].push_back({});
            continue;
        }
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
            auto count = std::atoi(cs_val_str.substr(0, 1).c_str());
            parse_map[key].push_back({val, count});
            cs_val_str.erase(0, pos + 2);
        }
        // Here's the gross add the end value to the loop thing again.
        parse_map[key].push_back({cs_val_str.substr(2, cs_val_str.find(" bag") - 2), std::atoi(cs_val_str.substr(0, 1).c_str())});
    }

    auto final_val = bag_count("shiny gold", parse_map);

    std::cout << final_val - 1 << "\n";
    return 0;
}