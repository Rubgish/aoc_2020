#include "utils.hpp"

int main(int argc, char *argv[])
{
    // Ignoring 0th element
    std::vector<int> input(1000001);

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
    input[8] = 10;

    for (int i = 10; i <= 1000000; i++)
    {
        input[i] = i + 1;
    }

    // And finally link the last element back to the first.
    input[1000000] = 3;

    // Set the initial value
    int val = 3;
    for (size_t i = 0; i < 10000000; i++)
    {
        // x, y, z are first, second & 3rd number respectively.
        int x = input[val];
        int y = input[x];
        int z = input[y];

        // Where to start looking next loop
        int next_val = input[z];

        int pos = val - 1;
        if (pos == 0)
        {
            pos += 1000000;
        }
        while ((pos == x) || (pos == y) || (pos == z))
        {
            pos -= 1;
            if (pos == 0)
            {
                pos += 1000000;
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

    std::cout << (int64_t)input[1] * input[input[1]] << "\n";
}