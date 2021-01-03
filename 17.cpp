#include "utils.hpp"

int perturbe(int (*array)[23][15][15], int x, int y, int z, int w)
{
    int matches = 0;

    for (int ii = -1; ii < 2; ii++)
    {
        if (x + ii < 0)
        {
            continue;
        }
        for (int jj = -1; jj < 2; jj++)
        {
            if (y + jj < 0)
            {
                continue;
            }
            for (int kk = -1; kk < 2; kk++)
            {
                if (z + kk < 0)
                {
                    continue;
                }
                for (int ww = -1; ww < 2; ww++)
                {
                    if (w + ww < 0)
                    {
                        continue;
                    }
                    if (array[x + ii][y + jj][z + kk][w + ww] == 1)
                    {
                        if (ii != 0 || jj != 0 || kk != 0 || ww != 0)
                        {
                            matches++;
                        }
                    }
                }
            }
        }
    }

    return matches;
}

// I've been drinking wine and it's late I am sorry in advance for this
int main(int argc, char *argv[])
{
    auto input = read_input("day17_input");
    int count = 23;
    int z_count = 15;
    // x - y - z start in the x-y plane
    int a[23][23][15][15] = {0};

    int x = 7;
    int y = 7;
    int z = 7;
    for (auto i : input)
    {
        for (auto j : i)
        {
            if (j == '#')
            {
                a[x][y][z][z] = 1;
            }
            x++;
        }
        y++;
        x = 7;
    }

    for (int loops = 0; loops < 6; loops++)
    {
        int a_new[23][23][15][15] = {0};
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                for (int k = 0; k < z_count; k++)
                {
                    for (int w = 0; w < z_count; w++)
                    {
                        int match_count = perturbe(a, i, j, k, w);
                        if ((a[i][j][k][w] == 1) && (match_count == 2 || match_count == 3))
                        {
                            a_new[i][j][k][w] = 1;
                        }
                        else if (match_count == 3)
                        {
                            a_new[i][j][k][w] = 1;
                        }
                    }
                }
            }
        }
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                for (int k = 0; k < z_count; k++)
                {
                    for (int w = 0; w < z_count; w++)
                    {
                        a[i][j][k][w] = a_new[i][j][k][w];
                    }
                }
            }
        }
    }

    int final_count = 0;
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            for (int k = 0; k < z_count; k++)
            {
                for (int w = 0; w < z_count; w++)
                {
                    if (a[i][j][k][w] == 1)
                    {
                        final_count++;
                    }
                }
            }
        }
    }
    std::cout << final_count << "\n";
}