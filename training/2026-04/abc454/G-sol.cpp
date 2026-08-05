#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 2500010;
const long long MOD = 998244353;

// 全局树结构与数据
int p[MAXN];
int c[MAXN];
vector<int> adj[MAXN];

// 树链剖分/DSU相关
int sz[MAXN];
int heavy[MAXN];
int tin[MAXN];
int tout[MAXN];
int node_at[MAXN];
int timer_dfs = 0;

// 状态维护数组
int cnt[MAXN];   // cnt[x] 表示颜色 x 出现的次数
int freq[MAXN];  // freq[f] 表示出现次数恰好为 f 的颜色种数
int max_f = 0;   // 当前最大的出现次数

// 答案存储
int ans_m[MAXN];
int ans_k[MAXN];

// O(1) 状态更新函数
inline void add_color(int color, int val) {
  int f = cnt[color];

  // 移除旧的状态
  if (f > 0) freq[f]--;
  if (f == max_f && freq[f] == 0)
    max_f--;  // 只有当最大频次没有任何颜色拥有时，才下降

  // 更新出现次数
  cnt[color] += val;
  f = cnt[color];

  // 加入新的状态
  if (f > 0) freq[f]++;
  if (f > max_f) max_f = f;
}

// 预处理 DFS 序和重儿子
void pre_dfs(int u) {
  tin[u] = ++timer_dfs;
  node_at[timer_dfs] = u;
  sz[u] = 1;
  heavy[u] = 0;

  for (int v : adj[u]) {
    pre_dfs(v);
    sz[u] += sz[v];
    if (heavy[u] == 0 || sz[v] > sz[heavy[u]]) {
      heavy[u] = v;
    }
  }
  tout[u] = timer_dfs;
}

// DSU on Tree 核心逻辑
void dsu_dfs(int u, bool keep) {
  // 1. 优先处理所有的轻儿子，算完后不保留（清空）
  for (int v : adj[u]) {
    if (v != heavy[u]) {
      dsu_dfs(v, false);
    }
  }

  // 2. 处理重儿子，算完后保留其状态！
  if (heavy[u]) {
    dsu_dfs(heavy[u], true);
  }

  // 3. 把当前节点自身，以及所有轻儿子的状态加回来
  // 利用 DFS 序，可以将递归转化为连续数组的高效遍历
  for (int v : adj[u]) {
    if (v != heavy[u]) {
      for (int i = tin[v]; i <= tout[v]; ++i) {
        add_color(c[node_at[i]], 1);
      }
    }
  }
  add_color(c[u], 1);  // 加上自己

  // 4. 记录当前子树的答案
  ans_m[u] = max_f;
  ans_k[u] = freq[max_f];

  // 5. 如果当前节点是作为轻儿子被调用的，完成使命后清空它所在的子树影响
  if (!keep) {
    for (int i = tin[u]; i <= tout[u]; ++i) {
      add_color(c[node_at[i]], -1);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  unsigned long long seed;
  int M, F;

  if (!(cin >> N >> seed >> M >> F)) return 0;

  // 读取 q 数组和 d 数组 (注意下标和边界)
  vector<int> q(M + 1, 0), d(M + 1, 0);
  for (int i = 2; i <= M; ++i) cin >> q[i];
  for (int i = 1; i <= M; ++i) cin >> d[i];

  unsigned long long state = seed;

  // 按照伪代码生成树的拓扑关系 p[i]
  for (int i = 2; i <= N; ++i) {
    if (i <= M) {
      p[i] = q[i];
    } else {
      p[i] = (state % (i - 1)) + 1;
      state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;  // % 2^31
    }
    adj[p[i]].push_back(i);  // 建树
  }

  // 按照伪代码生成颜色 c[i]
  for (int i = 1; i <= N; ++i) {
    if (i <= M) {
      c[i] = d[i];
    } else {
      c[i] = (state % F) + 1;
      state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;  // % 2^31
    }
  }

  // 1. 预处理出 sz, heavy, 以及 dfs 序
  pre_dfs(1);

  // 2. 执行树上启发式合并计算答案 (根节点，保留最终状态)
  dsu_dfs(1, true);

  // 3. 计算最终需输出的哈希/校验值
  long long final_ans = 0;
  for (int i = 1; i <= N; ++i) {
    long long term1 = ans_m[i] ^ i;
    long long term2 = ans_k[i] ^ i;
    long long prod = (term1 * term2) % MOD;
    final_ans = (final_ans + prod) % MOD;
  }

  cout << final_ans << "\n";

  return 0;
}