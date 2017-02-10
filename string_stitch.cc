#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int N;
    cin >> N;
    vector<vector<int>> adj;
    adj.resize(N);
    vector<string> strs;
    strs.resize(N);
    unordered_map<char, vector<int>> pre;
    for (int i = 0; i < N; ++i) {
      cin >> strs[i];
      pre[strs[i][0]].push_back(i);
    }
    for (int i = 0; i < N; ++i) {
      const string& str = strs[i];
      auto it = pre.find(str[str.size() - 1]);
      if (it != pre.end()) {
        adj[i] = it->second;
      }
    }
    bool all_visited = false;
    for (int head = 0; head < N && !all_visited; ++head) {
      stack<int> nodes;
      nodes.push(head);
      vector<int> visit(N, 0);
      unordered_set<int> visited;
      while (!nodes.empty()) {
        int node = nodes.top();
        if (visit[node] == 1) {
          visit[node] = 2;
          nodes.pop();
          visited.insert(node);
          continue;
        }
        visit[node] = 1;
        for (int v : adj[node]) {
          if (visit[v] == 0) nodes.push(v);
        }
      }
      all_visited = visited.size() == N;
    }
    if (all_visited) {
      cout << "Head to tail ordering is possible.\n";
    } else {
      cout << "Head to tail ordering is not possible.\n";
    }
  }
  return 0;
}
