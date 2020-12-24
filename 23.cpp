#include "utils.hpp"

int main(int argc, char *argv[])
{
    // Ignoring 0th element
    std::vector<int> input(10);

    // should get ingored
    input[0] = 0;

    // Original values
    input[3] = 2;
    input[2] = 6;
    input[6] = 5;
    input[5] = 1;
    input[1] = 9;
    input[9] = 4;
    input[4] = 7;
    input[7] = 8;
    input[8] = 3;

    // Set the initial value
    int val = 3;
    for (size_t i = 0; i < 100; i++)
    {
        int x = input[val];
        int y = input[x];
        int z = input[y];
        int next_val = input[z];

        int pos = val - 1;
        if (pos == 0)
        {
            pos += 9;
        }
        while ((pos == x) || (pos == y) || (pos == z))
        {
            pos -= 1;
            if (pos == 0)
            {
                pos += 9;
            }
        }

        // Make val point to its new number
        input[val] = next_val;

        // Make the 3rd number point to what pos points to
        input[z] = input[pos];

        // Make pos point to the first number
        input[pos] = x;

        // update val
        val = next_val;
    }

    int x = 1;
    for (size_t i = 0; i < input.size() - 2; i++)
    {
        std::cout << input[x];
        x = input[x];
    }
}