// Program to find maximum sub contiguous sub-array
// Time: O(n)
// Space: O(1)

#include<algorithm>
#include<iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int max_sum = 0, run_sum = 0;
  for (int i = 0, t = -1; i < n; ++i) {
    cin >> t;
    run_sum = max(run_sum + t, t);
    max_sum = max(run_sum, max_sum);
  }
  cout << max_sum << endl;
  return 0;
}
