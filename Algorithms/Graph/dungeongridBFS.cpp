#include <bits/stdc++.h>

using namespace std;

class Grid {
private:
  int R, C, startRow, startCol;
  vector<vector<char> > matrix;
  queue<int> rq; // row queue
  queue<int> cq; // column queue
  int move_count, nodes_left_in_layer, nodes_in_next_layer;
  bool reached_end;
  vector<vector<bool> > visited;
  vector<int> dr;
  vector<int> dc;

public:
  Grid(vector<vector<char> >& grid, int rows, int cols, int sRow, int sCol) {
    R = rows;
    C = cols;
    startRow = sRow;
    startCol = sCol;
    matrix = vector<vector<char> >(R, vector<char>(C));
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        matrix[i][j] = grid[i][j];
      }
    }
    move_count = 0;
    nodes_left_in_layer = 1;
    nodes_in_next_layer = 0;
    reached_end = false;
    visited = vector<vector<bool> >(R, vector<bool>(C, false));
    dr = { -1, 1, 0, 0 };
    dc = { 0, 0, 1, -1 };
  }

  void explore_neighbours(int r, int c) {
    for (int i = 0; i < 4; i++) {
      int rr = r + dr[i];
      int cc = c + dc[i];

      if (rr < 0 || cc < 0) continue;
      if (rr >= R || cc >= C) continue;

      if (visited[rr][cc]) continue;
      if (matrix[rr][cc] == '#') continue;

      rq.push(rr);
      cq.push(cc);
      visited[rr][cc] = true;
      nodes_in_next_layer++;
    }
  }

  int solve() {
    rq.push(startRow);
    cq.push(startCol);
    visited[startRow][startCol] = true;

    while (!rq.empty()) {
      int r = rq.front();
      int c = cq.front();

      if (matrix[r][c] == 'E') {
        reached_end = true;
        break;
      }

      explore_neighbours(r, c);
      nodes_left_in_layer--;

      if (nodes_left_in_layer == 0) {
        nodes_left_in_layer = nodes_in_next_layer;
        nodes_in_next_layer = 0;
        move_count++;
      }

      rq.pop();
      cq.pop();
    }

    if (reached_end)
      return move_count;

    return -1;
  }
};

int main() {
  vector<vector<char> > grid = {
    { 'S', '.', '.', '#', '.', '.', '.' },
    { '.', '#', '.', '.', '.', '#', '.' },
    { '.', '#', '.', '.', '.', '.', '.' },
    { '.', '.', '#', '#', '.', '.', '.' },
    { '#', '.', '#', 'E', '.', '#', '.' }
  };

  Grid g(grid, 5, 7, 0, 0);
  int minMoves = g.solve();
  if (minMoves != -1)
    cout << "Minimum moves required to reach end: " << minMoves << endl;
  else
    cout << "Can't reach end" << endl;
  return 0;
}
