#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long
#define arr array
#define INF 987654321

class ShortestPath {

  public:
    int V;
    // Dijkstra's method that returns the shortest distance from one source node to all other nodes
    vector<int> dijkstra1(int src) {
      vector<int> dist(V, INF);
      vector<pair<int, int>> adj[V];
      dist[src] = 0;
      // This is Min Heap Queue
      priority_queue<pair<int, int>> pq;
      pq.push(make_pair(0, src));
      while(!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if(dist[here] < cost) continue;

        for(int i = 0; i < adj[here].size(); i++) {
          int there = adj[here][i].second;
          int nextDist = cost + adj[here][i].first;
          if(nextDist < dist[there]) {
            dist[there] = nextDist;
            pq.push(make_pair(-nextDist, there));
          }
        }
      }
      return dist;
    }

    // Dijkstra's method with destination node given that returns the 
    // shortest distance to that destination
    int dijkstra2(int src, int dest) {
      vector<int> dist(V, INF);
      vector<pair<int, int>> adj[V];
      dist[src] = 0;
      priority_queue<pair<int, int>> pq;
      pq.push(make_pair(0, src));
      while(!pq.empty()) {
        int cost = -pq.top().first;
        int here = pq.top().second;
        pq.pop();

        if(cost > dist[here]) continue;

        for(int i = 0; i < adj[here].size(); i++) {
          int there = adj[here][i].second;
          int nextDist = cost + adj[here][i].first;
          // very first one will be the shortest length
          if there == dest: return nextDist;

          if nextDist < dist[there] {
            dist[there] = nextDist;
            pq.push(make_pair(-nextDist, there));
          }
        }
      }
    return -1;
    }

    // Dijkstra's method that does not use heap queue
    vector<int> dijkstra3(int src) {
      vector<int> dist(V, INF);
      vector<pair<int, int>> adj[V];
      vector<bool> visited(V, false);
      dist[src] = 0; visited[src] = false;
      while(true) {
        int closest = INF, here;
        for(int i = 0; i < V; i++) {
          if(dist[i] < closest && !visited[i]) {
            here = i;
            closest = dist[i];
          }
          if(closest == INF) break;
          
          visited[here] = true;
          for(int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            if(visited[there]) continue;
            int nextDist = dist[here] + adj[here][i].second;
            dist[there] = min(dist[there], nextDist);
          }
        }
        return dist;
      }
    }

    /*
    Bellman-Ford Method with adjacency list
    Works even with negative edge weights
    We assume that node's value is in range of 0 to size - 1, inclusive
    */
    vector<int> bellman_ford(int src) {
      vector<int> upper(V, INF)
      vector<pair<int, int>> adj[V];
      upper[src] = 0;
      bool updated = False;
      for(int i = 0; i < V; i++) {
        updated = False;
        for(int node = 0; node < V; node++) {
          for(int i = 0; i < adj[node].size(); i++) {
            int next = adj[node][i].first;
            int cost = adj[node][i].second;
            if(upper[next] > (upper[node] + cost)) {
              updated = True;
              upper[next] = upper[node] + cost;
            }
          }
        }
        if(!updated) break;
      }
      // If updated after V iterations, then it means that there is a negative cycle
      // And we return an empty array 
      if(updated) upper.clear();
      return upper;
    } 

    // Warshall-Floyd method with adjacency matrix
    void floyd1() {
      int adj[V][V];
      for(int i = 0; i < V; i++) adj[i][i] = 0;

      for(int transit = 0; transit < V; transit++) {
        for(int node1 = 0; node1 < V; node1++) {
          for(int node2 = 0; node2 < V; node2++) {
            adj[node1][node2] = min(adj[node1][node2], 
            adj[node1][transit] + adj[transit][node2]);
          }
        }
      }
    }
  
    // Warshall-Floyd method with reconstructing the shortest path between two nodes
    int via[V][V];
    int adj[V][V];
    void floyd2() {
      for(int i = 0; i < V; i++) adj[i][i] = 0;
      memset(via, -1, sizeof(via))
      for(int transit = 0; transit < V; transit++) {
        for(int node1 = 0; node1 < V; node1++) {
          for(int node2 = 0; node2 < V; node2++) {
            if (adj[node1][node2] > (adj[node1][transit] + adj[transit][node2])) {
              via[node1][node2] = transit;
              adj[node1][node2] = adj[node1][transit] + adj[transit][node2];
            }
          }
        }
      }
    }

    void reconstruct(int u, int v, vector<int>& path) {
      if(via[u][v] == -1) {
        path.push_back(u);
        if(u!=v) path.push_back(v);
      }

      else {
        reconstruct(u, via[u][v], path);
        path.pop_back();
        reconstruct(via[u][v], v, path);
      }
    }
  }
