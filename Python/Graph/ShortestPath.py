from collections import *
from typing import *
from sys import *
import heapq
# Assume that number of vertices and graph are given
V = 13
graph = defaultdict(list)
INF = 987654321

class ShortestPath(object):
   # Dijkstra's method that returns the shortest distance from one source node to all other nodes
   def dijkstra1(self, src: int) -> dict:  
      # Min-heap-queue for taking out the smallest item 
      hq = [(0, src)]
      # Distance variable to store all distances
      dist = defaultdict(INF)

      while hq:
        distance, node1 = heapq.heappop(hq)

        if distance > dist[node1]: continue
        # If node1 is not yet in the dist, then the path is the shortest one
        if node1 not in dist:
           dist[node1] = distance
           for node2, weight in graph[node1]:
              heapq.heappush((dist + weight, node2))
      
      return dist
      
    # Dijkstra's method with destination node given that returns the 
    # shortest distance to that destination
   def dijkstra2(self, edges: List[List[int]], src: int, dest: int) -> int:  
      # Min-heap-queue for taking out the smallest item 
      hq = [(0, src)]
      # Distance variable to store all distances
      dist = defaultdict(INF)

      while hq:
        distance, node1 = heapq.heappop(hq)
        if node1 == dest:
          return distance
        if distance > dist[node1]: continue
        elif node1 not in dist:
           dist[node1] = distance
           for node2, weight in graph[node1]:
              heapq.heappush((dist + weight, node2))

      return -1
    
    # Dijkstra's method that does not use heap queue
   def dijkstra3(self, src: int) -> List[int]:
      visited = [False] * V
      dist = [INF] * V
      dist[src] = 0
      while(True):
        closest = selected = maxsize
        for i in range(V):
          if (dist[i] < closest) and not(visited[i]):
            selected = i
            closest = dist[i]
        if closest == maxsize: break
        visited[selected] = True
        for dest, weight in graph[selected]:
           if visited[dest]: continue
           distance = dist[selected] + weight
           dist[dest] = min(dist[dest], distance) 
      return dist

    # Bellman-Ford Method with adjacency list
    # Works even with negative edge weights
    # We assume that node's value is in range of 0 to size - 1, inclusive
   def bellman_ford(self, src: int) -> List[int]:
      
      dist = [INF] * V
      dist[src] = 0
      for iter in range(V):
        success = False
        for node1 in range(V):
           for node2, weight in graph[node1]:
              if dist[node2] > dist[node1] + weight:
                 success = True
                 dist[node2] = dist[node1] + weight
        # If not even one dist has been updated, we break the loop
        if not success:
           break
      # If there is not negative cycle in our graph, return the distances
      if not success:
         return dist
      # This is the case when there is a negative cycle 
      return -1

   # Warshall-Floyd method with adjacency matrix
   def warshall_floyd1(self, edges: List[List[int]]) -> List[List[int]]:
      dist = [([INF] * V) for _ in range(V)]

      for node1, node2, weight in edges:
        dist[node1][node2] = weight
      
      # Preprocessing
      for i in range(V): dist[i][i] = 0

      for transit in range(V):
         for node1 in range(V):
            for node2 in range(V):
               dist[node1][node2] = min(dist[node1][node2], dist[node1][transit] + dist[transit][node2])
      
      return dist
   
   # Warshall-Floyd method with reconstructing the shortest path between two nodes
   def warshall_floyd2(self, edges: List[List[int]]) -> List[int]:
      dist = [([INF] * V) for _ in range(V)]
      via = [-1] * V
      for node1, node2, weight in edges:
        dist[node1][node2] = weight
      
      # Preprocessing
      for i in range(V): dist[i][i] = 0

      for transit in range(V):
         for node1 in range(V):
            for node2 in range(V):
               if(dist[node1][node2] > dist[node1][transit] + dist[transit][node2]):
                  dist[node1][node2] = min(dist[node1][node2], dist[node1][transit] + dist[transit][node2])
                  via[node1][node2] = transit
      return via
   
   def reconstruct(self, node1: int, node2: int, edges: List[List[int]]) -> List[int]:
      via = self.warshall_floyd2(edges, V)
      path = []
      def make(node1: int, node2: int, path: List[int]) -> None:
         if (via[node1][node2] == -1):
            path.append(node1)
            if (node1 != node2): path.append(node2)
         else:
            make(node1, via[node1][node2])
            path.pop()
            make(via[node1][node2], node2)
      make(node1, node2, path)
      return path