#include <algorithm>
#include <filesystem>
#include <iostream>
#include <iterator>

#include "helpers.h"

template <typename T>
int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

bool withinDistance(int first, int second) {
  int distance = std::abs(second - first);
  return distance >= 1 && distance <= 3;
}

int solveDay2(const std::vector<std::vector<int>>& vec) {
  int unsafe_reports = 0;
  for (auto v : vec) {
    if (v.size() < 2) {
      unsafe_reports++;
      continue;
    }

    auto it = ++v.begin();
    auto current = *(it);
    auto prev = *(it - 1);
    auto sign = sgn(current - prev);

    if (sign == 0 || !withinDistance(current, prev)) {
      unsafe_reports++;
      continue;
    }

    while (++it != v.end()) {
      current = *(it);
      prev = *(it - 1);
      auto newSign = sgn(current - prev);
      if (!withinDistance(current, prev)) {
        unsafe_reports++;
        break;
      }
      if (newSign != sign) {
        unsafe_reports++;
        break;
      }
    }
  }
  return vec.size() - unsafe_reports;
}

int main(int argc, char** argv) {
  std::filesystem::path fp = "day2-input.txt.out";
  auto data = parseDelimiterSeparatedFileV2(fp, ',');
  // auto ret = solveDay2(data);
  std::vector<std::vector<int>> testData = {{7, 6, 4, 2, 1}, {1, 2, 7, 8, 9},
                                            {9, 7, 6, 2, 1}, {1, 3, 2, 4, 5},
                                            {8, 6, 4, 4, 1}, {1, 3, 6, 7, 9},
                                            {4, 4, 4, 4},    {4, 4, 3, 3, 2, 2},
                                            {4, 4},          {4},
                                            {4, 4, 3},       {4, 4, 4}};

  std::cout << "Solution to day 2: " << solveDay2(data) << std::endl;
  return 0;
}
