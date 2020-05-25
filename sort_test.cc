// You need C++11 for this to compile!
// You should be having it, so compile this with 'g++ -std=c++11 filename.cc'
// ./a.out N1 N2
// where N1 < N2 and the test will run for array sizes of N1, N1 + 1, ... N2
// and produce result for all the iterations.

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <cassert>
#include <cstdlib>
#include <climits>

void CocktailSort(std::vector<int>& num, int start, int end) {
  const int i_end = end - 1;
  bool swapped = false;
  do {
    for (int i = start; i <= i_end; ++i) {
      if (num[i] > num[i + 1]) {
        std::swap(num[i], num[i + 1]);
        swapped = true;
      }
    }
    if (!swapped) break;
    swapped = false;
    for (int i = end - 1; i >= start; --i) {
      if (num[i] > num[i + 1]) {
        std::swap(num[i], num[i + 1]);
        swapped = true;
      }
    }
  } while (swapped);
}

// This sort works by following a simple invariant. Every time the inner
// for loop completes, we place the min and max elements of the iterated
// subarray at the two ends. We need to do this exactly n / 2 times,
// since with each iteration we place 2 elements correctly.
// I saw the animation on wiki page of Cocktail sort and without reading
// the pseudo code thought of this algorithm and 'assumed' this should be
// Cocktail sort. Well, it is not. But for the ~10k runs of comparison, this
// out performs Cocktail sort, so will use this in QSort.
// Above Cocktail is for demo!
void MyBadSort(std::vector<int>& num, const int start, const int end) {
  const int nelem = end - start + 1;
  if (nelem == 1) return;
  if (nelem == 2) {
    if (num[start] > num[end]) std::swap(num[start], num[end]);
    return;
  }
  int found = start;
  const int n_iter = nelem / 2;
  for (int ix = 0; ix < n_iter; ++ix) {
    const int loc = end - ix;
    int min = num[found];
    int max = num[loc];
    if (min > max) {
      std::swap(min, max);
      std::swap(num[found], num[loc]);
    }
    const int upto = end - ix;
    for (int i = found + 1; i < upto; ++i) {
      if (num[i] < min) {
        min = num[i];
        std::swap(num[found], num[i]);
      }
      if (num[i] > max) {
        max = num[i];
        std::swap(num[loc], num[i]);
      }
    }
    ++found;
  }
}

void MyQSortNaive(std::vector<int>& num, const int start, const int end) {
  const int nelem = end - start + 1;
  if (nelem == 1) return;
  if (nelem == 2) {
    if (num[start] > num[end]) std::swap(num[start], num[end]);
    return;
  }
  const int pivot = num[start];
  int pos = start;
  for (int i = start; i <= end; ++i) {
    if (num[i] < pivot) {
      std::swap(num[pos], num[i]);
      ++pos;
    }
  }
  if (pos > start) MyQSortNaive(num, start, pos - 1);
  for (int i = pos; i <= end; ++i) {
    if (num[i] == pivot) {
      std::swap(num[pos], num[i]);
      ++pos;
    }
  }
  if (pos < end) MyQSortNaive(num, pos, end);
}

void MyQSort(std::vector<int>& num, const int start, const int end) {
  const int nelem = end - start + 1;
  if (nelem == 1) return;
  if (nelem == 2) {
    if (num[start] > num[end]) std::swap(num[start], num[end]);
    return;
  }
  if (nelem == 3) {
    if (num[start] > num[start + 1]) std::swap(num[start], num[start + 1]);
    if (num[start + 1] > num[end]) std::swap(num[start + 1], num[end]);
    if (num[start] > num[start + 1]) std::swap(num[start], num[start + 1]);
    return;
  }
  if (nelem <= 10) {
    MyBadSort(num, start, end);
    return;
  }
  const int pivot = num[start];
  int pos = start;
  for (int i = start; i <= end; ++i) {
    if (num[i] < pivot) {
      std::swap(num[pos], num[i]);
      ++pos;
    }
  }
  if (pos > start) MyQSort(num, start, pos - 1);
  for (int i = pos; i <= end; ++i) {
    if (num[i] == pivot) {
      std::swap(num[pos], num[i]);
      ++pos;
    }
  }
  if (pos < end) MyQSort(num, pos, end);
}

int main(int argc, char** argv) {
  assert(argc == 3);
  const int MOD_VALUE = 1000;  // INT_MAX
  unsigned long long int std_qsort = 0, my_qsort_naive = 0, my_qsort = 0;
  for (int run = std::stoi(argv[1]); run <= std::stoi(argv[2]); ++run) {
    unsigned seed1 = std::chrono::system_clock::now()
        .time_since_epoch().count();
    std::mt19937 rnd(seed1 + run * 1000);
    int N = run;
    std::cout << "\n\nRunning comparison with " << run
              << " elements to sort\n";
    std::vector<int> num;
    num.reserve(N);

    // C++ std::sort
    num.clear();
    for (int i = 0; i < N; ++i) num.push_back(rnd() % MOD_VALUE);
    std::shuffle(num.begin(), num.end(), rnd);
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(num.begin(), num.end());
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast
      <std::chrono::microseconds>(end - start);
    assert(std::is_sorted(num.begin(), num.end()));
    std_qsort += elapsed.count();
    // std::cout << "Time spent in std::sort: " << elapsed.count() << "\n";

    // My QSort implementation without the Cocktail support
    num.clear();
    for (int i = 0; i < N; ++i) num.push_back(rnd() % MOD_VALUE);
    std::shuffle(num.begin(), num.end(), rnd);
    start = std::chrono::high_resolution_clock::now();
    // qsort(&num[0], num.size(), sizeof(num[0]), cmp);
    MyQSortNaive(num, 0, num.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast
      <std::chrono::microseconds>(end - start);
    assert(std::is_sorted(num.begin(), num.end()));
    // std::cout << "Time spent in Naive Qsort: " << elapsed.count() << "\n";
    my_qsort_naive += elapsed.count();

    // My QSort with Cocktail support
    num.clear();
    for (int i = 0; i < N; ++i) num.push_back(rnd() % MOD_VALUE);
    std::shuffle(num.begin(), num.end(), rnd);
    start = std::chrono::high_resolution_clock::now();
    MyQSort(num, 0, num.size() - 1);
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast
      <std::chrono::microseconds>(end - start);
    assert(std::is_sorted(num.begin(), num.end()));
    // std::cout << "Time spent in MyQsort with sorter: " << elapsed.count() << "\n";
    my_qsort += elapsed.count();
  }
  std::cout << "\n\n";
  std::cout << "Total time taken for std::sort: " << std_qsort << "\n";
  std::cout << "Total time taken for naive myqsort: " << my_qsort_naive << "\n";
  std::cout << "Total time taken for myqsort: " << my_qsort << "\n";
  return 0;
}
