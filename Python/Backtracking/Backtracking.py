from collections import *
from typing import *
from sys import *
import heapq

class KnightTour(object):
  def __init__(self) -> None:
    self.N = 8
    self.dx = {2, 1, -1, -2, -2, -1, 1, 2}
    self.dy = {1, 2, 2, 1, -1, -2, -2, -1}
    self.sol = [[-1] * self.N for _ in range(N)]
    self.sol[0][0] = 0

  def knight_dfs(self, x: int, y: int, iter: int) -> bool:
    if (iter == self.N * self.N): return True
    for add_x, add_y in zip(self.dx, self.dy):
        new_x = x + add_x
        new_y = y + add_y
        if((0 <= new_x < self.N) and (0 <= new_y < self.N) and (self.sol[new_x][new_y] == -1)):
            self.sol[new_x][new_y] = iter
            if self.knight_dfs(new_x, new_y, iter + 1): return True
            self.sol[new_x][new_y] = -1
    return False
  
  def solve_knight(self) -> bool:
    return self.knight_dfs(0, 0, 1)
    
class RatInMaze(object):
  def __init__(self):
    self.dx = {1, -1, 0, 0}
    self.dy = {0, 0, 1, -1}
    self.dire = {"D", "U", "R", "L"}
    self.ret = []

  def dfs(self, x: int, y: int, n: int, s: str, arr: List[List[int]]) -> None:
    if ((x < 0) or (x >= n) or (y < 0) or (y >= n) or (arr[x][y] == 0)): return None
    if ((x == n - 1) and (y == n - 1)):
        self.ret.append(s)
    arr[x][y] = 0
    
    for i in range(4):
        next_x = x + self.dx[i]
        next_y = y + self.dy[i]
        self.dfs(next_x, next_y, n, s + dir[i], arr)
    arr[x][y] = 1
    return None
  
  def findPath(self, m: List[List[int]], n: int) -> List[str]:
    self.dfs(0, 0, n, "", m)
    return self.ret
    
class NQueen(object):
  def __init__(object) -> None:
     ret = []
    
  def check(self, record: List[int], col: int, row: int) -> int:
    length = len(record)
    for i in range(length):
      # Check for the same row already added
      if(record[i] == row): return False
      # Check for the left upper diagonal 
      if(record[i] == (row - (col-i))): return False
      # Check for the left lower diagonal
      if(record[i] == (row + (col-i))): return False
    return True
  
  def dfs1(self, col: int, record: List[int], n: int, ret: List[int]) -> None:
    if(col == n):
      self.ret.append(record)
      return
    
    for row in range(1, n + 1):
      if(self.check(record, col, row)):
        record.push_back(row)
        self.dfs1(col + 1, record, n)
        record.pop()
    return
  
  def nqueen_solve1(self, n: int) -> List[List[int]]:
    record = list()
    self.dfs1(0, record, n, self.ret)
    return self.ret
  
  # Optimized solution for checking the diagonals and rows separately (still adding row)
  def dfs2(self, col: int, record: List[int], n: int, left_diagonal: List[int], \
           right_diagonal: List[int], ret: List[int], check_row: List[int]) -> None:
    if(col == n):
      self.ret.append(record)
      return
    
    for row in range(1, n + 1):
      if ((left_diagonal[row - col + n - 1] != 1) and (right_diagonal[row + col] != 1) and
      (check_row[row] != 1)):
        record.append(row)
        left_diagonal[row - col + n - 1] = 1
        right_diagonal[row + col] = 1
        check_row[row] = 1
        self.dfs2(col + 1, record, n, left_diagonal, right_diagonal, ret, check_row);
        record.pop()
        left_diagonal[row - col + n - 1] = 0
        right_diagonal[row + col] = 0
        check_row[row] = 0
      return
  
  def nqueen_solve2(self, n: int) -> List[List[int]]:
      ret = list()
      left_diagonal = [0] * (2*n)
      right_diagonal = [0] * (2*n)
      check_row = [0] * (n + 1)
      record = list()
      self.dfs2(0, record, n, left_diagonal, right_diagonal, ret, check_row)
      return self.ret