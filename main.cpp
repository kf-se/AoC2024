#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "helpers.h"

int totalDistanceTwoVectors(const std::vector<int>& leftColumn,
                            const std::vector<int>& rightColumn) {
  // printVector(leftColumn);
  // printVector(rightColumn);

  if (leftColumn.size() != rightColumn.size()) {
    throw std::invalid_argument("Vectors are not the same length");
  }

  int totalDistance = 0;
  for (size_t i = 0; i < leftColumn.size(); i++) {
    totalDistance += std::abs(leftColumn.at(i) - rightColumn.at(i));
  }

  return totalDistance;
}

int main(int /* argc */, char** /* argv */) {
  changeDelimiterOfFile("day1-input.txt", "day1-input.txt.output", "   ", ",");
  auto data = parseDelimiterSeparatedFile("day1-input.txt.output", ',');
  std::vector<int> leftColumn = data.first;
  std::vector<int> rightColumn = data.second;
  std::sort(leftColumn.begin(), leftColumn.end());
  std::sort(rightColumn.begin(), rightColumn.end());

  auto sum = totalDistanceTwoVectors(leftColumn, rightColumn);

  std::cout << "Sum of distance: " << sum << std::endl;

  return 0;
}
