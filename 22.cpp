#include "utils.hpp"

int main(int argc, char *argv[])
{
    auto input = read_input("day22_input");
    std::queue<int> p1;
    std::queue<int> p2;

    bool read_p2 = false;
    for (auto line : input)
    {
        if (line.empty() || line.find("Player 1") != std::string::npos)
        {
            continue;
        }
        else if (line.find("Player 2") != std::string::npos)
        {
            read_p2 = true;
            continue;
        }
        else if (read_p2)
        {
            p2.push(std::stoi(line));
        }
        else
        {
            p1.push(std::stoi(line));
        }
    }

    int i = 0;
    while ((p1.size() != 0) && (p2.size() != 0))
    {
        if (p1.front() > p2.front())
        {
            p1.push(p1.front());
            p1.push(p2.front());
            p1.pop();
            p2.pop();
        }
        else
        {
            p2.push(p2.front());
            p2.push(p1.front());
            p1.pop();
            p2.pop();
        }

        i++;
        if (i % 100 == 0)
        {
            std::cout << i << "\n";
        }
    }

    int score = 0;
    int size = 50;
    if (p1.size() != 0)
    {
        while (size >= 1)
        {
            score += (p1.front() * size);
            p1.pop();
            size--;
        }
    }
    else
    {
        while (size >= 1)
        {
            score += (p2.front() * size);
            p2.pop();
            size--;
        }
    }

    std::cout << score << "\n";

    // 2x queues
    // compare queue::front()
    //  pop both elements
    //  push to winner
    // continue til queue is empty
}
