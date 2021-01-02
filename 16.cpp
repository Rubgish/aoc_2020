#include "utils.hpp"

class validity
{
public:
    std::vector<std::pair<int, int>> valid_ranges;
    std::string identifier;
    std::vector<int> possible_pos;
    int position;

    validity(std::string name)
    {
        identifier = name;
    }

    void add_range(int min, int max)
    {
        valid_ranges.push_back(std::make_pair(min, max));
    }

    bool validate(int &value)
    {
        bool valid = false;
        for (auto x : valid_ranges)
        {
            if ((value >= x.first) && (value <= x.second))
            {
                valid = true;
            }
        }
        return valid;
    }

    void erase_pos(int pos)
    {
        possible_pos.erase(std::remove(possible_pos.begin(), possible_pos.end(), pos), possible_pos.end());
    }
};

int check_rules(std::vector<int> &ticket, std::vector<validity> &rules)
{
    int invalid_count = 0;
    for (auto x : ticket)
    {
        bool loop_valid = false;
        for (auto y : rules)
        {
            if (y.validate(x))
            {
                loop_valid = true;
            }
        }
        if (!loop_valid)
        {
            invalid_count += x;
        }
    }
    return invalid_count;
}

int main(int argc, char *argv[])
{

    std::vector<validity> rules;

    // Why write a parser when you can have your cursor in 20 places at once?
    auto rule = validity("departure_location");
    rule.add_range(43, 237);
    rule.add_range(251, 961);
    rules.push_back(rule);
    rule = validity("departure_station");
    rule.add_range(27, 579);
    rule.add_range(586, 953);
    rules.push_back(rule);
    rule = validity("departure_platform");
    rule.add_range(31, 587);
    rule.add_range(608, 967);
    rules.push_back(rule);
    rule = validity("departure_track");
    rule.add_range(26, 773);
    rule.add_range(784, 973);
    rules.push_back(rule);
    rule = validity("departure_date");
    rule.add_range(41, 532);
    rule.add_range(552, 956);
    rules.push_back(rule);
    rule = validity("departure_time");
    rule.add_range(33, 322);
    rule.add_range(333, 972);
    rules.push_back(rule);
    rule = validity("arrival_location");
    rule.add_range(30, 165);
    rule.add_range(178, 965);
    rules.push_back(rule);
    rule = validity("arrival_station");
    rule.add_range(31, 565);
    rule.add_range(571, 968);
    rules.push_back(rule);
    rule = validity("arrival_platform");
    rule.add_range(36, 453);
    rule.add_range(473, 963);
    rules.push_back(rule);
    rule = validity("arrival_track");
    rule.add_range(35, 912);
    rule.add_range(924, 951);
    rules.push_back(rule);
    rule = validity("class");
    rule.add_range(39, 376);
    rule.add_range(396, 968);
    rules.push_back(rule);
    rule = validity("duration");
    rule.add_range(31, 686);
    rule.add_range(697, 974);
    rules.push_back(rule);
    rule = validity("price");
    rule.add_range(28, 78);
    rule.add_range(96, 971);
    rules.push_back(rule);
    rule = validity("route");
    rule.add_range(32, 929);
    rule.add_range(943, 955);
    rules.push_back(rule);
    rule = validity("row");
    rule.add_range(40, 885);
    rule.add_range(896, 968);
    rules.push_back(rule);
    rule = validity("seat");
    rule.add_range(26, 744);
    rule.add_range(765, 967);
    rules.push_back(rule);
    rule = validity("train");
    rule.add_range(46, 721);
    rule.add_range(741, 969);
    rules.push_back(rule);
    rule = validity("type");
    rule.add_range(30, 626);
    rule.add_range(641, 965);
    rules.push_back(rule);
    rule = validity("wagon");
    rule.add_range(48, 488);
    rule.add_range(513, 971);
    rules.push_back(rule);
    rule = validity("zone");
    rule.add_range(34, 354);
    rule.add_range(361, 973);
    rules.push_back(rule);

    auto input = read_input("day16_input");
    std::vector<int> ticket;
    std::vector<std::vector<int>> nearby_tickets;

    bool my_ticket = true;
    for (auto x : input)
    {
        if (x.empty() || x.find("your ticket") != std::string::npos)
        {
            continue;
        }
        if (x.find("nearby tickets:") != std::string::npos)
        {
            my_ticket = false;
            continue;
        }
        std::stringstream ss(x);
        if (my_ticket)
        {
            for (int i; ss >> i;)
            {
                ticket.push_back(i);
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }
        }
        else
        {
            std::vector<int> cur_ticket;
            for (int i; ss >> i;)
            {
                cur_ticket.push_back(i);
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }
            nearby_tickets.push_back(cur_ticket);
        }
    }

    int error_rate = 0;
    for (auto x : nearby_tickets)
    {
        error_rate += check_rules(x, rules);
    }
    std::cout << "error rate: " << error_rate << "\n";

    std::vector<std::vector<int>> valid_tickets;
    for (auto x : nearby_tickets)
    {
        if (check_rules(x, rules) == 0)
        {
            valid_tickets.push_back(x);
        }
    }

    for (auto &x : rules)
    {
        for (size_t i = 0; i < ticket.size(); i++)
        {
            bool field_match = true;
            for (auto y : valid_tickets)
            {
                if (!(x.validate(y[i])))
                {
                    // It's not this field
                    field_match = false;
                    break;
                }
            }
            if (field_match)
            {
                x.possible_pos.push_back(i);
            }
        }
    }

    int result_count = 0;
    while (result_count < rules.size())
    {
        for (auto &x : rules)
        {
            if (x.possible_pos.size() == 1)
            {
                auto result = x.possible_pos.front();
                x.position = result;
                for (auto &y : rules)
                {
                    y.erase_pos(result);
                }
                result_count++;
                break;
            }
        }
    }

    int64_t multi_result = 1;
    for (auto x : rules)
    {
        if (x.identifier.find("departure") != std::string::npos)
        {
            multi_result = multi_result * ticket[x.position];
        }
    }
    std::cout << "multiplication result: " << multi_result << "\n";
}
