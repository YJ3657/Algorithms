/*
Backtracking is an algorithmic technique that solves a problem by recursively covering
all possibilities, but backtracks/removes those solutions that do not meet required
constraints / are not optimized. Backtracking is used to solve decision problem, optimization problem,
and enumeration problem.

This file contains some well-known problems that can be solved using backtracking.
*Note however that backtracking may not likely be the best solution in terms of time/space
complexities
* Note the difference between backtracking, brute-force, and branch-and-bound algorithms
*/

#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long
#define arr array
#define INF 987654321

class Backtracking {

  // https://www.geeksforgeeks.org/the-knights-tour-problem/
  namespace knight_tour {
    #define N 8
    int dx = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy = {1, 2, 2, 1, -1, -2, -2, -1};
    int sol[N][N];
    memset(sol, -1, sizeof(sol));
    sol[0][0] = 0;

    bool knight_dfs(int x, int y, int iter) {
      int k, next_x, next_y;
      // Base case for when the knight filled the whole space
      if (iter == (N * N)) return true;

      for (k = 0; k < 8; k++) {
        next_x = x + dx[k];
        next_y = y + dy[k];

        if (next_x >= 0 && next_x < N && next_y >=0 && next_y < N && sol[next_x][next_y] == -1) {
          sol[next_x][next_y] = iter;
          if (knight_dfs(next_x, next_y, iter + 1)) return true;
          else sol[next_x][next_y] = -1;
        }
      }
      return false;
    }
  
    bool solve(void) {
      if knight_dfs(0, 0, 1) {
        return true;
      }
      return false;
    }
  }  

  namespace rat_in_maze {
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    vector<string> dir = {"D", "U", "R", "L"};
    vector<string> ret;
    vector<string> findPath(vector<vector<int>> &m, int n) {
        dfs(0, 0, n, "", m);
        return ret;
    }
    
    void dfs(int x, int y, int n, string s, vector<vector<int>> &arr) {
        if (x < 0 || x >= n || y < 0 || y >= n || arr[x][y] == 0) return;
        if (x == n - 1 && y == n - 1) {
            ret.push_back(s);
        }
        arr[x][y] = 0;
        int next_x, next_y;
        for (int i = 0; i < 4; i++) {
            next_x = x + dx[i];
            next_y = y + dy[i];
            dfs(next_x, next_y, n, s + dir[i], arr);
        }
        arr[x][y] = 1;
    }
  }
}