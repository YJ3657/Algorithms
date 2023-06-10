from collections import *
from typing import *
from sys import *
import heapq

# Assume that number of vertices and graph are given
V = 13
INF = 987654321
graph = defaultdict(list)
n, m = 13, 13
visited = bMatch = aMatch = None

class NetworkFlow:
  # Edmonds-Karp algorithm for implementing Ford-Fulkerson algorithm 
  # Calculate all flows and return the total flow
  # capacity of edges is given as parameter 
  def edmondsKarp(self, capacity: List[List[int]], source: int, sink: int) -> int:
    flow = [[0] * V for _ in range(V)]
    totalFlow = 0

    while(True):
      parent = [-1 * V]
      q = deque([source])
      parent[source] = source
      while(q and parent[sink] == -1):
        here = q.popleft()
        for there in range(V):
            if(capacity[here][there] - flow[here][there] > 0 and parent[there] == -1):
                q.append(there)
                parent[there] = here
      # Terminate the infinite while loop if there is no more 
      # augmenting path
      if parent[sink] == -1: break
      amount = INF
      p = sink
      while p != source:
        amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount)
        p = parent[p]
      p = sink
      while p != source:
        flow[parent[p]][p] += amount
        flow[p][parent[p]] -= amount
        p = parent[p]
      totalFlow += amount
    
    return totalFlow
    
  # Method for Bipartite Matching for unweighted graph using DFS the returns the maximum 
  # cardinality bipartite matching (MCBM) (This will also be included in a separate file for matching)
  # Can think of it as a simplified network flow algorithm for weighted graph with all equal 
  # weights
  def dfs(self, a: int) -> bool:
    if(visited[a]): return False
    visited[a] = True
    for b in range(m):
      if b in graph[a]:
        if (bMatch[b] == -1) or (self.dfs(bMatch[b])):
          aMatch[a] = b
          bMatch[b] = a
          return True
    return False
  
  def bipartiteMatch(self) -> int:
    size = 0
    aMatch, bMatch = [-1] * n, [-1] * m
    visited = [False] * n
    for start in range(n):
      if self.dfs(start): size += 1
    return start