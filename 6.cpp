#include "utils.hpp"

int main(int argc, char *argv[]) {
  auto input = read_input("day6_input");
  std::vector<std::unordered_map<char, int>> c_form_groups = {};
  std::vector<int> c_form_valid = {};
  std::unordered_map<char, int> current_group = {};
  int group_size = 0;

  for (auto x: input)
  {
    std::istringstream istream(x);
    // If we just have a new line, that's a new group.
    if (istream.peek()== EOF)
    {
        int valid_count = 0;
        for (auto y: current_group)
        {
            if (y.second == group_size)
            {
              valid_count += 1;
            }
        }
        c_form_groups.push_back(current_group);
        c_form_valid.push_back(valid_count);
        current_group = {};
        group_size = 0;
        continue;
    }

    group_size += 1;
    for (size_t i = 0; i < x.length(); i++)
    {
        current_group[x[i]]++;
    }
  }

  // Last group. Need some kind of finally aspect to save doing this?
  c_form_groups.push_back(current_group);
  int valid_count = 0;
  for (auto y: current_group)
  {
    if (y.second == group_size)
    {
      valid_count += 1;
    }
  }
  c_form_valid.push_back(valid_count);

  // Calculate results
  int total_sum = 0;
  for (auto x: c_form_groups)
  {
      total_sum += x.size();
  }

  std::cout << total_sum << "\n";

  int total_valid_sum = 0;
  for (auto x: c_form_valid)
  {
      total_valid_sum += x;
  }

  std::cout << total_valid_sum << "\n";
  return 0;
}