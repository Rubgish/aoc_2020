#include "utils.hpp"

struct Edge
{
    std::string N;
    std::string E;
    std::string S;
    std::string W;
};

class Tile
{
public:
    Tile(int input)
    {
        num = input;
    }
    int64_t num;
    Edge e;
    bool matched = false;

    void rotate_r()
    {
        auto tmp_lines = lines;
        for (size_t i = 0; i < lines.size(); i++)
        {
            for (size_t j = 0; j < lines.size(); j++)
            {
                lines[i][j] = tmp_lines[tmp_lines.size() - j - 1][i];
            }
        }
        populate_edges();
    }

    void flip_ns()
    {
        auto tmp_lines = lines;
        for (size_t i = 0; i < tmp_lines.size(); i++)
        {
            lines[i] = tmp_lines[lines.size() - i - 1];
        }
        populate_edges();
    }

    void flip_ew()
    {
        for (size_t i = 0; i < lines.size(); i++)
        {
            std::reverse(lines[i].begin(), lines[i].end());
        }
        populate_edges();
    }

    bool edge_match(std::string edge)
    {
        if ((edge == e.E) || (edge == e.N) || (edge == e.W) || (edge == e.S))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void add_line(std::string line)
    {
        lines.push_back(line);
    }

    void append_line(int line_num, std::string line)
    {
        lines[line_num] += line;
    }

    void populate_edges()
    {
        auto north = lines.front();
        auto south = lines.back();
        std::string east;
        std::string west;
        for (size_t i = 0; i < lines.size(); i++)
        {
            east.push_back(lines[i][9]);
            west.push_back(lines[i][0]);
        }
        e = Edge{north, east, south, west};
    }

    void cut_edges()
    {
        for (size_t i = 1; i < (lines.size() - 1); i++)
        {
            auto new_line = lines[i].substr(1, lines[i].size() - 2);
            cut_lines.push_back(new_line);
        }
    }

    std::vector<std::string> lines;
    std::vector<std::string> cut_lines;
};

int main(int argc, char *argv[])
{

    auto input = read_input("day20_input");

    std::map<int, Tile> tiles;

    int cur_tile = 0;
    for (auto x : input)
    {
        if (x.find("Tile") != std::string::npos)
        {
            cur_tile = std::stoi(x.substr(5, 4));
            tiles.insert(std::make_pair(cur_tile, Tile(std::stoi(x.substr(5, 4)))));
        }
        else if (!x.empty())
        {
            tiles.at(cur_tile).add_line(x);
        }
        else
        {
            tiles.at(cur_tile).populate_edges();
        }
    }

    bool tile_found = false;
    int original_tile;

    // Count how many matches each tile gets so we can find corners.
    for (auto &i : tiles)
    {
        auto x = i.second;
        x.matched = true;
        int match_count = 0;
        for (auto &j : tiles)
        {
            auto y = j.second;
            if (x.num != y.num)
            {
                if (y.edge_match(x.e.N) || y.edge_match(x.e.E) || y.edge_match(x.e.S) || y.edge_match(x.e.W))
                {
                    match_count++;
                    y.matched = true;
                }
                if (!y.matched)
                {
                    y.flip_ew();
                    if (y.edge_match(x.e.N) || y.edge_match(x.e.E) || y.edge_match(x.e.S) || y.edge_match(x.e.W))
                    {
                        match_count++;
                        y.matched = true;
                    }
                }
                if (!y.matched)
                {
                    y.flip_ns();
                    if (y.edge_match(x.e.N) || y.edge_match(x.e.E) || y.edge_match(x.e.S) || y.edge_match(x.e.W))
                    {
                        match_count++;
                        y.matched = true;
                    }
                }
                if (!y.matched)
                {
                    y.flip_ew();
                    if (y.edge_match(x.e.N) || y.edge_match(x.e.E) || y.edge_match(x.e.S) || y.edge_match(x.e.W))
                    {
                        match_count++;
                        y.matched = true;
                    }
                }
                if (!y.matched)
                {
                    y.rotate_r();
                    if (y.edge_match(x.e.N) || y.edge_match(x.e.E) || y.edge_match(x.e.S) || y.edge_match(x.e.W))
                    {
                        match_count++;
                        y.matched = true;
                    }
                }
            }
            y.matched = false;
        }
        if (match_count == 2 && tile_found != true)
        {
            original_tile = x.num;
            tile_found = true;
        }
    }

    // At this stage, I could have completed part A. However I was an idiot and didn't spot that
    // I'd worked out the corners so was done. Instead I went ahead and (literally starting from a corner)
    // created the put-together puzzle, then looked at the corners. This comment is a testament to the
    // folly of someone who was too busy writing code to think about what they were doing :)

    // Place a corner tile at 0,0.
    // Keep matching E->W til we don't find a match (i.e. end of the first row.)
    // Then move up a row and start again, until there's no further tiles (opposite corner to
    // where we started).
    std::map<std::pair<int, int>, Tile> pic;
    pic.emplace(std::make_pair(std::make_pair(0, 0), tiles.at(original_tile)));
    auto it = tiles.find(original_tile);
    tiles.erase(it);
    int pic_x = 0;
    int pic_y = 0;
    tile_found = false;
    while (true)
    {
        tile_found = false;
        auto target = pic.at(std::make_pair(pic_x, pic_y)).e.E;
        bool target_met = false;
        for (auto &i : tiles)
        {
            auto x = i.second;
            // Do all the permutation stuff
            if (x.edge_match(target))
            {
                pic_x++;
                if (x.e.W != target)
                {
                    x.rotate_r();
                }
                if (x.e.W != target)
                {
                    x.flip_ew();
                }
                if (x.e.W != target)
                {
                    x.rotate_r();
                }
                pic.emplace(std::make_pair(std::make_pair(pic_x, pic_y), x));
                auto it = tiles.find(x.num);
                tiles.erase(it);
                tile_found = true;
                break;
            }
            x.flip_ew();
            if (x.edge_match(target))
            {
                pic_x++;
                if (x.e.W != target)
                {
                    x.rotate_r();
                }
                if (x.e.W != target)
                {
                    x.flip_ew();
                }
                pic.emplace(std::make_pair(std::make_pair(pic_x, pic_y), x));
                auto it = tiles.find(x.num);
                tiles.erase(it);
                tile_found = true;
                break;
            }
            x.flip_ns();
            if (x.edge_match(target))
            {
                pic_x++;
                if (x.e.W != target)
                {
                    x.flip_ew();
                }

                pic.emplace(std::make_pair(std::make_pair(pic_x, pic_y), x));
                auto it = tiles.find(x.num);
                tiles.erase(it);
                tile_found = true;
                break;
            }
        }

        if (!tile_found)
        {
            pic_x = 0;
            target = pic.at(std::make_pair(pic_x, pic_y)).e.N;
            pic_y++;
            for (auto &i : tiles)
            {
                auto x = i.second;
                if (x.edge_match(target))
                {
                    if (x.e.S != target)
                    {
                        x.flip_ns();
                    }
                    if (x.e.S != target)
                    {
                        x.rotate_r();
                    }
                    if (x.e.S != target)
                    {
                        x.flip_ns();
                    }
                    pic.emplace(std::make_pair(std::make_pair(pic_x, pic_y), x));
                    auto it = tiles.find(x.num);
                    tiles.erase(it);
                    tile_found = true;
                    break;
                }
                x.flip_ew();
                if (x.edge_match(target))
                {
                    if (x.e.S != target)
                    {
                        x.flip_ns();
                    }
                    if (x.e.S != target)
                    {
                        x.rotate_r();
                    }
                    if (x.e.S != target)
                    {
                        x.flip_ns();
                    }
                    pic.emplace(std::make_pair(std::make_pair(pic_x, pic_y), x));
                    auto it = tiles.find(x.num);
                    tiles.erase(it);
                    tile_found = true;
                    break;
                }
                x.flip_ns();
                if (x.edge_match(target))
                {
                    if (x.e.S != target)
                    {
                        x.flip_ns();
                    }
                    if (x.e.S != target)
                    {
                        x.rotate_r();
                    }
                    if (x.e.S != target)
                    {
                        x.flip_ns();
                    }
                    pic.emplace(std::make_pair(std::make_pair(pic_x, pic_y), x));
                    auto it = tiles.find(x.num);
                    tiles.erase(it);
                    tile_found = true;
                    break;
                }
            }
        }

        if (!tile_found)
        {
            std::cout << "Part A:" << pic.at(std::make_pair(0, 0)).num * pic.at(std::make_pair(11, 0)).num * pic.at(std::make_pair(0, 11)).num * pic.at(std::make_pair(11, 11)).num << "\n";
            break;
        }
    }

    // The connections here are N->S and E->W. It's much easier to print out if they are S->N and E->W.
    // A north-south flip achieves this, so do that.
    for (auto &x : pic)
    {
        x.second.flip_ns();
        x.second.cut_edges();
    }

    auto picture = Tile(0);
    int cut_lines_size = pic.at(std::make_pair(0, 0)).cut_lines.size();
    // Assumes the picture is square.
    int size = std::sqrt(pic.size());
    // Make each set of 8 lines at a time, then append them to a 'mega tile'. This gives us
    // rotation & flipping if we need it.
    for (size_t k = 0; k < size; k++)
    {
        std::vector<std::string> temp_lines(cut_lines_size);
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < cut_lines_size; j++)
            {
                temp_lines[j] += pic.at(std::make_pair(i, k)).cut_lines[j];
            }
        }

