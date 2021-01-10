#include "utils.hpp"

// What does the func look like?
// https://en.wikipedia.org/wiki/CYK_algorithm

// hardcode 8: 42, 43: 132 | 26, 26: "b", 132: "a" ?
bool cyk_grammar(std::string input, std::map<int, std::pair<std::pair<int, int>, std::pair<int, int>>> rules)
{
    // Get length of input n
    int n = input.length();
    // Get length of rules r
    int r = rules.size() + 2;

    // Hardcoded bits
    int a_val = 132;
    // int a_val = 1;
    int b_val = 26;
    // int b_val = 3;
    int spec_rule_1 = 8;
    int spec_result_1 = 42;
    int spec_rule_2 = 43;
    int spec_result_2_a = 132;
    int spec_result_2_b = 26;

    // Initialize array P[n, n, r] = false
    bool P[n][n][r];
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            for (size_t k = 0; k < r; k++)
            {
                P[i][j][k] = false;
            }
        }
    }

    // Do the first replacement of the input with
    for (size_t i = 0; i < n; i++)
    {
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
        // maybe skip the + 1?
        for (size_t s = 0; s < (n - l - 1); s++)
        {
            for (size_t p = 0; p <= l; p++)
            {
                for (size_t a = 0; a < r; a++)
                {
                    // if (P[p][s][a] == true)
                    // {
                    //     std::cout << "[" << p << "]"
                    //               << "[" << s << "]"
                    //               << "[" << a << "]"
                    //               << "\n";
                    // }
                    // Skip rules that were -> a and -> b
                    // if ((a == a_val) || (a == b_val)) // || (a == spec_rule_1) || (a == spec_rule_2))
                    // {
                    //     continue;
                    // }
                    // rule 8 is just '8 : 42' which we can't represent in the grammar as A->BC
                    // if (a == spec_rule_1)
                    // {
                    //     auto b = spec_result_1;
                    //     if (P[p][s][b])
                    //     {
                    //         P[l + 1][s][a] = true;
                    //     }
                    //     continue;
                    // }
                    // // // rule 43 is '43: 132 | 26' which again, can't represent cleanly, so do it manual.
                    // if (a == spec_rule_2)
                    // {
                    //     auto b = spec_result_2_a;
                    //     if (P[p][s][b])
                    //     {
                    //         P[l + 1][s][a] = true;
                    //     }
                    //     b = spec_result_2_b;
                    //     if (P[p][s][b])
                    //     {
                    //         P[l + 1][s][a] = true;
                    //     }
                    //     continue;
                    // }

                    // We've forced each rule to have two options (in the case of just A->BC originally,
                    // we now have a-> BC | BC which is functionally the same, just extra work).
                    auto b = rules[a].first.first;
                    auto c = rules[a].first.second;
                    if (P[p][s][b] && P[l - p][s + p + 1][c])
                    {
                        P[l + 1][s][a] = true;
                        if (a == spec_result_1)
                        {
                            P[l + 1][s][spec_rule_1] = true;
                        }
                        if ((a == spec_result_2_a) || (a == spec_result_2_b))
                        {
                            P[l + 1][s][spec_rule_2] = true;
                        }
                    }
                    b = rules[a].second.first;
                    c = rules[a].second.second;
                    if (P[p][s][b] && P[l - p][s + p + 1][c])
                    {
                        P[l + 1][s][a] = true;
                        if (a == spec_result_1)
                        {
                            P[l + 1][s][spec_rule_1] = true;
                        }
                        if ((a == spec_result_2_a) || (a == spec_result_2_b))
                        {
                            P[l + 1][s][spec_rule_2] = true;
                        }
                    }
                }
            }
        }
    }

    // for (size_t i = 0; i < n; i++)
    // {
    //     for (size_t j = 0; j < n; j++)
    //     {
    //         for (size_t k = 0; k < r; k++)
    //         {
    //             if (P[i][j][k] == true)
    //             {
    //                 std::cout << "true: ";
    //             }
    //             std::cout << "[" << i << "]"
    //                       << "[" << j << "]"
    //                       << "[" << k << "]"
    //                       << "\n";
    //         }
    //     }
    // }
    // std::cout << "\n\n\n";
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
    auto input = read_input("day19_input");
    // auto input = read_input("day19_test_input");

    bool rules_read = false;
    // my compiler doesn't like /s idk why
    std::regex reg_exp_a("([0-9]+):[[:space:]]([0-9]+)[[:space:]]([0-9]+)[[:space:]].*[[:space:]]([0-9]+)[[:space:]]([0-9]+)");
    std::smatch reg_out_a;
    std::map<int, std::pair<std::pair<int, int>, std::pair<int, int>>> data;
    int match = 0;
    int lc = 0;

    for (auto x : input)
    {
        if (x.empty())
        {
            rules_read = true;
            continue;
        }

        if (!rules_read)
        {
            std::regex_search(x, reg_out_a, reg_exp_a);
            auto p_a = std::make_pair(std::stoi(reg_out_a[2]), std::stoi(reg_out_a[3]));
            auto p_b = std::make_pair(std::stoi(reg_out_a[4]), std::stoi(reg_out_a[5]));
            auto val = std::make_pair(p_a, p_b);
            data.emplace(std::stoi(reg_out_a[1]), val);
        }
        else
        {
            lc++;
            std::cout << x << "\n";
            if (cyk_grammar(x, data))
            {
                match++;
                std::cout << "matched\n";
            }
        }
        std::cout << "matched: " << match << " of " << lc << "\n";
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
    // }
}