#include "utils.hpp"

int check(const std::pair<int, int> &x, std::map<std::pair<int, int>, bool> &tiles, std::map<std::pair<int, int>, bool> &new_tiles)
{
    std::vector<std::pair<int, int>> perms = {};
    perms.push_back(std::make_pair(2, 0));
    perms.push_back(std::make_pair(1, -1));
    perms.push_back(std::make_pair(-1, -1));
    perms.push_back(std::make_pair(-2, 0));
    perms.push_back(std::make_pair(-1, 1));
    perms.push_back(std::make_pair(1, 1));

    int match_count = 0;

    for (auto y : perms)
    {
        auto coord = std::make_pair(x.first + y.first, x.second + y.second);
        tiles.emplace(coord, false);
        if (tiles[coord] == true)
        {
            match_count++;
        }
    }

    return match_count;
}

void check_self(const std::pair<int, int> &x, std::map<std::pair<int, int>, bool> &tiles, std::map<std::pair<int, int>, bool> &new_tiles)
{
    auto matches = check(x, tiles, new_tiles);
    if ((matches == 0) || (matches > 2))
    {
        new_tiles[x] = false;
    }
}

void check_others(const std::pair<int, int> &x, std::map<std::pair<int, int>, bool> &tiles, std::map<std::pair<int, int>, bool> &new_tiles)
{
    std::vector<std::pair<int, int>> perms = {};
    perms.push_back(std::make_pair(2, 0));
    perms.push_back(std::make_pair(1, -1));
    perms.push_back(std::make_pair(-1, -1));
    perms.push_back(std::make_pair(-2, 0));
    perms.push_back(std::make_pair(-1, 1));
    perms.push_back(std::make_pair(1, 1));

    for (auto y : perms)
    {
        auto coord = std::make_pair(x.first + y.first, x.second + y.second);
        auto matches = check(coord, tiles, new_tiles);
        if (matches == 2)
        {
            new_tiles.emplace(coord, false);
            if (!new_tiles[coord])
            {
                new_tiles[coord] = !new_tiles[coord];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    auto input = read_input("day24_input");
    std::map<std::pair<int, int>, bool> tiles;
    std::vector<std::string> command_line;
    std::vector<std::vector<std::string>> command_list;

    for (auto x : input)
    {
        int i = 0;
        while (i < x.length())
        {
            if (x.at(i) == 'n' || x.at(i) == 's')
            {
                command_line.push_back(x.substr(i, 2));
                i += 2;
            }
            else
            {
                command_line.push_back(x.substr(i, 1));
                i++;
            }
        }
        command_list.push_back(command_line);
        command_line = {};
    }

    for (auto command : command_list)
    {
        std::pair<int, int> tile_pos = {};
        int x = 0;
        int y = 0;
        for (auto dir : command)
        {
            if (dir == "e")
            {
                x += 2;
            }
            else if (dir == "se")
            {
                x += 1;
                y -= 1;
            }
            else if (dir == "sw")
            {
                x -= 1;
                y -= 1;
            }
            else if (dir == "w")
            {
                x -= 2;
            }
            else if (dir == "nw")
            {
                x -= 1;
                y += 1;
            }
            else if (dir == "ne")
            {
                x += 1;
                y += 1;
            }
            else
            {
                std::cout << "we errorin brah"
                          << "\n";
            }
        }
        auto coord = std::make_pair(x, y);
        tiles.emplace(coord, false);
        tiles[coord] = !tiles[coord];
    }

    int flipped_count = 0;
    for (auto x : tiles)
    {
        if (x.second)
        {
            flipped_count++;
        }
    }
    std::cout << "day 0:" << flipped_count << "\n";

    for (size_t i = 0; i < 100; i++)
    {
        flipped_count = 0;
        auto new_tiles = tiles;
        for (auto x : tiles)
        {
            if (x.second)
            {
                check_self(x.first, tiles, new_tiles);
                check_others(x.first, tiles, new_tiles);
            }
        }
        tiles = new_tiles;
        for (auto x : tiles)
        {
            if (x.second)
            {
                flipped_count++;
            }
        }
    }
    std::cout << "day 100:" << flipped_count << "\n";
}