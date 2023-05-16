from collections import *
from typing import *
from sys import *

class ShortestPath(object):
   V = 13
   # Dijkstra's method that returns the shortest distance from one source node to all other nodes
   def dijkstra1(self, edges: List[List[int]], src: int) -> dict:  
      # Forming the graph
      graph = collections.defaultdict(list)
      for n1, n2, weight in edges:
         graph[n1].append((n2, weight))

      # Min-heap-queue for taking out the smallest item 
      hq = [(0, src)]
      # Distance variable to store all distances
      dist = collections.defaultdict(int)

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
      # Forming the graph in adjacency list
      graph = collections.defaultdict(list)
      for n1, n2, weight in edges:
         graph[n1].append((n2, weight))

      # Min-heap-queue for taking out the smallest item 
      hq = [(0, src)]
      # Distance variable to store all distances
      dist = collections.defaultdict(int)

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
   def dijkstra3(self, edges: List[List[int]], src: int) -> List[int]:
      # Forming the graph in adjacency list
      graph = collections.defaultdict(list)
      size = 0
      for n1, n2, weight in edges:
        if n1 not in graph: size += 1
        graph[n1].append((n2, weight))
      visited = [False] * size
      dist = [sys.maxsize] * size
      dist[src] = 0
      while(True):
        closest = selected = sys.maxsize
        for i in range(size):
          if (dist[i] < closest) and not(visited[i]):
            selected = i
            closest = dist[i]
        if closest == sys.maxsize: break
        visited[selected] = True
        for dest, weight in graph[selected]:
           if visited[dest]: continue
           distance = dist[selected] + weight
           dist[dest] = min(dist[dest], distance) 
      return dist

    # Bellman-Ford Method with adjacency list
    # Works even with negative edge weights
    # We assume that node's value is in range of 0 to size - 1, inclusive
   def bellman_ford(self, edges: List[List[int]], src: int, size: int) -> List[int]:
       # Forming the graph in adjacency list
      graph = collections.defaultdict(list)
      for n1, n2, weight in edges:
         graph[n1].append((n2, weight))        

      dist = [sys.maxsize] * size
      dist[src] = 0
      for iter in range(size):
        success = False
        for node1 in range(size):
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
   def warshall_floyd1(self, edges: List[List[int]], size: int) -> List[List[int]]:
      dist = [([sys.maxsize] * size) for _ in range(size)]

      for node1, node2, weight in edges:
        dist[node1][node2] = weight
      
      # Preprocessing
      for i in range(size): dist[i][i] = 0

      for transit in range(size):
         for node1 in range(size):
            for node2 in range(size):
               dist[node1][node2] = min(dist[node1][node2], dist[node1][transit] + dist[transit][node2])
      
      return dist
   
   # Warshall-Floyd method with reconstructing the shortest path between two nodes
   def warshall_floyd2(self, edges: List[List[int]], size: int) -> List[int]:
      dist = [([sys.maxsize] * size) for _ in range(size)]
      via = [-1] * size
      for node1, node2, weight in edges:
        dist[node1][node2] = weight
      
      # Preprocessing
      for i in range(size): dist[i][i] = 0

      for transit in range(size):
         for node1 in range(size):
            for node2 in range(size):
               if(dist[node1][node2] > dist[node1][transit] + dist[transit][node2]):
                  dist[node1][node2] = min(dist[node1][node2], dist[node1][transit] + dist[transit][node2])
                  via[node1][node2] = transit
      return via
   
   def reconstruct(self, node1: int, node2: int) -> List[int]:
      via = warshall_floyd2(edges, V)
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

