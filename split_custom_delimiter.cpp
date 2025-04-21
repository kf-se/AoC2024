#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = str.find(delimiter);

  while (end != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + 1;
    end = str.find(delimiter, start);
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

int main() {
  std::string csv = "apple,banana,orange,grape";
  auto fruits = split(csv, ',');

  for (const auto& fruit : fruits) {
    std::cout << fruit << std::endl;
  }
  return 0;
}
