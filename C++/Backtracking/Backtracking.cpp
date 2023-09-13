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
// Create class for each problem instead of namespace
#include<bits/stdc++.h>
#include<limits.h>
using namespace std;

#define ll long long
#define arr array
#define INF 987654321

  // https://www.geeksforgeeks.org/the-knights-tour-problem/
class knight_tour {
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
      return knight_dfs(0, 0, 1);
    }
  }

class rat_in_maze {
    // https://www.geeksforgeeks.org/rat-in-a-maze/
    vector<int> dx = {1, -1, 0, 0};
    vector<int> dy = {0, 0, 1, -1};
    vector<string> dir = {"D", "U", "R", "L"};
    vector<string> ret;
    
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
    
    vector<string> findPath(vector<vector<int>> &m, int n) {
        dfs(0, 0, n, "", m);
        return ret;
    }
  }

class n_queen {
    // https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/
    
    // Naive Backtracking solution by adding row (First Solution)
    vector<vector<int>> ret;
    int check(vector<int> record, int col, int row) {
        for(int i = 0; i< record.size(); i++) {
            // Check for the same row already added
            if(record[i] == row) return false;
            // Check for the left upper diagonal 
            if(record[i] == (row - (col-i))) return false;
            // Check for the left lower diagonal
            if(record[i] == (row + (col-i))) return false;
        }
        return true;
    }
    
    void dfs1(int col, vector<int>& record, int n, vector<int>& ret){
        if(col == n) {
            ret.push_back(record);
            return;
        }
        for(int row = 1; row <= n; row++) {
            if(check(record, col, row) == true) {
                record.push_back(row);
                dfs1(col + 1, record, n);
                record.pop_back();
            }
        }
        return;
    }

    vector<vector<int>> nQueen1(int n) {
        vector<int> record;
        dfs1(0, record, n, ret);
        return ret;
    }

    // Optimized solution for checking the diagonals and rows separately (still adding row)
    void dfs2(int col, vector<int>& record, int n, vector<int>& left_diagonal, 
    vector<int>& right_diagonal, vector<vector<int>>& ret, vector<int>& check_row) {
      if(col == n) {
        ret.push_back(record);
        return;
      }
      for(int row = 1; row <= n; row++) {
        if ((left_diagonal[row - col + n - 1] != 1) && (right_diagonal[row + col] != 1) && 
        (check_row[row] != 1)) {
          record.push_back(row);
          left_diagonal[row - col + n - 1] = 1;
          right_diagonal[row + col] = 1;
          check_row[row] = 1;
          dfs2(col + 1, record, n, left_diagonal, right_diagonal, ret, check_row);
          record.pop_back();
          left_diagonal[row - col + n - 1] = 0;
          right_diagonal[row + col] = 0;
          check_row[row] = 0;
        }
      }
        return;
    }
    
    vector<vector<int>> nQueen2(int n) {
        // code here
        vector<vector<int>> ret;
        vector<int> left_diagonal(2*n, 0);
        vector<int> right_diagonal(2*n, 0);
        vector<int> check_row(n + 1, 0);
        vector<int> record;
        dfs2(0, record, n, left_diagonal, right_diagonal, ret, check_row);
        return ret;
    }
  }

