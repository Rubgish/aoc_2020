#include "utils.hpp"

int main(int argc, char *argv[])
{
  auto input = read_input("day3_input");
  std::pair<int64_t, int64_t> result = {0, 0};
  char hash[] = {'#'};
  int64_t tree_count = 0;
  int64_t input_length = input[0].length();
  std::vector<std::pair<int64_t, int64_t>> slopes = {{1, 1}, {1, 3}, {1, 5}, {1, 7}, {2, 1}};
  std::vector<std::int64_t> outputs;
  for (auto x : slopes)
  {
    tree_count = 0;
    result = {0, 0};
    while (result.first < input.size())
    {
      if (input[result.first].at(result.second % input_length) == hash[0])
      {
        tree_count += 1;
      }
      result.first += x.first;
      result.second += x.second;
    }
    std::cout << tree_count << "\n";
    outputs.push_back(tree_count);
  }

  int64_t total_trees = 1;
  for (auto x : outputs)
  {
    total_trees = total_trees * x;
  }
  std::cout << total_trees << "\n";
}