#include "utils.hpp"

int main(int argc, char *argv[])
{
    std::unordered_map<int, std::pair<int, int>> input;
    input[8] = {1, 0};
    input[11] = {2, 0};
    input[0] = {3, 0};
    input[19] = {4, 0};
    input[1] = {5, 0};
    input[2] = {6, 0};

    int target = 2;
    for (size_t i = 7; i < 30000000; i++)
    {
        if (input.count(target) > 0)
        {
            if ((input[target].first == (i - 1) && input[target].second == 0))
            {
                //Annoying extra case i have had to add for reasons
                input[0] = std::make_pair(i, input[0].first);
                target = 0;
            }
            else
            {
                int change_val = input[target].first - input[target].second;
                auto result = std::make_pair(i, input[change_val].first);
                input[change_val] = result;
                target = change_val;
            }
        }
        else
        {
            // target not seen before.
            input[target] = {i, 0};
            i++;
            input[0] = std::make_pair(i, input[0].first);
            target = (i - input[0].first);
        }
        if (i % 1000000 == 0)
        {
            std::cout << i << "\n";
        }

        if (i == 29999999)
        {
            std::cout << "target was: " << target << "\n";
            std::cout << input[target].first - input[target].second << "\n";
        }
    }
}