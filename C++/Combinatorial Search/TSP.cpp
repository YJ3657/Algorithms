#include<bits/stdc++.h>
using namespace std;
#include<"../Graph/MST.cpp"
// Some heuristics applied to the TSP problem.

const double INF = 1e200;
const int MAX = 30;
int n; // Count of cities
double dist[MAX][MAX]; // Array to store the distance between the adjacent cities
// Best solution found so far
double best;

// path: path that has been currently built
// visited: visit status of every city
// currentLength: length of the path visited so far
// Try visiting the rest of cities and update the best solution
void naive_search(vector<int>& path, vector<bool>& visited, double currentLength) {
  int here = path.back();

  // Base case: if visited every city, return to the 0th city and terminate
  if(path.size() == n) {
    best = min(best, currentLength + dist[here][0]);
    return;
  }
  // Try every other city that has not been visited
  for(int next = 0; next < n; next++) {
    if(visited[next]) continue;
    path.push_back(next);
    visited[next] = true;
    // Complete the remaining route by the recursive call
    naive_search(path, visited, currentLength + dist[here][next]);
    visited[next] = false;
    path.pop_back();
  }
}

// Need to find the shortest edge among the adjacent ones for each city.
double minEdge[MAX];

// The simplest type of heuristic
double simpleHeuristic(vector<bool>& visited) {
  double ret = minEdge[0]; // Edge to use to return to the starting point.
  for(int i = 0; i < n; i++) {
    if(!visited[i])
      ret += minEdge[i];
  }
  return ret;
}

void simple_heuristic_search(vector<int>& path, vector<bool>& visited, double currentLength) {
  int here = path.back();
  // Pruning using the simple heuristic
  if(best <= currentLength + simpleHeuristic(visited)) return;
  // Base case: if visited every city, return to the 0th city and terminate
  if(path.size() == n) {
    best = min(best, currentLength + dist[here][0]);
    return;
  }
  // Try every other city that has not been visited
  for(int next = 0; next < n; next++) {
    if(visited[next]) continue;
    path.push_back(next);
    visited[next] = true;
    // Complete the remaining route by the recursive call
    naive_search(path, visited, currentLength + dist[here][next]);
    visited[next] = false;
    path.pop_back();
  }
}

// Sort the nearest cities for each city
vector<int> nearest[MAX];
void nearest_heuristic_search(vector<int>& path, vector<bool>& visited, double currentLength) {
  int here = path.back();
  // Base case: if visited every city, return to the 0th city and terminate
  if(path.size() == n) {
    best = min(best, currentLength + dist[here][0]);
    return;
  }
  // Try every other city that has not been visited
  for(int i = 0; i < nearest[here].size(); i++) {
    int next = nearest[here][i];
    if(visited[next]) continue;
    path.push_back(next);
    visited[next] = true;
    // Complete the remaining route by the recursive call
    naive_search(path, visited, currentLength + dist[here][next]);
    visited[next] = false;
    path.pop_back();
  }
}

// Check if the distance gets shorter by swapping the order of two
// middle nodes in the path's last 4 nodes
bool pathSwapPruning(const vector<int>& path) {
  if(path.size() < 4) return false;
  int p = path[path.size() - 4];
  int a = path[path.size() - 3];
  int b = path[path.size() - 2];
  int q = path[path.size() - 1];
  return dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q];
}

// More general and better version of the pathSwapPruning
// where except the current and the starting nodes,
// we flip every subpath and see if the distance gets shorter. 
bool pathReversePruning(const vector<int>& path) {
  if(path.size() < 4) return false;
  int b = path[path.size() - 2];
  int q = path[path.size() - 1];

  for(int i = 0; i + 3 < path.size(); i++) {
    int p = path[i];
    int a = path[i + 1];
    // Try swapping [..., p, a, ..., b, q] to [..., p, b, ..., a, q]
    if(dist[p][a] + dist[b][q] > dist[p][b] + dist[a][q])
      return true;
  }
  return false;
}

// Sorted edges by the distance
vector<pair<double, pair<int, int>>> edges;
// MSTheuristic that finds the MST that includes the starting point, here, and unvisited nodes
double mstHeuristic(int here, const vector<bool>& visited) {
  // Kruskal's MST
  DisjointSet sets(n);
  double taken = 0;
  for(int i = 0; i <edges.size(); i++) {
    int a = edges[i].second.first, b = edges[i].second.second;
    if(a != 0 && a != here && visited[a]) continue;
    if(b != 0 && b != here && visited[b]) continue;
    if(sets.merge(a, b))
      taken += edges[i].first;
  }
  return taken;
}

// if the remaining city count is less than CACHED_DEPTH, switch to dp
const int CACHED_DEPTH = 5;
// dp(here, visited) = cache[here][남은 도시의 수][visited]
map<int, double> cache[MAX][CACHED_DEPTH + 1];
// here: current position
// visited: visit status
// return the rest of remaining cities and reutnr the shortest distance to the origin back
double dp(int here, int visited) {
  // Basis: return to origin when there are no more cities 
  if(visited == (1 << n) - 1) return dist[here][0];
  // Memoization
  int remaining = n - __builtin_popcount(visited);
  double& ret = cache[here][remaining][visited];
  if(ret > 0) return ret;
  ret = INF;
  // iterate through next cities 
  for(int next = 0; next < n; next++) {
    if(visited & (1 << next)) continue;
    ret = min(ret, dp(next, visited + (1 << next)) + dist[here][next]);
  }
  return ret;
}