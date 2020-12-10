#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_ints("day10_input");
    std::map<std::string, int> results{};

    int target = 0;
    while (true)
    {
        target += 1;
        if (std::find(input.begin(), input.end(), target) != input.end())
        {
            results["1"]++;
        }
        else if (std::find(input.begin(), input.end(), target + 2) != input.end())
        {
            target += 2;
            results["3"]++;
        }
        else
        {
            break;
        }
    }

    std::cout << (results["1"] * (results["3"] + 1)) << "\n";

    // part B
    input.push_back(0);
    std::sort(input.begin(), input.end());

    std::map<std::string, int> p2_results = {};
    int cur_pos = 0;
    int new_pos = 0;
    int ones = 0;
    int multiplier = 1;
    int64_t final_multi = 1;
    while (true)
    {
        if (cur_pos == (input.size() - 1))
        {
            while (ones > 0)
            {
                ones--;
                multiplier += ones;
            }
            if (multiplier != 0)
            {
                final_multi = final_multi * multiplier;
            }
            break;
        }
        if (input[cur_pos + 1] == (input[cur_pos] + 3))
        {
            cur_pos += 1;
            while (ones > 0)
            {
                ones--;
                multiplier += ones;
            }
            if (multiplier != 0)
            {
                final_multi = final_multi * multiplier;
            }
            multiplier = 1;
            continue;
        }
        else if (input[cur_pos + 1] == (input[cur_pos] + 1))
        {
            ones++;
            cur_pos++;
        }
    }

    std::cout << final_multi << "\n";

    return 0;
}