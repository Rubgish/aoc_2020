#include "utils.hpp"

// What does the func look like?
// https://en.wikipedia.org/wiki/CYK_algorithm

class Pair
{
public:
    Pair(int key_val, int val_1, int val_2)
    {
        key = key_val;
        val1 = val_1;
        val2 = val_2;
    }
    int key;
    int val1;
    int val2;
};

bool cyk_grammar(std::string input, std::list<Pair> rules)
{
    // Get length of input n
    int n = input.length();

    // Hardcoded bits - 132: 'a', 26: 'b'
    int a_val = 132;
    // int a_val = 1;
    int b_val = 26;
    // int b_val = 14;

    // Initialize array P[n, n, r] = false
    // bool P[n][n][r + 1];
    bool P[n][n][150];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            for (size_t k = 0; k < 150; k++)
            {
                P[i][j][k] = false;
            }
        }
    }

    // Do the first replacement of the input with
    for (size_t i = 0; i < n; i++)
    {
        int special = 43;
        // SPECIAL FOR TEST DATA
        // int special = 15;
        P[0][i][special] = true;
        if (input[i] == 'a')
        {
            // 'a' is rule 132.
            P[0][i][a_val] = true;
        }
        else if (input[i] == 'b')
        {
            // 'b' is rule 26
            P[0][i][b_val] = true;
        }
    }

    for (size_t l = 0; l < n; l++)
    {
        for (size_t s = 0; s < (n - l - 1); s++)
        {
            for (size_t p = 0; p <= l; p++)
            {
                for (auto &&x : rules)
                {
                    auto a = x.key;
                    auto b = x.val1;
                    auto c = x.val2;

                    if (P[p][s][b] && P[l - p][s + p + 1][c])
                    {
                        P[l + 1][s][a] = true;
                    }
                }
                if (p == 7)
                {
                    if (P[p][s][42] && P[p][s + 8][42] && P[p][s + 16][31] && P[p][s + 24][31])
                    {
                        std::cout << "updated: " << p << "\n";
                        P[p + 24][s][11] = true;
                        P[p + 8][s + 8][11] = true;
                    }
                    if (P[p][s][42] && P[p][s + 8][42] && P[p][s + 16][42] && P[p][s + 24][31] && P[p][s + 32][31] && P[p][s + 40][31])
                    {
                        std::cout << "Madness\n";
                        P[p + 40][s][11] = true;
                    }
                    if (P[p][s][42] && P[p][s + 8][42] && P[p][s + 16][42] && P[p][s + 24][42] && P[p][s + 32][31] && P[p][s + 40][31] && P[p][s + 48][31] && P[p][s + 56][31])
                    {
                        std::cout << "Wicked Sick \n";
                        P[p + 56][s][11] = true;
                    }
                }
            }
            // Row 7 only interesting row, need to run this once p==7 is hit. 8: 42 8 I think should just be handled
            // fine as is. It's the 42 11 31 I need to handle. I think. Maybe.

            // // Part A: This takes me from 376 to 384 w/ & w/o part B but w/ part C
            // int p = 7;
            // // for (int q = 0; q < 50; q++)
            // // {
            // //     if (P[p][s][42] && P[p][s + q][42] && P[p][s + (2 * q)][31] && P[p][s + (3 * q)][31])
            // //     {
            // //         std::cout << "q: " << q << " p: " << p << "\n";
            // //         P[p + (3 * q)][s][11] = true;
            // //     }
            // // }
            // // Part B: From 306 -> 376 w/o part A
            // if (P[p][s][42] && P[p + 8][s + 8][11] && P[p][s + 24][31])
            // {
            //     P[p + 24][s][11] = true;
            // }
        }
    }

    if (P[n - 1][0][0] == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char *argv[])
{
    auto input = read_input("day19_may");
    // auto input = read_input("day_19_test");

    bool rules_read = false;
    // my compiler doesn't like /s idk why
    // Full line, e.g. 61: 16 132 | 3 26
    std::regex reg_exp_a("([0-9]+):[[:space:]]([0-9]+)[[:space:]]([0-9]+)[[:space:]].*[[:space:]]([0-9]+)[[:space:]]([0-9]+)");
    // Single section, e.g. 93: 26 26
    std::regex reg_exp_b("([0-9]+):[[:space:]]([0-9]+)[[:space:]]([0-9]+)");
    // Single per gap, e.g. 8: 42 | 7
    std::regex reg_exp_c("([0-9]+):[[:space:]]([0-9]+)[[:space:]].*[[:space:]]([0-9]+)");
    // Single value, e.g. 8: 42
    std::regex reg_exp_d("([0-9]+):[[:space:]]([0-9]+)");
    std::smatch reg_out_a;
    std::smatch reg_out_b;
    std::smatch reg_out_c;
    std::smatch reg_out_d;
    std::list<Pair> rules = {};
    std::list<std::pair<int, int>> replacements = {};
    int match = 0;
    int lc = 0;

    for (auto x : input)
    {
        if (x.empty())
        {
            for (auto &&y : replacements)
            {
                for (auto &&z : rules)
                {
                    if (y.second == z.key)
                    {
                        rules.emplace_back(Pair(y.first, z.val1, z.val2));
                    }
                }
            }
            // Part C: From 187 (orig) -> 306 w/o Part A or B.
            rules.emplace_back(Pair(8, 42, 8));
            rules_read = true;

            for (auto x : rules)
            {
                std::cout << x.key << ": " << x.val1 << " " << x.val2 << "\n";
            }
            continue;
        }

        if (!rules_read)
        {
            if (std::regex_search(x, reg_out_a, reg_exp_a))
            {
                rules.emplace_back(Pair(std::stoi(reg_out_a[1]), std::stoi(reg_out_a[2]), std::stoi(reg_out_a[3])));
                rules.emplace_back(Pair(std::stoi(reg_out_a[1]), std::stoi(reg_out_a[4]), std::stoi(reg_out_a[5])));
            }
            else if (std::regex_search(x, reg_out_b, reg_exp_b))
            {
                rules.emplace_back(Pair(std::stoi(reg_out_b[1]), std::stoi(reg_out_b[2]), std::stoi(reg_out_b[3])));
            }
            else if (std::regex_search(x, reg_out_c, reg_exp_c))
            {
                replacements.emplace_back(std::make_pair(std::stoi(reg_out_c[1]), std::stoi(reg_out_c[2])));
                replacements.emplace_back(std::make_pair(std::stoi(reg_out_c[1]), std::stoi(reg_out_c[3])));
                // rules.emplace_front(Pair(std::stoi(reg_out_c[1]), std::stoi(reg_out_c[2]), std::nullopt));
                // rules.emplace_front(Pair(std::stoi(reg_out_c[1]), std::stoi(reg_out_c[3]), std::nullopt));
            }
            else if (std::regex_search(x, reg_out_d, reg_exp_d))
            {
                replacements.emplace_back(std::make_pair(std::stoi(reg_out_d[1]), std::stoi(reg_out_d[2])));
                // rules.emplace_front(Pair(std::stoi(reg_out_d[1]), std::stoi(reg_out_d[2]), std::nullopt));
            }
            else
            {
                std::cout << "MISSED REGEX FOR: " << x << "\n";
            }
        }
        else
        {
            lc++;
            if (cyk_grammar(x, rules))
            {
                match++;
                std::cout << "matched on :" << x << "\n";
                // return 0;
            }
            // return 0;
            std::cout << "matched: " << match << " of " << lc << "\n";
        }
        // read rule number
        // for each variant (ie. between each |)
        //   store that as a possible rule
        // Cheat a bit and for any rule that only has one section, duplicate that
        //   ? std::map<std::int, std::pair<int,int>> maybe?
        //   Hmm, maybe a multimap for the duplicate entries.
        //   Yeah I think that'll be fine, so long as I can still get a size of it and iterate over the whole thing
        // Nah, multimap is a huge pain.
        // Instead force everything to have two sections, but still be a map
        // std::map<int, std::pair<std::pair<int,int>, std::pair<int,int>>
        // looks a mess but I think it's okay.

        // Once we hit blank line, swap over to reading inputs.
        // run the func
    }
    std::cout << "matches: " << match << "\n";

    // for (int x = 0; x < data.size(); x++)
    // {
    //     std::cout << data[x].first.first << "," << data[x].first.second << "\n";
    //     std::cout << data[x].second.first << "," << data[x].second.second << "\n";
    // }
}