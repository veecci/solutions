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
int const N = 40004;
int const M = N * 2;
struct Edges {
  int u, next;
} e[M];
int p[N], idx;
void init() { clr(p, 0xff); idx = 0; }
void addedge(int u, int v) { e[idx].u = v, e[idx].next = p[u], p[u] = idx++; }
int n; int matx[N], maty[N]; bool fx[N], fy[N];
int path(int u) {
  fx[u] = 1;
  for (int i = p[u]; ~i; i = e[i].next) {
    int v = e[i].u;
    if (fy[v]) continue;
    fy[v] = 1;
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
  rep(i, n) if (!~matx[i]) {
    clr(fy, 0);
    ret += path(i);
  }
  return ret;
}

void fs(int r, int c) {
  clr(fx, 0); clr(fy, 0);
  rep(i, r) rep(j, c) if ((i + j) % 2 == 0) {
    int id = i * c + j;
    if (!~matx[id]) {
      path(id);
    }
  }
}

int g[202][202];
int const dir[4][2] = { 0, 1, 0, -1, 1, 0, -1, 0 };
int main() {
  int r, c; scanf("%d%d", &r, &c);
  rep(i, r) rep(j, c) scanf("%d", &g[i][j]);
  init(); n = r * c;
  rep(i, r) rep(j, c) if (g[i][j] && (i + j) % 2 == 0) {
    int id = i * c + j;
    rep(k, 4) {
      int ti = i + dir[k][0], tj = j + dir[k][1];
      if (ti >= 0 && tj >= 0 && ti < r && tj < c && g[ti][tj]) {
        int tid = ti * c + tj;
        addedge(id, tid);
      }
    }
  }
  int k = hungary();
  fs(r, c);
  int sum = 0; rep(i, r) rep(j, c) sum += g[i][j];
  printf("%d\n", sum - k);
  rep(i, r) {
    rep(j, c) {
      if (!g[i][j]) { putchar('#'); continue; }
      int id = i * c + j;
      if ((i + j) % 2 == 0) putchar(fx[id] ? 'G' : '.');
      else putchar(!fy[id] ? 'G' : '.');
    } 
    puts("");
  }
  return 0;
}

