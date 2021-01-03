#include "utils.hpp"

int64_t compute(std::string string)
{
    int64_t result = 0;
    char stored_action = {};
    while (string.size() != 0)
    {
        if (string[0] == '(')
        {
            int b_count = 1;
            int pos = 1;
            while (b_count > 0)
            {
                if (string[pos] == '(')
                {
                    b_count++;
                }
                else if (string[pos] == ')')
                {
                    b_count--;
                }
                pos++;
            }

            if (stored_action == '+')
            {
                result += compute(string.substr(1, pos - 2));
            }
            else if (stored_action == '*')
            {
                result = result * compute(string.substr(1, pos - 2));
            }
            else
            {
                result = compute(string.substr(1, pos - 2));
            }
            string.erase(0, pos);
        }
        else if (string[0] == '+')
        {
            stored_action = '+';
            string.erase(0, 1);
        }
        else if (string[0] == '*')
        {
            stored_action = '*';
            string.erase(0, 1);
        }
        else
        {
            int digit = string[0] - '0';
            if (stored_action == '+')
            {
                result += digit;
            }
            else if (stored_action == '*')
            {
                result = result * digit;
            }
            else
            {
                result = digit;
            }
            string.erase(0, 1);
        }
    }
    return result;
}

std::string extra_brackets(std::string input)
{
    // when we find a plus, go back a unit (either char or entire bracket), and add a bracket.
    // Then find the end of the plus chain (i.e. end of line or a * symbol) and close the bracket.
    // If we find brackets, recurse that through & replace the bracket with the output from the recurse, then move on.
    bool not_done = true;
    for (int i = 0; i < input.size(); i++)
    {
        not_done = true;
        if (input[i] == '(')
        {
            int b_count = 1;
            int pos = i + 1;
            while (b_count > 0)
            {
                if (input[pos] == '(')
                {
                    b_count++;
                }
                else if (input[pos] == ')')
                {
                    b_count--;
                }
                pos++;
            }
            auto new_string = extra_brackets(input.substr(i + 1, pos - i - 2));
            input.erase(i + 1, pos - i - 2);
            input.insert(i + 1, new_string);
            i += new_string.length();
        }
        else if (input[i] == '+')
        {
            // Open the brackets
            if (input[i - 1] == ')')
            {
                int b_count = 1;
                int pos = i - 2;
                while (b_count > 0)
                {
                    if (input[pos] == ')')
                    {
                        b_count++;
                    }
                    else if (input[pos] == '(')
                    {
                        b_count--;
                    }
                    pos--;
                }
                input.insert(pos + 1, "(");
                i++;
            }
            else
            {
                input.insert(i - 1, "(");
                i++;
            }
            // Find where to close the brackets
            while (not_done)
            {
                if (i == (input.length() - 2))
                {
                    input.append(")");
                    not_done = false;
                }
                while (input[i + 2] == '+')
                {
                    i += 2;
                }

                if (i >= (input.length() - 2))
                {
                    input.append(")");
                    not_done = false;
                }
                else if (input[i + 2] == '*')
                {
                    input.insert(i + 2, ")");
                    not_done = false;
                }
                else if (input[i + 1] == '(')
                {
                    i++;
                    int b_count = 1;
                    int pos = i + 1;
                    while (b_count > 0)
                    {
                        if (input[pos] == '(')
                        {
                            b_count++;
                        }
                        else if (input[pos] == ')')
                        {
                            b_count--;
                        }
                        pos++;
                    }
                    auto new_string = extra_brackets(input.substr(i + 1, pos - i - 2));
                    input.erase(i + 1, pos - i - 2);
                    input.insert(i + 1, new_string);
                    i += (new_string.length());
                }
            }
        }
    }
    return input;
}

int main(int argc, char *argv[])
{
    auto input = read_input("day18_input");
    int64_t result = 0;
    for (auto line : input)
    {
        auto altered_line = extra_brackets(line);
        result += compute(altered_line);
    }
    std::cout << result << "\n";
}
