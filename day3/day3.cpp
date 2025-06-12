#include <cctype>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::stringstream LOG;

/*
1. Parse string and add all valid mul(x,y) operations to a vector.
1a. Create function for parsing all mul(x,y) from a string.
2. Create the mul operation, returns an int.
3. Create function for looping over all operations and summing the result.
*/

int mul(int x, int y) {
  return x * y;
}

int summarise(std::vector<std::function<int()>> vec) {
  int sum = 0;
  for (auto m : vec) {
    sum += m();
  }
  return sum;
}

bool isDigit(const char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}

bool isEndingParenthesis(const char c) {
  return c == ')';
}

bool isComma(const char c) {
  return c == ',';
}

std::vector<std::function<int()>> parseInput(const std::string& input) {
  static const std::string MUL = "mul(";

  std::vector<std::function<int()>> res = {};
  std::stringstream ss;

  size_t end = input.find(MUL);
  while (end != std::string::npos) {
    end += MUL.size();
    auto start = end;
    while (start != std::string::npos && isDigit(input.at(start)) &&
           start - end < 3) {
      ++start;
    }
    auto subs = input.substr(end, start - end);
    LOG << end << " " << start << " "
        << "Substring: " << subs << std::endl;
    int x = 0;
    try {
      x = std::stoi(subs);
      LOG << x << std::endl;
    } catch (std::invalid_argument& e) {
      LOG << e.what() << input.substr(end, start) << std::endl;
    }

    int y = 0;
    if (start != std::string::npos && isComma(input.at(start))) {
      auto end2 = start + 1;
      auto nextStart = end2;
      while (nextStart != std::string::npos && isDigit(input.at(nextStart)) &&
             nextStart - end2 < 3) {
        ++nextStart;
      }
      auto subss = input.substr(end2, nextStart - end2);
      LOG << end2 << " " << nextStart << " "
          << "Substrings: " << subss << std::endl;
      try {
        y = std::stoi(subss);
        LOG << y << std::endl;
      } catch (std::invalid_argument& e) {
        LOG << e.what() << subss << std::endl;
      }

      if (nextStart != std::string::npos &&
          isEndingParenthesis(input.at(nextStart))) {
        LOG << "Push back" << std::endl;
        res.push_back(std::bind(mul, x, y));
      }
    }

    end = input.find(MUL, end);
  }

  return res;
}

int main() {
  std::string testData =
      "xmul(2,4)%&mul[3,7]!mul(02341.)@^do_not_mul(5,5)+mul(32,64]then(mul(11,"
      "8)"
      "mul(8,5))";

  auto fp = std::filesystem::path("day3-input.txt.out");
  std::ifstream istrm(fp);
  if (!istrm.is_open()) {
    std::cout << "failed to open " << fp.c_str() << std::endl;
    throw std::logic_error("Failed to open file");
  }

  std::string data;
  for (std::string line; std::getline(istrm, line);) {
    data += line;
  }

  auto operations = parseInput(data);
  auto res = summarise(operations);
  std::cout << data;
  std::cout << LOG.str();
  std::cout << "Results: " << res << std::endl;
}
