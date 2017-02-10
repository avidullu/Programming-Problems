#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> v;
    v.resize(n);
    for (int i = 0; i < n; ++i) cin >> v[i];
    vector<int> s1, s2;
    s1.push_back(v[0]);
    int sum_s1 = s1.front(), sum_s2 = 0;
    int min_diff = sum_s1;
    for (int i = 1; i < n; ++i) {
      const int elem = v[i];
      int add_s1 = abs(sum_s1 + elem - sum_s2);
      int add_s2 = abs(sum_s2 + elem - sum_s1);
      int replace_s1 = 10000, replace_s2 = 100000, idx_s1 = 0, idx_s2 = -1;
      for (int j = 0; j < s1.size(); ++j) {
        const int e = s1[j];
        if (abs((sum_s1 - e + elem) - (sum_s2 + e)) < replace_s1) {
          replace_s1 = abs((sum_s1 - e + elem) - (sum_s2 + e));
          idx_s1 = j;
        }
      }
      for (int j = 0; j < s2.size(); ++j) {
        const int e = s2[j];
        if (abs((sum_s2 - e + elem) - (sum_s1 + e)) < replace_s2) {
          replace_s2 = abs((sum_s2 - e + elem) - (sum_s1 + e));
          idx_s2 = j;
        }
      }
      const int min_val = std::min({add_s1, add_s2, replace_s1, replace_s2});
      // cout << "i: " << i << " :add_s1: " << add_s1 << ":add_s2: " << add_s2
      // << ":replace_s1: " << replace_s1 << ":replace_s2: " << replace_s2 << ":min_val: " << min_val << "\n";
      min_diff = min_val;
      if (min_val == add_s1) {
        sum_s1 += elem;
        s1.push_back(elem);
      } else if (min_val == add_s2) {
        sum_s2 += elem;
        s2.push_back(elem);
      } else if (min_val == replace_s1) {
        s2.push_back(s1[idx_s1]);
        std::iter_swap(s1.begin() + idx_s1, s1.end() - 1);
        s1.pop_back();
        s1.push_back(elem);
        sum_s1 = sum_s1 - s2.back() + s1.back();
        sum_s2 += s2.back();
      } else {
        s1.push_back(s2[idx_s2]);
        std::iter_swap(s2.begin() + idx_s2, s2.end() - 1);
        s2.pop_back();
        s2.push_back(elem);
        sum_s2 = sum_s2 - s1.back() + s2.back();
        sum_s1 += s1.back();
      }
      /*
      cout << "sum_s1: " << sum_s1 << "  sum_s2: " << sum_s2 << "\n";
      for (int v : s1) cout << v << " ";
      cout << "\n";
      for (int v : s2) cout << v << " ";
      cout << "\n";*/
    }
    cout << min_diff << "\n";
  }
  return 0;
}
