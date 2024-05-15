#include<bits/stdc++.h>
using namespace std;

// Range Minimum Query 
struct RMQ {
  // length of the array
  int n;
  const int INT_MAX = numeric_limits<int>::max();
  // stores minimum in each range
  // each node is stored in the same manner as in heap with index
  // 2 * i and 2 * i + 1
  vector<int> rangeMin;
  RMQ(const vector<int>& array) {
    n = array.size();
    rangeMin.resize(n * 4);
    init(array, 0, n - 1, 1);
  }

  // whe node represents the array[left...right],
  // initialize the subtree rooted at node and return the minimum in this range
  int init(const vector<int>& array, int left, int right, int node) {
    if(left == right)
      return rangeMin[node] = array[left];
    int mid = (left + right) / 2;
    int leftMin = init(array, left, mid, node * 2);
    int rightMin = init(array, mid + 1, right, node * 2 + 1);
    return rangeMin[node] = min(leftMin, rightMin);
  }

  // Given node and its range array[nodeLeft..nodeRight], 
  // return the minimum value in union with array[left..right]
  int query(int left, int right, int node, int nodeLeft, int nodeRight) {
    // if there is no intersection, just ignore
    if(right < nodeLeft || nodeRight < left) return INT_MAX;
    // when node's range is completely inside the array[left..right]
    if(left <= nodeLeft && nodeRight <= right) 
      return rangeMin[node];
    int mid = (nodeLeft + nodeRight) / 2;
    return min(query(left, right, 2 * node, nodeLeft, mid),
              query(left, right, 2 * node + 1, mid + 1, nodeRight));
  }

  // When we have array[index] = newValue, we update the 
  // subtree rooted at node if impacted and return the minimum 
  // value represented by the range
  int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
    // if range is not influenced by the change, just ignore
    if(index < nodeLeft || nodeRight < index)
      return rangeMin[node];
    if(nodeLeft == nodeRight) return rangeMin[node] = newValue;
    int mid = (nodeLeft + nodeRight) / 2;
    return rangeMin[node] = min(
      update(index, newValue, 2 * node, nodeLeft, mid),
      update(index, newValue, 2 * node + 1, mid + 1, nodeRight)
    );
  }

  // calling interface method for user
  int query(int left, int right) {
    return query(left, right, 1, 0, n-1);
  }

  // calling interface method for update
  int update(int index, int newValue) {
    return update(index, newValue, 1, 0, n-1);
  }
};