#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

std::stringstream LOG;

std::vector<int> getData(std::filesystem::path fp) {
  std::vector<int> ret;
  std::ifstream istrm(fp);

  if (!istrm.is_open()) {
    LOG << "Failed to open file: " << fp.c_str() << std::endl;
  }

  return ret;
}

int main() {
  auto data = getData("day4-input.txt.out");
  LOG << data.size();
  std::cout << LOG.str() << std::endl;
}
