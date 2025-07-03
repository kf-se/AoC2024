#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;
stringstream LOG;

vector<string> getData(filesystem::path fp) {
  vector<string> ret;
  ifstream istrm(fp);

  if (!istrm.is_open()) {
    LOG << "Failed to open file: " << fp.c_str() << endl;
  }

  string line;
  while (getline(istrm, line)) {
    ret.push_back(line);
  }

  return ret;
}

int findXmas(const vector<string> &data) {
  const map<int, char> xmas = {{1, 'M'}, {2, 'A'}, {3, 'S'}};
  size_t dataSize = data.size();
  int rx = 0;
  int nrXmas = 0;

  while (rx < dataSize) {
    int cx = 0;
    string row = data.at(rx);
    size_t rowSize = row.size();

    while (cx < rowSize) {
      if (row.at(cx) == 'X') {
        // Find horizontal
        {
          bool leftMatch = true;
          bool rightMatch = true;
          for (const auto &[k, v] : xmas) {
            if (cx - k < 0 || row.at(cx - k) != v)
              leftMatch = false;
            if (cx + k >= rowSize || row.at(cx + k) != v)
              rightMatch = false;
          }
          if (leftMatch)
            ++nrXmas;
          if (rightMatch)
            ++nrXmas;
        }
        // Find vertical
        {
          bool upMatch = true;
          bool downMatch = true;
          for (const auto &[k, v] : xmas) {
            if (rx - k < 0 || data.at(rx - k).at(cx) != v)
              upMatch = false;
            if (rx + k >= dataSize || cx >= data.at(rx + k).size() ||
                data.at(rx + k).at(cx) != v)
              downMatch = false;
          }
          if (upMatch)
            ++nrXmas;
          if (downMatch)
            ++nrXmas;
        }
        // Find diagonal
        {
          bool upLeftMatch = true;
          bool upRightMatch = true;
          bool downLeftMatch = true;
          bool downRightMatch = true;

          for (const auto &[k, v] : xmas) {
            if (rx - k < 0 || cx - k < 0 || data.at(rx - k).at(cx - k) != v)
              upLeftMatch = false;
            if (rx - k < 0 || cx + k >= data.at(rx - k).size() ||
                data.at(rx - k).at(cx + k) != v)
              upRightMatch = false;
            if (rx + k >= dataSize || cx + k >= data.at(rx + k).size() ||
                data.at(rx + k).at(cx + k) != v)
              downRightMatch = false;
            if (rx + k >= dataSize || cx - k < 0 ||
                cx + k > data.at(rx + k).size() ||
                data.at(rx + k).at(cx - k) != v)
              downLeftMatch = false;
          }

          if (upLeftMatch)
            ++nrXmas;
          if (downLeftMatch)
            ++nrXmas;
          if (upRightMatch)
            ++nrXmas;
          if (downRightMatch)
            ++nrXmas;
        }
      }
      ++cx;
    }
    ++rx;
  }

  return nrXmas;
}

int main() {
  auto data = getData("day4-input.txt.out");
  LOG << data.size();
  cout << LOG.str() << endl;
  cout << data[0].size() << endl;
  data = {"MMMSXXMASM", "MSAMXMSMSA", "AMXSXMAAMM", "MSAMASMSMX", "XMASAMXAMM",
          "XXAMMXXAMA", "SMSMSASXSS", "SAXAMASAAA", "MAMMMXMMMM", "MXMXAXMASX"};
  int ret = findXmas(data);
  cout << "answer: " << ret << endl;
}
