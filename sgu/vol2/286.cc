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
int const N = 100010;
int const M = 1000010;
struct Graph {
  struct Edges {
    int u, next;
    bool c;
  } e[M];
  int p[N], idx;
  void init() { clr(p, 0xff); idx = 0; }
  void addedge(int u, int v) { e[idx].u = v, e[idx].next = p[u], p[u] = idx++; }
} g1, g2;
int n;
int lines[M][2];
bool vis[N];

void go(int u) {
  vis[u] = 1;
  for (int i = g1.p[u]; ~i; i = g1.e[i].next) {
    if (g1.e[i].c) continue;
    g1.e[i].c = g1.e[i ^ 1].c = 1;
    g2.addedge(u, g1.e[i].u);
    go(g1.e[i].u);
  }
}

int matx[N], maty[N], fy[N];
int ptr;

int path(int u) {
  for (int i = g2.p[u]; ~i; i = g2.e[i].next) {
    int v = g2.e[i].u;
    if (fy[v] == ptr) continue;
    fy[v] = ptr;
    if (!~maty[v] || path(maty[v])) {
      matx[u] = v, maty[v] = u;
      return 1;
    }
  }
  return 0;
}
int hungary() {
  int ret = 0;
  clr(matx, 0xff), clr(maty, 0xff);
  ptr = 1;
  Rep(i, n) if (!~matx[i]) {
    ret += path(i);
    ++ptr;
  }
  return ret;
}

int main() {
  int k; scanf("%d%d", &n, &k); 
  g1.init(); g2.init();
  int m = n * k / 2;
  rep(i, m) {
    int x, y; scanf("%d%d", &x, &y);
    g1.addedge(x, y); g1.addedge(y, x);
    lines[i][0] = x, lines[i][1] = y;
  }
  Rep(i, n) if (!vis[i]) go(i);
  int ret = hungary();
  if (ret == n) {
    puts("YES");
    rep(i, m) {
      int x = lines[i][0], y = lines[i][1];
      if (matx[x] == y || matx[y] == x) printf("%d\n", i + 1);
    }
  } else puts("NO");
  return 0;
}

