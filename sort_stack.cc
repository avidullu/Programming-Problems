// Sort a stach using another stack without recursion
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

int main() {
  stack<int> in;
  int v = 0;
  while (1) {
    cin >> v;
    if (v == -1) break;
    in.push(v);
  }
  stack<int> tmp;
  for (int i = 2; i <= in.size(); ++i) {
    for (int j = 0; j < i; ++j) {
      tmp.push(in.top());
      in.pop();
    }
    int tmp_top = tmp.top();
    tmp.pop();
    while (!tmp.empty()) {
      if (tmp.top() < tmp_top) {
        in.push(tmp.top());
      } else {
        in.push(tmp_top);
        tmp_top = tmp.top();
      }
      tmp.pop();
    }
    in.push(tmp_top);
  }
  while (!in.empty()) {
    cout << in.top() << "  ";
    in.pop();
  }
  cout << "\n";
  return 0;
}
