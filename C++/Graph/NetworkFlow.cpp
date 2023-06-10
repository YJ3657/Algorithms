#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long
#define arr array
#define INF 987654321

const int MAX_V = 100;
int V;


class NetworkFlow {
  
  // capacity[u][v] = the amount that can flow between the nodes 'u' and 'v'
  // flow[u][v] = the amount of actual flow between the nodes 'u' and 'v' (negative if in reverse direction)
  int capcity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
  
  // Edmonds-Karp algorithm for implementing Ford-Fulkerson algorithm 
  // Calculate all flow[][] and return the total flow
  int edmondsKarp(int source, int sink) {
    // Resetting flow to be all 0s
    memset(flow, 0, sizeof(flow));
    int totalFlow = 0;

    while(True) {
      // Using BFS to find augmenting paths
      vector<int> parent(MAX_V, -1);
      queue<int> q;
      parent[source] = source;
      q.push(source);
      while(!q.empty() && parent[sink] == -1) {
        int here = q.front(); q.pop();
        for(int there = 0; there < V; there++) {
          // Check for the residual capacity and add accordingly
          if(capacity[here][there] - flow[here][there] > 0 && 
             parent[there] == -1) {
              q.push(there);
              parent[there] = here;
             }
        }
      }
      // When there is no more augmenting path, terminate
      if(parent[sink] == -1) break;
      // We find the minimum possible capacity in our augmenting path
      int amount = INF;
      for(int p = sink; p != source; p = parent[p]) 
        amount = min(capacity[oarent[p]][p] - flow[parent[p]][p], amount);
      
      // Sending the flow through the augmenting path
      for(int p = sink; p != source; p = parent[p]) {
        flow[parent[p]][p] += amount;
        flow[p][parent[p]] -= amount;
      }
      totalFlow += amount;
    }
    return totalFlow;
  }

  // Method for Bipartite Matching for unweighted graph using DFS the returns the maximum 
  // cardinality bipartite matching (MCBM) (This will also be included in a separate file for matching)
  // Can think of it as a simplified network flow algorithm for weighted graph with all equal 
  // weights
  // Corresponding number of vertices for A and B bipartite sets
  int n, m;
  bool adj[n][m];
  vector<int> aMatch, bMatch;
  vector<bool> visited;
  
  bool dfs(int a) {
    if(visited[a]): return false;
    
    visited[a] = true;
    
    for(int b = 0; b < m; b++) 
      if(adj[a][b]) 
        if(bMatch[b] == -1 || dfs(bMatch[b])) {
          aMatch[a] = b;
          bMatch[b] = a;
          return true;
        }
    return false;
  }

int bipartiteMatch(void) {
  // Initially, we don't have any matches in our bipartite matching
  aMatch = vector<int>(n, - 1);
  bMatch = vector<int>(m, -1);
  int size = 0;
  for(int start = 0; start < n; start++) {
    visited = vector<bool>(n, false);
    if(dfs(start)): ++size;
  }
  return size;
}
}