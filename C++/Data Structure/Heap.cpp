#include<bits/stdc++.h>
#define INF 987654321
using namespace std;

class HeapPQ {
  public:
    vector<int> heap;
  public:
    HeapPQ(vector<int> a) {
      this.heap = a;
      this->build_max_heap(a);
    }

    int left(int i) {
      return 2*i;
    }

    int right(int i) {
      return 2*i + 1;
    }

    int parent(int i) {
      return floor(i / 2);
    }

    void max_heapify(vector<int> &a, int i) {
      int l = left(i), r = right(i), largest = i;
      
      if(l < a.size() and a[l] > a[largest]) {
        largest = l;
      }
      if(r < a.size() and a[r] > a[largest]) {
        largest = r;
      }
      
      if(largest == i) return;
      swap(a[i], a[largest]);
      max_heapify(a, largest);
      return;
    }

    void build_max_heap(vector<int> &a) {
      for(int i = floor(a.size() / 2), i > 0; i--) {
        max_heapify(a, i);
      }
      return;
    }

    int heap_maximum(vector<int>& a) {
      return a[1];
    }    

    int heap_extract_max(vector<int>& a) {
      if(a.size() < 1) return;
      int max = a[0];
      a[0] = a.back();
      a.pop_back();
      max_heapify(a, 0);
      return max;
    }

    void heap_increase_key(vector<int>& a, int i, int key) {
      if(key < A[i]) return;
      a[i] = key;
      while(i > 0 && (a[parent(i)] < a[i])) {
        swap(a[i], a[parent(i)]);
        i = parent(i);
      }
      return;
    } 

    void max_heap_insert(vector<int>& a, int key) {
      a.push_back(-INF);
      heap_increase_key(a, a.size() - 1, key);
      return;
    }
}