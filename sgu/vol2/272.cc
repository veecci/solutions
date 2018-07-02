#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <ctime>
#include <map>

#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define Rep(i, n) for (int i = 1; i <= (n); ++i)
#define clr(x, a) memset(x, (a), sizeof x)
using namespace std;
typedef long long ll;
int const N = 10010;
int const M = 200010;
struct Edges {
  int u, next;
} e[M];
int p[N], idx;
void init() { clr(p, 0xff); idx = 0; }
void addedge(int u, int v) { e[idx].u = v, e[idx].next = p[u], p[u] = idx++; }
int dis[N], dit[N], ak;
queue<int> q;
bool va[N], vb[N];
int cur[N], path[M], px;
bool vis[N];

bool dfs(int u, int d) {
  cur[d] = u;
  vis[u] = 1;
  if (d == ak) {
    rep(i, d + 1) path[px++] = cur[i];
    return 1;
  }
  for (int i = p[u]; ~i; i = e[i].next) {
    int v = e[i].u;
    if (!vis[v] && dis[v] > dis[u] && dis[v] + dit[v] == ak) {
      if (dfs(v, d + 1)) return 1;
    }
  }
  //vis[u] = 0;
  return 0;
}
int main() {
  int n, m; scanf("%d%d", &n, &m);
  init();
  rep(i, m) {
    int x, y; scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  int n1, n2; scanf("%d", &n1);
  clr(dis, 0x3f);
  rep(i, n1) {
    int x; scanf("%d", &x);
    q.push(x); dis[x] = 0; va[x] = 1;
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = p[u]; ~i; i = e[i].next) {
      int v = e[i].u;
      if (dis[u] + 1 < dis[v]) {
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
  clr(dit, 0x3f); while (!q.empty()) q.pop(); 
  scanf("%d", &n2);
  rep(i, n2) {
    int x; scanf("%d", &x);
    q.push(x); dit[x] = 0; vb[x] = 1;
  }
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = p[u]; ~i; i = e[i].next) {
      int v = e[i].u;
      if (dit[u] + 1 < dit[v]) {
        dit[v] = dit[u] + 1;
        q.push(v);
      }
    }
  }
  ak = inf;
  Rep(i, n) if (vb[i]) ak = min(ak, dis[i]);
  Rep(i, n) if (va[i] && !vis[i]) dfs(i, 0);
  int ac = px / (ak + 1);
  printf("%d %d\n", ac, ak);
  px = 0;
  rep(i, ac) {
    rep(j, ak + 1) {
      int d = path[px++];
      if (j == ak) printf("%d\n", d);
      else printf("%d ", d);
    }
  }
  return 0;
}

