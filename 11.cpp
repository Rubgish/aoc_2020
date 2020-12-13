#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day11_input");
    char chairs[92][92] = {};

    int y = 0;
    for (auto x : input)
    {
        for (size_t i = 0; i < x.size(); i++)
        {
            chairs[y][i] = x.at(i);
        }
        y++;
    }

    char new_array[92][92] = {};
    std::memcpy(new_array, chairs, 92 * 92 * sizeof(char));
    for (int x = 0; x < 92; x++)
    {
        for (int y = 0; y < 92; y++)
        {
            new_array[x][y] = chairs[x][y];
        }
    }
    int loop_count = 0;
    while (true)
    {
        for (size_t x = 0; x < 92; x++)
        {
            for (size_t y = 0; y < 92; y++)
            {
                if (chairs[x][y] == '.')
                {
                    continue;
                }
                else
                {
                    int count = 0;
                    for (size_t i = 0; i < 3; i++)
                    {
                        for (size_t j = 0; j < 3; j++)
                        {
                            if ((x + i - 1) < 0 || (x + i - 1) > 91)
                            {
                                continue;
                            }
                            if ((y + j - 1) < 0 || (y + j - 1) > 91)
                            {
                                continue;
                            }
                            if ((i == 1) && (j == 1))
                            {
                                continue;
                            }
                            if (chairs[x + i - 1][y + j - 1] == '#')
                            {
                                count++;
                            }
                        }
                    }
                    if (chairs[x][y] == 'L' && count == 0)
                    {
                        new_array[x][y] = '#';
                    }
                    else if (chairs[x][y] == '#' && count >= 4)
                    {
                        new_array[x][y] = 'L';
                    }
                }
            }
        }
        bool same = true;
        while (same)
        {
            for (int x = 0; x < 92; x++)
            {
                for (int y = 0; y < 92; y++)
                {
                    if (chairs[x][y] != new_array[x][y])
                    {
                        same = false;
                    }
                }
            }
            break;
        }
        if (same)
        {
            std::cout << "breaking";
            break;
        }

        for (int x = 0; x < 92; x++)
        {
            for (int y = 0; y < 92; y++)
            {
                chairs[x][y] = new_array[x][y];
            }
        }

        loop_count += 1;
    }
    int occupied = 0;
    for (int x = 0; x < 92; x++)
    {
        for (int y = 0; y < 92; y++)
        {
            if (chairs[x][y] == '#')
            {
                occupied++;
            }
        }
    }
    std::cout << "loop count: " << loop_count << "\n";
    std::cout << "occupied seats: " << occupied << "\n";

    return 0;
}