from collections import *
from typing import *
from sys import *
import heapq

# Assume that number of vertices and graph are given
V = 13
INF = 987654321

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
      
            
                

