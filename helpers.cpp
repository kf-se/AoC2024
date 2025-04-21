#include <fstream>
#include <iostream>

#include "helpers.h"

namespace fs = std::filesystem;

bool has_only_space(const std::string& str) {
  return str.find_first_not_of(' ') == str.npos;
}

void changeDelimiterOfString(std::string& str, const std::string& delimFrom,
                             const std::string& delimTo) {
  auto pos = str.find(delimFrom);

  while (pos != std::string::npos) {
    str.replace(pos, delimFrom.size(), delimTo);
    pos = str.find(delimFrom, pos + delimTo.size());
  }
}

void changeDelimiterOfFile(const fs::path& fp, const fs::path& fp_out,
                           const std::string& delimFrom,
                           const std::string& delimTo) {
  std::ifstream istrm(fp);
  if (!istrm.is_open()) {
    throw std::logic_error("Failed to open file");
  }

  std::ofstream ostrm(fp_out);
  std::string line;
  getline(istrm, line);
  while (!istrm.eof()) {
    if (!has_only_space(line)) {
      changeDelimiterOfString(line, delimFrom, delimTo);
      ostrm << line << '\n';
    }
    getline(istrm, line);
  }
}

std::vector<std::string> tokenizer(const std::string& str, char delimiter) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = str.find(delimiter);

  while (end != std::string::npos) {
    auto substring = str.substr(start, end - start);
    tokens.push_back(substring);
    start = end + 1;
    end = str.find(delimiter, start);
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

std::pair<std::vector<int>, std::vector<int>> parseDelimiterSeparatedFile(
    fs::path fp, char delimiter) {
  std::pair<std::vector<int>, std::vector<int>> ret;

  std::ifstream istrm(fp);
  if (!istrm.is_open()) {
    std::cout << "failed to open " << fp.c_str() << std::endl;
    throw std::logic_error("Failed to open file");
  }

  std::string line;
  std::vector<std::vector<std::string>> lines;
  while (getline(istrm, line)) {
    // std::cout << "Current line " << line << std::endl;
    auto tokens = tokenizer(line, delimiter);
    ret.first.push_back(std::stoi(tokens[0]));
    ret.second.push_back(std::stoi(tokens[1]));
  }

  return ret;
}
