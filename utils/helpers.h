#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

bool has_only_space(const std::string& str);

void changeDelimiterOfString(std::string& str, const std::string& delimFrom,
                             const std::string& delimTo);

void changeDelimiterOfFile(const fs::path& fp, const fs::path& fp_out,
                           const std::string& delimFrom,
                           const std::string& delimTo);

std::vector<std::string> tokenizer(const std::string& str, char delimiter);

std::pair<std::vector<int>, std::vector<int>> parseDelimiterSeparatedFile(
    fs::path fp, char delimiter);

std::vector<std::vector<int>> parseDelimiterSeparatedFileV2(fs::path fp,
                                                            char delimiter);

void printVector(const std::vector<int>& vec);
