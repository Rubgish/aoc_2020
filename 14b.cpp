#include "utils.hpp"

int64_t get_int_from_str(std::string str)
{
    int64_t result = 0;
    int64_t multiplier = 1;
    for (auto i = str.crbegin(); i != str.crend(); i++)
    {
        result += (multiplier * ((int)*i - '0'));
        multiplier *= 2;
    }
    return result;
}

std::string get_str_from_int(int64_t num)
{
    std::string str = "000000000000000000000000000000000000";
    int64_t multiplier = 1;
    for (auto i = str.rbegin(); i != str.rend(); i++)
    {
        if ((num % (multiplier * 2)) >= multiplier)
        {
            *i = '1';
        }
        multiplier *= 2;
    }
    return str;
}

/// Go through the string. For each X, do two loops - one for 0, one for 1. If we hit no X's, we're at the end of recursion so store our current string.
void recurse_str(std::string input, std::map<int64_t, int64_t> *store, int64_t &value, int64_t &rc)
{
    rc += 1;
    bool final = true;
    for (auto i = input.begin(); i != input.end(); i++)
    {
        if (*i == 'X')
        {
            final = false;
            std::string orig_str = input;
            *i = '0';
            recurse_str(input, store, value, rc);
            input = orig_str;
            *i = '1';
            recurse_str(input, store, value, rc);
            break;
        }
    }

    if (final)
    {
        store->insert_or_assign(get_int_from_str(input), value);
    }
}

int main(int argc, char *argv[])
{
    auto input = read_input("day14_input");
    std::map<int64_t, int64_t> results;
    std::string current_bitmask;
    std::string m_addr;
    int64_t value;

    std::regex reg_exp_a("([0-9]+)");
    std::regex reg_exp_b("([[:space:]][0-9]+)");
    int64_t rc = 0;
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
            m_addr = get_str_from_int(std::stoi(reg_out_a[0]));
            value = std::stoi(reg_out_b[0]);
            std::string result_str = "000000000000000000000000000000000000";
            for (int i = 0; i < current_bitmask.length(); i++)
            {
                if (current_bitmask[i] == 'X')
                {
                    result_str[i] = 'X';
                }
                else if (current_bitmask[i] == '1' || m_addr[i] == '1')
                {
                    result_str[i] = '1';
                }
            }

            recurse_str(result_str, &results, value, rc);
        }
    }

    int64_t final_value = 0;
    for (auto x : results)
    {
        final_value += x.second;
    }
    std::cout << rc << "\n";
    std::cout << final_value << "\n";
}
