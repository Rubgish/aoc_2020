#include "utils.hpp"

void transform_str(std::string& bp_str){
    
    // Iterate over itself, updating letters to binary in place.
    std::transform(std::begin(bp_str), std::end(bp_str), std::begin(bp_str), [](auto ch) {
        switch(ch) {
            case 'F':
              return '0';
            case 'B':
              return '1';
            case 'L':
              return '0';
            case 'R':
              return '1';
        }
    });
}

int main(int argc, char *argv[]) {
  auto input = read_input("day5_input");
  uint64_t max_value = 0;
  std::vector<int> seat_list = {};

  for (auto x: input)
  {
      // Get some 1's and 0's
      transform_str(x);

      // Turn 1's and 0's into ints
      auto row = std::stoi(x.substr(0, 7), nullptr, 2);
      auto column = std::stoi(x.substr(7), nullptr, 2);

      // Calc the seat ID
      auto seat_id = (row * 8) + column;

      // Store it (part 2 requirement)
      seat_list.push_back(seat_id);

      // Update the highest seat ID if we calculated a new one
      if (seat_id > max_value)
      {
          max_value = seat_id;
      }
  }

  std::cout << max_value << "\n";

  // Quick & dirty part 2.
  // Not first row -> greater than 7, my seat_id was 933 -> less than 933.
  for (size_t i = 7; i < 933; i++)
  {
      if (std::count(seat_list.begin(), seat_list.end(), i))
      {
          continue;
      }
      else
      {
          std::cout << i << " is missing \n";
      }
  }

  return 0;
}