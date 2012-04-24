// Program to find the maximum sum submatrix in a given NxN matrix.
// Time: O(n^3)
// Space: O(n^2)

#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

int FindMaxAndDistance(int* arr, int n) {
  int max_sum = arr[0], run_sum = arr[0];
  for (int i = 1; i < n; ++i) {
    run_sum = max(run_sum + arr[i], arr[i]);
    max_sum = max(max_sum, run_sum);
  }
  return max_sum;
}

int main() {
  int n;
  cin >> n;
  int a[n][n];
  int tmp_arr[n][n];
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> a[i][j];
      tmp_arr[i][j] = a[i][j];
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      tmp_arr[i][j] += tmp_arr[i][j-1];
    }
  }
  int max_sum = INT_MIN;
  for (int i = 0; i < n; ++i) {
    for (int  j = i; j < n; ++j) {
      int tmp[n];
      if (i == j) {
        for (int k = 0; k < n; ++k) {
          tmp[k] = a[k][i];
        }
      } else {
        for (int k = 0; k < n; ++k) {
          tmp[k] = tmp_arr[k][j] - tmp_arr[k][i] + a[k][i];
        }
      }
      max_sum = max(max_sum, FindMaxAndDistance(tmp, n));
    }
  }
  cout << max_sum << endl;
  return 0;
}