        for (auto x : temp_lines)
        {
            picture.add_line(x);
        }
    }

    // Trial and error rotations/flips to achieve this. There's a small number of options here
    // and at this point, I'm pretty confident I am way faster doing them by hand than
    // trying to write code, given how badly the whole code thing has worked out for me
    // so far this problem :D
    picture.rotate_r();
    picture.rotate_r();
    picture.flip_ns();

    // If you want to view the result, uncomment the below lines.
    // for (int i = 0; i < picture.lines.size(); i++)
    // {
    //     std::cout << picture.lines[i];
    //     std::cout << "\n";
    // }

    // Loop through the picture, find each '#' and do some checks to see if it's a sea creature.
    // Assume no overlaps.
    int hash_count = 0;
    int monster_count = 0;
    for (int x = 0; x < picture.lines[0].size(); x++)
    {
        auto l = picture.lines[x];
        for (int y = 0; y < l.size(); y++)
        {
            if (l[y] == '#')
            {
                hash_count++;
                if ((x == 0) || (x == l.size() - 1))
                {
                    continue;
                }

                if ((y + 19) > l.size())
                {
                    continue;
                }
                if ((l[y + 5] != '#') || (l[y + 6] != '#') || (l[y + 11] != '#') || (l[y + 12] != '#') || (l[y + 17] != '#') || (l[y + 18] != '#') || (l[y + 19] != '#'))
                {
                    continue;
                }
                auto lu = picture.lines[x - 1];
                if (lu[y + 18] != '#')
                {
                    continue;
                }
                auto lb = picture.lines[x + 1];
                if ((lb[y + 1] != '#') || (lb[y + 4] != '#') || (lb[y + 7] != '#') || (lb[y + 10] != '#') || (lb[y + 13] != '#') || (lb[y + 16] != '#'))
                {
                    continue;
                }

                monster_count++;
            }
        }
    }
    std::cout << "hash count: " << hash_count << "\n";
    std::cout << "monster count: " << monster_count << "\n";
    std::cout << "final result: " << hash_count - (monster_count * 15) << "\n";
}