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
  const map<int, char> horizontal = {{1, 'M'}, {2, 'A'}, {3, 'S'}};
  const map<int, char> vertical = {{1, 'M'}, {2, 'A'}, {3, 'S'}};
  const map<int, char> diagonalLeft = {{1, 'M'}, {2, 'A'}, {3, 'S'}};
  const map<int, char> diagonalRight = {{1, 'M'}, {2, 'A'}, {3, 'S'}};

  int rx = 0;
  int nrXmas = 0;

  while (rx < data.size()) {
    int cx = 0;
    string row = data.at(rx);
    size_t rowSize = row.size();
    while (cx < rowSize) {
      cout << rx << " " << cx << endl;
      if (row.at(cx) == 'X') {
        // Find horizontal
        {
          bool leftMatch = true;
          bool rightMatch = true;
          for (const auto &[k, v] : horizontal) {
            int left = -k;
            int right = k;
            cout << cx + right << endl;
            if (cx + left < 0 || row.at(cx + left) != v)
              leftMatch = false;
            if (cx + right >= rowSize || row.at(cx + right) != v)
              rightMatch = false;
          }
          if (leftMatch)
            ++nrXmas;
          if (rightMatch)
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
  for (int c = 0; c < 3; c++) {
    cout << data[c] << endl;
  }
  int ret = findXmas(data);
  cout << "answer: " << ret << endl;
}
