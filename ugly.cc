#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  int cnt = 6;
  int i;
  vector<pair<int, int>> ugly;
  ugly.emplace_back(0, 0);
  for (i = 1; i < cnt; ++i) ugly.emplace_back(i, 1);
  for (i = cnt; cnt <= 505; ++i) {
    if (i % 2 == 0 && ugly[i / 2].second == 1) {
      ugly.emplace_back(i, 1);
      ++cnt;
    } else if (i % 3 == 0 && ugly[i / 3].second == 1) {
      ugly.emplace_back(i, 1);
      ++cnt;
      continue;
    } else if (i % 5 == 0 && ugly[i / 5].second == 1) {
      ugly.emplace_back(i, 1);
      ++cnt;
      continue;
    } else {
      ugly.emplace_back(i, 0);
    }
  }
  while (t--) {
    int n;
    cin >> n;
    cnt = 0;
    for (i = 0; cnt < n; ++i) {
      if (ugly[i].second == 1) ++cnt;
    }
    cout << ugly[i - 1].first << "\n";
  }
  return 0;
}
