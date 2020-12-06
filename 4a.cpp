#include "utils.hpp"

// Should I make a deseralizer with an expected set of formats & types and use that? Absolutely. Will I? Only if they make us extend this in future :D.
// Should I have a passport class? Also yes.
// Should I stop messing around with strings? Definitely.

bool validate_passport(std::unordered_map<std::string, std::string> &pp)
{
  if ((std::stoi(pp["byr"]) < 1920) || (std::stoi(pp["byr"]) > 2002))
  {
    return false;
  }

  if ((std::stoi(pp["iyr"]) < 2010) || (std::stoi(pp["iyr"]) > 2020))
  {
    return false;
  }

  if ((std::stoi(pp["eyr"]) < 2020) || (std::stoi(pp["eyr"]) > 2030))
  {
    return false;
  }

  auto v_height = false;
  if (pp["hgt"].substr(pp["hgt"].length() - 2) == "cm")
  {
    auto hgt = std::stoi(pp["hgt"].substr(0, pp["hgt"].length() - 2));
    if (hgt < 150 || hgt > 193)
    {
      return false;
    }
    v_height = true;
  }
  if (pp["hgt"].substr(pp["hgt"].length() - 2) == "in")
  {
    auto hgt = std::stoi(pp["hgt"].substr(0, pp["hgt"].length() - 2));
    if (hgt < 59 || hgt > 76)
    {
      return false;
    }
    v_height = true;
  }
  if (!v_height)
  {
    return false;
  }

  if ((pp["pid"].length() != 9) || (pp["pid"].find_first_not_of("0123456789") != std::string::npos))
  {
    return false;
  }
  std::list<std::string> valid_eyes = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
  if (std::find(valid_eyes.begin(), valid_eyes.end(), pp["ecl"]) == valid_eyes.end())
  {
    return false;
  }

  if (pp["hcl"].size() != 7)
  {
    return false;
  }

  if (pp["hcl"].substr(0, 1) != "#")
  {
    return false;
  }

  if (pp["hcl"].substr(1).find_first_not_of("0123456789abcdef") != std::string::npos)
  {
    return false;
  }

  return true;
}

int main(int argc, char *argv[])
{
  auto input = read_input("day4_input");
  std::vector<std::unordered_map<std::string, std::string>> passports;
  std::unordered_map<std::string, std::string> current_passport = {};
  std::vector<std::string> kv_pairs = {};
  std::string colon = ":";
  for (auto x : input)
  {
    std::istringstream istream(x);
    std::string cur_str;

    // If we just have a new line, that's a new passport.
    if (istream.peek() == EOF)
    {
      passports.push_back(current_passport);
      current_passport = {};
      continue;
    }

    std::copy(std::istream_iterator<std::string>(istream), std::istream_iterator<std::string>(), std::back_inserter(kv_pairs));

    for (auto y : kv_pairs)
    {
      auto key = y.substr(0, y.find(colon));
      auto len = key.length() + colon.length();
      auto value = y.substr(len);
      current_passport.insert(std::make_pair(key, value));
    }

    kv_pairs = {};
  }

  // We won't have inserted the last passport, so do it now:
  passports.push_back(current_passport);

  std::vector<std::unordered_map<std::string, std::string>> valid_passports;

  std::vector<std::string> req_pp_fields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
  int valid_pp = 0;
  for (auto x : passports)
  {
    auto valid = true;
    for (size_t i = 0; i < req_pp_fields.size(); i++)
    {
      if (x.count(req_pp_fields[i]) == 0)
      {
        // invalid passport
        valid = false;
        break;
      }
    }
    if (valid)
    {
      valid_pp += 1;
      valid_passports.push_back(x);
    }
  }
  std::cout << valid_pp << "\n";

  int final_pp = 0;
  for (auto x : valid_passports)
  {
    if (validate_passport(x))
    {
      final_pp += 1;
    }
  }

  std::cout << final_pp << "\n";
}