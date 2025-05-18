#include <filesystem>

#include "helpers.h"

int main(int argc, char** argv) {
  std::filesystem::path fp = "input.txt.out";
  auto data = parseDelimiterSeparatedFile(fp, ',');
  return 0;
}
