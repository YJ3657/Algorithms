#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long
#define arr array
#define INF 987654321

const int MAX_V = 100;
int V;
vector<pair<int, int>> adj[MAX_V];
// Union-Find Disjoint Set Data Structure
struct DisjointSet {
  vector<int> parent, rank;
  DisjointSet(int n) : parent(n), rank(n , 1) {
    for(int i = 0; i < n; i++) 
      parent[i] = i;
  }

  int find(int u) {
    if(u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }

  void merge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) return;
    if(rank[u] > rank[v]) swap(u, v);
    parent[u] = v;
    if(rank[u] == rank[v]) ++rank[v];
  }
};
// Class containing methods for getting MST
class MST {
  public: 
    // Kruskal's algorithm with union-find 
  int kruskal(vector<pair<int, int>>& selected) {
    int ret = 0;
    selected.clear();
    vector<pair<int, pair<int,int>>> edges;

    for(int u = 0; u < V; u++) {
      for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, cost = adj[u][i].second;
        edges.push_back(make_pair(cost, make_pair(u, v)));
      }
    }

    sort(edges.begin(), edges.end());

    DisjointSet sets(V);

    for(int i = 0; i < edges.size(); i++) {
      int cost = edges[i].first
      int u = edges[i].second.first, v  = edges[i].second.second;

      if(sets.find(u) == sets.find(v)) continue;

      sets.merge(u, v);
      ret += cost;
      selected.push_back(make_pair(u, v));
    }
    return ret;
  }

  // Prim algorithm without the use of heap queue
  int prim1(vector<pair<int, int>>& selected) {
    selected.clear();
    vector<bool> added(V, false);
    vector<int> minWeight(V, INF), parent(V, -1);

    int ret = 0;
    minWeight[0] = parent[0] = 0;
    
    for(int iter = 0; iter < V; iter++) {
      int u = -1;
      for(int v = 0; v < V; v++) 
        if(!added[v] && (u == -1 || minWeight[v] < minWeight[u]))
          u = v;
      
      if(parent[u] != u)
        selected.push_back(make_pair(parent[u], u));
      ret += minWeight[u];
      added[u] = true;
      
      for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, weight = adj[u][i].second;
        if(!added[v] && minWeight[v] > weight) {
          parent[v] = u;
          minWeight[v] = weight;
        }
      }
      return ret
    }
  }

  // Prim algorithm using the heap queue
  int prim2(vector<pair<int, int>>& selected) { 
    selected.clear();
    vector<bool> added(V, false);
    vector<int> parent(V, -1), minWeight(V, INF);
    priority_queue<pair<int, int>> pq;

    int ret = 0;
    parent[0] = 0;
    minWeight[0] = 0;
    pq.push(make_pair(0, 0));

    while(!pq.empty()) {
      int cost = pq.top().first;
      int u = pq.top().second;
      pq.pop();

      if(parent[u] != u)
        selected.push_back(make_pair(parent[u], u));
      ret += minWeight[u];
      added[u] = true;

      for(int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first, weight = adj[u][i].second;
        if(!added[v] && minWeight[v] > weight) {
          parent[v] = u;
          minWeight[v] = weight;
          pq.push(make_pair(weight, v));
        }
      }
    }
    return ret;
  }
}