#include "utils.hpp"

int main(int argc, char *argv[])
{
    std::map<int, int> input;
    input[0] = 8;
    input[1] = 11;
    input[2] = 0;
    input[3] = 19;
    input[4] = 1;
    input[5] = 2;

    while (input.size() < 2020)
    {
        auto target = input[input.size() - 1];
        for (auto iter = input.rbegin(); iter != input.rend(); iter++)
        {
            if (iter == input.rbegin())
            {
                continue;
            }

            else if (iter->second == target)
            {
                input[input.size()] = (input.size() - iter->first + -1);
                break;
            }
            else if (iter->first == 0)
            {
                input[input.size()] = 0;
                break;
            }
        }
    }
    std::cout << input[2019] << "\n";
}