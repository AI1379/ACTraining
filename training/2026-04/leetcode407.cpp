#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  struct Node {
    int height;
    int x, y;
  };

  // 最小堆比较器：高度越小越优先出队
  struct Cmp {
    bool operator()(const Node& a, const Node& b) {
      return a.height > b.height;
    }
  };

  int trapRainWater(vector<vector<int>>& heightMap) {
    if (heightMap.empty() || heightMap[0].empty()) {
      return 0;
    }

    int m = heightMap.size();
    int n = heightMap[0].size();

    // 优先队列，存放当前的“木桶边界”
    priority_queue<Node, vector<Node>, Cmp> pq;
    // 访问标记数组，防止重复遍历
    vector<vector<bool>> visited(m, vector<bool>(n, false));

    // 1. 将矩阵的最外圈（初始边界）全部加入最小堆
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
          pq.push({heightMap[i][j], i, j});
          visited[i][j] = true;
        }
      }
    }

    int water = 0;
    // 定义上下左右四个方向
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // 2. 木桶效应：从最矮的边开始向内 BFS 收缩
    while (!pq.empty()) {
      Node curr = pq.top();
      pq.pop();

      // 遍历当前边界格子的四个邻居
      for (int k = 0; k < 4; ++k) {
        int nx = curr.x + dirs[k][0];
        int ny = curr.y + dirs[k][1];

        // 确保不越界且未被访问过
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
          // 如果内部的格子比当前边界更矮，说明它是凹陷的，可以接水
          if (heightMap[nx][ny] < curr.height) {
            water += curr.height - heightMap[nx][ny];
          }

          // 将这个内部格子变成新的边界放入堆中
          // 注意：它的新高度是它自身高度和外围水位（curr.height）的最大值
          pq.push({max(curr.height, heightMap[nx][ny]), nx, ny});
          visited[nx][ny] = true;
        }
      }
    }

    return water;
  }
};

int main() { return 0; }