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

int findMas(const vector<string> &data) {
  size_t dataSize = data.size();
  int rx = 0;
  int nrXmas = 0;

  while (rx < dataSize) {
    int cx = 0;
    string row = data.at(rx);
    size_t rowSize = row.size();

    while (cx < rowSize) {
      if (row.at(cx) == 'A') {
        bool tl = false;
        bool bl = false;
        bool tr = false;
        bool br = false;
        int rA = rx + 1;
        int rB = rx - 1;
        int cB = cx - 1;
        int cA = cx + 1;
        if (rB >= 0 && cB >= 0 && data.at(rB).at(cB) == 'M') {
          if (rA < dataSize && cA < data.at(rA).size() &&
              data.at(rA).at(cA) == 'S')
            tl = true;
        }
        if (rB >= 0 && cA < data.at(rB).size() && data.at(rB).at(cA) == 'M') {
          if (rA < dataSize && cB >= 0 && data.at(rA).at(cB) == 'S')
            tr = true;
        }
        if (rA < dataSize && cA < data.at(rA).size() &&
            data.at(rA).at(cA) == 'M') {
          if (rB >= 0 && cB >= 0 && data.at(rB).at(cB) == 'S') {
            br = true;
          }
        }
        if (rA < dataSize && cB >= 0 && data.at(rA).at(cB) == 'M') {
          if (rB >= 0 && cA < data.at(rB).size() && data.at(rB).at(cA) == 'S')
            bl = true;
        }
        if ((tl && tr) || (tl && bl) || (tr && br) || (bl && br))
          ++nrXmas;
      }
      ++cx;
    }
    ++rx;
  }

  return nrXmas;
}

int findXmas(const vector<string> &data) {
  const map<int, char> xmas = {{1, 'M'}, {2, 'A'}, {3, 'S'}};
  const map<int, char> mas = {{1, 'M'}, {2, 'A'}, {3, 'S'}};
  size_t dataSize = data.size();
  int rx = 0;
  int nrXmas = 0;

  while (rx < dataSize) {
    int cx = 0;
    string row = data.at(rx);
    size_t rowSize = row.size();

    while (cx < rowSize) {
      if (row.at(cx) == 'X') {
        bool leftMatch = true;
        bool rightMatch = true;
        bool upMatch = true;
        bool downMatch = true;
        bool upLeftMatch = true;
        bool upRightMatch = true;
        bool downLeftMatch = true;
        bool downRightMatch = true;
        for (const auto &[k, v] : xmas) {
          // Find horizontal
          if (cx - k < 0 || row.at(cx - k) != v)
            leftMatch = false;
          if (cx + k >= rowSize || row.at(cx + k) != v)
            rightMatch = false;

          // Find vertical
          if (rx - k < 0 || data.at(rx - k).at(cx) != v)
            upMatch = false;
          if (rx + k >= dataSize || cx >= data.at(rx + k).size() ||
              data.at(rx + k).at(cx) != v)
            downMatch = false;

          // Find diagonal
          if (rx - k < 0 || cx - k < 0 || data.at(rx - k).at(cx - k) != v)
            upLeftMatch = false;
          if (rx - k < 0 || cx + k >= data.at(rx - k).size() ||
              data.at(rx - k).at(cx + k) != v)
            upRightMatch = false;
          if (rx + k >= dataSize || cx + k >= data.at(rx + k).size() ||
              data.at(rx + k).at(cx + k) != v)
            downRightMatch = false;
          if (rx + k >= dataSize || cx - k < 0 || data.at(rx + k).size() == 0 ||
              data.at(rx + k).at(cx - k) != v)
            downLeftMatch = false;
        }
        if (leftMatch)
          ++nrXmas;
        if (rightMatch)
          ++nrXmas;
        if (upMatch)
          ++nrXmas;
        if (downMatch)
          ++nrXmas;
        if (upLeftMatch)
          ++nrXmas;
        if (downLeftMatch)
          ++nrXmas;
        if (upRightMatch)
          ++nrXmas;
        if (downRightMatch)
          ++nrXmas;
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
  vector<string> data2 = {
      "MMMSXXMASM", "MSAMXMSMSA", "AMXSXMAAMM", "MSAMASMSMX", "XMASAMXAMM",
      "XXAMMXXAMA", "SMSMSASXSS", "SAXAMASAAA", "MAMMMXMMMM", "MXMXAXMASX"};
  vector<string> data3 = {
      ".M.S......", "..A..MSMS.", ".M.S.MAA..", "..A.ASMSM.", ".M.S.M....",
      "..........", "S.S.S.S.S.", ".A.A.A.A..", "M.M.M.M.M.", ".........."};
  // int ret = findXmas(data);
  int ret2 = findMas(data);
  // cout << "answer: " << ret << endl;
  cout << "answer2: " << ret2 << endl;
}
