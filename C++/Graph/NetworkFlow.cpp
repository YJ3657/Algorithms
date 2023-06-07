#include<bits/stdc++.h>

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
}