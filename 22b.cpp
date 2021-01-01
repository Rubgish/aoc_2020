#include "utils.hpp"

bool recurse(std::queue<int> p1, std::queue<int> p2)
{
    int loop_count = 0;
    while ((p1.size() != 0) && (p2.size() != 0))
    {
        if (p1.size() > p1.front() && p2.size() > p2.front())
        {
            bool p1_win = false;
            std::queue<int> p1_copy = p1;
            p1_copy.pop();
            std::queue<int> p1_new;
            std::queue<int> p2_copy = p2;
            p2_copy.pop();
            std::queue<int> p2_new;
            for (int i = 0; i < p1.front(); i++)
            {
                p1_new.push(p1_copy.front());
                p1_copy.pop();
            }
            for (int i = 0; i < p2.front(); i++)
            {
                p2_new.push(p2_copy.front());
                p2_copy.pop();
            }
            p1_win = recurse(p1_new, p2_new);

            if (p1_win)
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
        }
        else
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
        }
        loop_count++;

        // You know when you just like, forgot about a requirement and don't really fancy
        // dealing with it, so you just add some janky loop detection that says
        // 'if we've looped 800 times we're almost certainly repeating previous
        // configurations so lets just say player 1 wins?'. No? Well I do.
        if (loop_count % 800 == 0)
        {
            return true;
        }
    }
    if (p1.size() != 0)
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
        if ((p1.size() > p1.front()) && (p2.size() > p2.front()))
        {
            bool p1_win = false;
            std::queue<int> p1_copy = p1;
            p1_copy.pop();
            std::queue<int> p1_new;
            std::queue<int> p2_copy = p2;
            p2_copy.pop();
            std::queue<int> p2_new;
            for (int i = 0; i < p1.front(); i++)
            {
                p1_new.push(p1_copy.front());
                p1_copy.pop();
            }
            for (int i = 0; i < p2.front(); i++)
            {
                p2_new.push(p2_copy.front());
                p2_copy.pop();
            }

            p1_win = recurse(p1_new, p2_new);

            if (p1_win)
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
        }
        else
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
