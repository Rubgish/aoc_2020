#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_ints("day9_input");
    u_int64_t target = 0;

    std::deque<int64_t> nums = {};

    for (auto x : input)
    {
        if (nums.size() < 25)
        {
            nums.push_back(x);
            continue;
        }

        bool found = false;
        for (auto y : nums)
        {
            if (std::find(nums.begin(), nums.end(), (x - y)) != nums.end())
            {
                found = true;
                nums.push_back(x);
                nums.pop_front();
                break;
            }
        }
        if (!found)
        {
            std::cout << x << "\n";
            target = x;
            break;
        }
    }

    std::vector<int64_t> used_nums = {};
    for (size_t x = 0; x < input.size(); x++)
    {
        int64_t cur_val = 0;
        while (cur_val <= target)
        {
            for (size_t y = x; y < input.size(); y++)
            {
                cur_val += input[y];
                used_nums.push_back(input[y]);
                if (cur_val == target)
                {
                    goto result;
                }
            }
        }
        used_nums = {};
    }

result:
    std::sort(used_nums.begin(), used_nums.end());
    std::cout << used_nums[0] + used_nums[used_nums.size() - 1] << "\n";

    return 0;
}