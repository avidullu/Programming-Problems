#include <iostream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

vector<int> BuildLookupTable(const string& needle) {
  vector<int> ret_val;
  ret_val.resize(needle.length());
  size_t pos = 2, prefix_pos = 0;
  ret_val[0] = -1;
  ret_val[1] = 0;
  while (pos < needle.length()) {
    if (needle.at(pos - 1) == needle.at(prefix_pos)) {
      ret_val[pos++] = ++prefix_pos;
    } else if (prefix_pos > 0) {
      prefix_pos = ret_val[prefix_pos];
    } else {
      ret_val[pos++] = 0;
    }
  }
  return ret_val;
}

string FindNeedleInHaystackUsingKMP(const string& needle,
                                    const string& haystack) {
  vector<int> lookup_table = BuildLookupTable(needle);
  size_t haystack_index = 0;
  size_t needle_index = 0;
  while (haystack_index + needle_index < haystack.length()) {
    if (haystack.at(haystack_index + needle_index)
        == needle.at(needle_index)) {
      ++needle_index;
      if (needle_index == needle.length()) return "Found.";
    } else {
      haystack_index = haystack_index + needle_index
          - lookup_table[needle_index];
      if (lookup_table[needle_index] == -1) {
        needle_index = 0;
      } else {
        needle_index = lookup_table[needle_index];
      }
    }
  }
  return "Not found the needle.";
}

int main() {
  string needle, haystack;
  cout << "Enter the needle: ";
  getline(std::cin, needle);
  cout << "Enter the haystack: ";
  getline(std::cin, haystack);
  cout << FindNeedleInHaystackUsingKMP(needle, haystack) << "\n";
  char* ret_val = strstr(haystack.c_str(), needle.c_str());
  if (ret_val == NULL) {
    cout << "(Verifier) : Not Found\n";
  } else {
    cout << "(Verifier) : Found\n";
  }
}
