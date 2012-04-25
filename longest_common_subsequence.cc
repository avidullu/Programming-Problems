// Longest common subsequence. This is a test modification to test commits.
// Time: O(n^2)
// Space: O(n^2)

#include<iostream>
#include<algorithm>

using namespace std;

int main() {
  string L1, L2;
  cin >> L1 >> L2;
  int arr[L1.size() + 1][L2.size() + 1];
  for (int i = 0; i <= L2.size(); ++i) {
    arr[0][i] = 0;
  }
  for (int i = 0; i <= L1.size(); ++i) {
    arr[i][0] = 0;
  }
  for (int i = 1; i <= L1.size(); ++i) {
    for (int j = 1; j <= L2.size(); ++j) {
      arr[i][j] = (L1[i] == L2[j]) ? arr[i-1][j-1] + 1 : max(arr[i-1][j], arr[i][j-1]);
    }
  }
  cout << arr[L1.size()][L2.size()] << endl;
}
