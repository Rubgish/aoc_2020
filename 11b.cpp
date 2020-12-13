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
                    // north
                    for (size_t i = 1; i < 92; i++)
                    {
                        if (i > x)
                        {
                            break;
                        }
                        else if (chairs[x - i][y] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x - i][y] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    // south
                    for (size_t i = 1; i < 92; i++)
                    {
                        if ((x + i) > 91)
                        {
                            break;
                        }
                        else if (chairs[x + i][y] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x + i][y] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    // east
                    for (size_t i = 1; i < 92; i++)
                    {
                        if ((y + i) > 91)
                        {
                            break;
                        }
                        else if (chairs[x][y + i] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x][y + i] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    // west
                    for (size_t i = 1; i < 92; i++)
                    {
                        if (i > y)
                        {
                            break;
                        }
                        else if (chairs[x][y - i] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x][y - i] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    // north-east
                    for (size_t i = 1; i < 92; i++)
                    {
                        if (((y + i) > 91) || (i > x))
                        {
                            break;
                        }
                        else if (chairs[x - i][y + i] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x - i][y + i] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    // north-west
                    for (size_t i = 1; i < 92; i++)
                    {
                        if ((i > y) || (i > x))
                        {
                            break;
                        }
                        else if (chairs[x - i][y - i] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x - i][y - i] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    // south-east
                    for (size_t i = 1; i < 92; i++)
                    {
                        if (((y + i) > 91) || ((x + i) > 91))
                        {
                            break;
                        }
                        else if (chairs[x + i][y + i] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x + i][y + i] == '#')
                        {
                            count++;
                            break;
                        }
                    }

                    // south-west
                    for (size_t i = 1; i < 92; i++)
                    {
                        if ((i > y) || ((x + i) > 91))
                        {
                            break;
                        }
                        else if (chairs[x + i][y - i] == 'L')
                        {
                            break;
                        }
                        else if (chairs[x + i][y - i] == '#')
                        {
                            count++;
                            break;
                        }
                    }
                    if (chairs[x][y] == 'L' && count == 0)
                    {
                        new_array[x][y] = '#';
                    }
                    else if (chairs[x][y] == '#' && count >= 5)
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