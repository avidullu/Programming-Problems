#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
  public:
    double ComputeMedian(const map<int, int>& mp, int k) {
      const int sz = k / 2;
      const bool is_odd = k & 1;
      int count = 0;
      double value = 0;
      for (const auto& it : mp) {
        for (int i = 0; i < it.second; ++i) {
          if (is_odd && count == sz) return it.first;
          if (!is_odd && (count == sz || count == sz - 1)) {
            value += it.first;
          }
          count++;
        }
      }
      return value / 2;
    }

    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
      map<int, int> mp;
      vector<double> ret_val;
      for (int i = 0; i < k; ++i) mp[nums[i]]++;
      ret_val.push_back(ComputeMedian(mp, k));
      for (int i = k; i < nums.size(); ++i) {
        auto it = mp.find(nums[i - k]);
        if (it != mp.end()) {
          it->second--;
          if (it->second == 0) mp.erase(it);
        }
        ++mp[nums[i]];
        ret_val.push_back(ComputeMedian(mp, k));
      }
      return ret_val;
    }
};
