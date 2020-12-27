#include "utils.hpp"

int64_t process(std::string bitmask, int64_t val)
{
    int64_t result = val;
    int64_t multiplier = 1;
    for (auto i = bitmask.crbegin(); i != bitmask.crend(); i++)
    {
        if (*i == '0')
        {
            if ((val % (multiplier * 2)) >= multiplier)
            {
                result -= multiplier;
            }
        }
        else if (*i == '1')
        {
            if ((val % (multiplier * 2)) < multiplier)
            {
                result += multiplier;
            }
        }
        multiplier *= 2;
    }
    return result;
}

int main(int argc, char *argv[])
{
    auto input = read_input("day14_input");
    std::map<int64_t, int64_t> results;
    std::string current_bitmask;
    int m_addr;
    int64_t value;

    std::regex reg_exp_a("([0-9]+)");
    std::regex reg_exp_b("([[:space:]][0-9]+)");
    for (auto line : input)
    {
        if (line.find("mask") != std::string::npos)
        {
            current_bitmask = line.substr(7);
        }
        else
        {
            std::smatch reg_out_a;
            std::smatch reg_out_b;
            std::regex_search(line, reg_out_a, reg_exp_a);
            std::regex_search(line, reg_out_b, reg_exp_b);
            m_addr = std::stoi(reg_out_a[0]);
            value = std::stoi(reg_out_b[0]);
            results[m_addr] = process(current_bitmask, value);
        }
    }

    int64_t final_value = 0;
    for (auto x : results)
    {
        final_value += x.second;
    }
    std::cout << final_value << "\n";
}
