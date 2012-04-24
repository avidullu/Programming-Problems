#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

void PrintParanthesisRecursive(vector<char>& arr, int n, int open, int closed) {
  if (open == n && closed == n) {
    n<<=1;
    for (int i = 0; i < n; ++i) {
      printf("%c", arr[i]);
    }
    printf("\n");
    return;
  }
  if (open < n) {
    arr.push_back('(');
    PrintParanthesisRecursive(arr, n, open + 1, closed);
    arr.erase(arr.end() - 1);
  }
  if (closed + 1 <= open) {
    arr.push_back(')');
    PrintParanthesisRecursive(arr, n, open, closed + 1);
    arr.erase(arr.end() - 1);
  }
}

int main() {
  int n;
  cin >> n;
  vector<char> arr;
  PrintParanthesisRecursive(arr, n, 0, 0);
}
