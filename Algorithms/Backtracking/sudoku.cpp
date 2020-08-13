#include <iostream>
#include <vector>
#define UNASSIGNED 0

using namespace std;

bool hasUnassigned(vector<vector<int>>& grid, int& r, int& c) {
  for (int i = 0; i < 9; i++)
    for (int j = 0; j < 9; j++)
      if (grid[i][j] == UNASSIGNED) {
        r = i; c = j;
        return true;
      }
  return false;
}

bool possible(vector<vector<int>>& grid, int r, int c, int n) {
  for (int i = 0; i < 9; i++)
    if (grid[i][c] == n || grid[r][i] == n)
      return false;

  int boxStartRow = r - r % 3;
  int boxStartCol = c - c % 3;
  for (int row = 0; row < 3; row++)
    for (int col = 0; col < 3; col++)
      if (grid[row + boxStartRow][col + boxStartCol] == n)
        return false;

  return true;
}

bool solve(vector<vector<int>>& grid) {
  int row, col;

  // check if it has any blank space
  // if not then the grid is solved
  if (!hasUnassigned(grid, row, col)) return true;

  for (int num = 1; num <= 9; num++) {
    if (possible(grid, row, col, num)) {
      // if it is possible to place the number
      // at this position then place it and check
      // if the board is valid
      grid[row][col] = num;

      // if the board is valid then the grid is solved
      if (solve(grid))
        return true;

      // if not then remove the number and try another one
      grid[row][col] = UNASSIGNED;
    }
  }

  return false;
}

int main() {
  vector<vector<int>> grid = {
    {3, 0, 6, 5, 0, 8, 4, 0, 0},
    {5, 2, 0, 0, 0, 0, 0, 0, 0},
    {0, 8, 7, 0, 0, 0, 0, 3, 1},
    {0, 0, 3, 0, 1, 0, 0, 8, 0},
    {9, 0, 0, 8, 6, 3, 0, 0, 5},
    {0, 5, 0, 0, 9, 0, 6, 0, 0},
    {1, 3, 0, 0, 0, 0, 2, 5, 0},
    {0, 0, 0, 0, 0, 0, 0, 7, 4},
    {0, 0, 5, 2, 0, 6, 3, 0, 0}
  };

  solve(grid);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}
