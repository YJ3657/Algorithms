#include<bits/stdc++.h>
#define INF 987654321
using namespace std;

// Fenwick implementation for the prefix sum of the array A[]
struct FenwickTree {
  vector<int> tree;
  FenwickTree(int n) : tree(n + 1) {}
  // Calculating the prefix sum A[0..pos]
  int sum(int pos) {
    // Assume that index starts at 1
    ++pos;
    int ret = 0;
    while(pos > 0) {
      ret += tree[pos];
      // erasing the least significant 1 bit to get to next range
      pos &= pos - 1;
    }
    return ret;
  }

  // Adding val to A[pos]
  void add(int pos, int val) {
    ++pos;
    while(pos < tree.size()) {
      tree[pos] += val;
      pos += (pos & -pos);
    }
  }
};