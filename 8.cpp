#include "utils.hpp"

void reset_uses(std::vector<std::pair<std::string, std::pair<int, bool>>> &instructions)
{
    for (auto &x : instructions)
    {
        x.second.second = false;
    }
}

std::pair<int, bool> run_instructions(std::vector<std::pair<std::string, std::pair<int, bool>>> &instructions)
{
    int ci = 0;
    int acc = 0;
    while (true)
    {
        if (ci >= instructions.size())
        {
            // Found the sequence that works
            return std::make_pair(acc, true);
        }

        if (instructions[ci].second.second)
        {
            return std::make_pair(acc, false);
        }

        if (instructions[ci].first == "nop")
        {
            instructions[ci].second.second = true;
            ci++;
            continue;
        }

        if (instructions[ci].first == "acc")
        {
            instructions[ci].second.second = true;
            acc += instructions[ci].second.first;
            ci++;
            continue;
        }

        if (instructions[ci].first == "jmp")
        {
            instructions[ci].second.second = true;
            ci += instructions[ci].second.first;
            continue;
        }
    }
};

int main(int argc, char *argv[])
{
    auto input = read_input("day8_input");
    std::vector<std::pair<std::string, std::pair<int, bool>>> instructions;

    for (auto x : input)
    {
        std::pair<std::string, std::pair<int, bool>> instruction = {};
        instruction.first = x.substr(0, 3);
        instruction.second = {std::stoi(x.substr(4)), false};
        instructions.push_back(instruction);
    }

    for (auto &x : instructions)
    {
        if (x.first == "nop")
        {
            x.first = "jmp";
        }
        else if (x.first == "jmp")
        {
            x.first = "nop";
        }
        auto result = run_instructions(instructions);
        if (result.second)
        {
            std::cout << "yeee \n";
            std::cout << result.first << "\n";
            break;
        }
        else if (x.first == "nop")
        {
            x.first = "jmp";
        }
        else if (x.first == "jmp")
        {
            x.first = "nop";
        }
        reset_uses(instructions);
    }
    return 0;
}