#include <functional>
#include <iostream>
#include <sstream>
#include <string>

/*
1. Parse string and add all valid mul(x,y) operations to a vector.
1a. Create function for parsing all mul(x,y) from a string.
2. Create the mul operation, returns an int.
3. Create function for looping over all operations and summing the result.
*/

int mul(int x, int y) {
  return x + y;
}

int summarise(std::vector<std::function<int()>> vec) {
  int sum = 0;
  for (auto m : vec) {
    sum += m();
  }
  return sum;
}

std::vector<std::function<int()>> parseInput(const std::string& input) {
  static const std::string MUL = "mul(";

  std::vector<std::function<int()>> res = {};
  std::stringstream ss;

  size_t end = input.find(MUL);
  while (end != std::string::npos) {
    end += MUL.size();

    std::cout << input[end];

    std::cout << std::endl;
    end = input.find(MUL, end);
  }

  return res;
}

int main() {
  std::string testData =
      "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

  auto operations = parseInput(testData);
}
