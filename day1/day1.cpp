#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
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

int similarityScore(const std::vector<int>& left,
                    const std::vector<int>& right) {
  int res = 0;

  if (left.size() != right.size()) {
    throw std::invalid_argument("Vectors are not the same length");
  }

  std::map<int, int> similarities{};
  for (auto element : left) {
    int similarityScore = 0;
    if (similarities.find(element) == similarities.end()) {
      int countSim = std::count_if(right.begin(), right.end(),
                                   [&element](int i) { return element == i; });
      similarityScore = element * countSim;
      similarities.insert(std::pair{element, similarityScore});
    } else {
      similarityScore = similarities.at(element);
    }
    res += similarityScore;
  }

  return res;
}

int main(int /* argc */, char** /* argv */) {
  auto data = parseDelimiterSeparatedFile("day1-input.txt.out", ',');
  std::vector<int> leftColumn = data.first;
  std::vector<int> rightColumn = data.second;
  std::sort(leftColumn.begin(), leftColumn.end());
  std::sort(rightColumn.begin(), rightColumn.end());

  auto sum = totalDistanceTwoVectors(leftColumn, rightColumn);
  std::cout << "Sum of distance: " << sum << std::endl;

  auto score = similarityScore(leftColumn, rightColumn);
  std::cout << "Sum of similarities: " << score << std::endl;

  return 0;
}
