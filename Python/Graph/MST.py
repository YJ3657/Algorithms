from collections import *
from typing import *
from sys import *
import heapq

# Assume that number of vertices and graph are given
V = 13
graph = defaultdict(list)

# Union-Find Disjoint Set Data Structure
class DisjointSet(object):
  def __init__(self, n: int) -> None:
    self.parent, self.rank = [0] * n, [1] * n
    
    for i in range(n):
      self.parent[i] = i
    return None
  
  def find(self, u: int):
    if (u == self.parent[u]): return u
    self.parent[u] = self.find(self.parent[u])
    return self.parent[u]
  
  def merge(self, u: int, v: int) -> None:
    u, v = self.find(u), self.find(v)
    if(u == v): return None
    if(self.rank[u] > self.rank[v]):
      u, v = v, u
    self.parent[u] = v
    if(self.rank[u] == self.rank[v]): 
      self.rank[v] += 1
    return None

class MST(object):
  
  # Kruskal Algorithm with Union-Find 
  def kruskal(self, selected: List[tuple]) -> int:
    ret = 0
    selected = []
    edges = []

    for u in range(V):
      for (v, cost) in graph[u]:
        edges.append((cost, u, v))

    edges.sort()

    sets = DisjointSet()

    for i in range(len(edges)):
      cost, u, v = edges[-1][0], edges[-1][1], edges[-1][2]

      if(sets.find(u) == sets.find(v)): continue
      
      sets.merge(u, v)
      ret += cost
      selected.append((u, v))
    return ret
  
  # Prim's algorithm without heap queue
  def prim1(self, selected: List[tuple]) -> int:
    selected = []
    added = [False] * V
    minWeight, parent = [maxsize] * V, [-1] * V

    minWeight[0] = parent[0] = 0
    ret = 0

    for iteration in range(V):
      u = -1
      for v in range(V):
        if not(added[v]) and ((u == -1) or minWeight[v] > minWeight[u]):
          u = v
      
      if(parent[u] != u): selected.append(u)
      ret += minWeight[u]
      added[u] = True

      for (v, cost) in graph[u]:
        if(not(added[v]) and (cost > minWeight[v])):
          minWeight[v] = cost
          parent[v] = u
    return ret

  # Prim's algorithm with heap queue
  def prim2(self, selected: List[tuple]) -> int:
    selected = []
    added = [False] * V
    minWeight, parent = [maxsize] * V, [-1] * V

    minWeight[0] = parent[0] = 0
    ret = 0
    hq = [(0,0)]
    while(hq):
      weight, u = heapq.heappop(hq)
      
      if(u != parent[u]): selected.append(u)
      ret += weight
      added[u] = True

      for (v, cost) in graph[u]:
        if(not(added[v]) and (minWeight[v] > cost)):
          parent[v] = u
          minWeight[v] = cost
          hq.heappush((cost, v))
    
    return ret