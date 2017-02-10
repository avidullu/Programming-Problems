#include<list>
#include<iostream>
using namespace std;
int main() {
  int n;
  cin >> n;
  list<int> l1, l2, l3;
  int tmp;
  for (int i = 0; i< n; ++i) {
    cin >> tmp;
    l1.push_back(tmp);
  }
  cin >> n;
  for (int i = 0; i< n; ++i) {
    cin >> tmp;
    l2.push_back(tmp);
  }
  while (!l1.empty() || !l2.empty()) {
    if (!l1.empty() && !l2.empty()) {
      if (l1.front() < l2.front()) {
        l3.push_back(l1.front());
        l1.pop_front();
      } else {
        l3.push_back(l2.front());
        l2.pop_front();
      }
      continue;
    }
    if (!l1.empty()) {
      l3.push_back(l1.front());
      l1.pop_front();
      continue;
    }
    if (!l2.empty()) {
      l3.push_back(l2.front());
      l2.pop_front();
    }
  }
  for (int l : l3) cout << l << "  ";
  cout << "\n";
  return 0;
}
