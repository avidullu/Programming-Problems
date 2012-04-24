// Minimum steps to jump off an array
// Time: O(n)
// Space: O(1)

#include<iostream>

using namespace std;

int main() {
  int n;
  cin >> n;
  int a[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int jumps = 1;
  int pos = 0;
  while (pos < n) {
    int steps = a[pos];
    for (int j = pos; steps--; ++j) {
      int max_jump = a[j] + j;
      if (max_jump > pos) {
        pos = max_jump;
      }
      if (max_jump >= n) {
        break;
      }
    }
    ++jumps;
  }
  cout << jumps << endl;
  return 0;
}
