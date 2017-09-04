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
char mp[20][20]; int r[20][20];
int g[20202][9], f[20202], cnt;
int a[9];
int const dir[4][2] = { 0, 1, 0, -1, 1, 0, -1, 0 };
void dfs(int d, int s) {
  if (d == 9) {
    rep(i, d) g[cnt][i] = a[i];
    f[cnt] = s;
    ++cnt;
    return;
  }
  int mx = min(s + 1, 5);
  Rep(i, mx) {
    a[d] = i;
    dfs(d + 1, max(i, s));
  }
}
struct DSU {
  int p[10];
  void init() { rep(i, 10) p[i] = -1; }
  inline int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  void uni(int x, int y) {
    x = find(x), y = find(y); if (x == y) return;
    if (p[x] < p[y]) {
      p[x] += p[y], p[y] = x;
    } else {
      p[y] += p[x], p[x] = y;
    }
  }
} dsu;
struct Node {
  int x, y;
} p[10];
struct Block {
  int x[10], y[10], n;
  int w, h;
  void add(int tx, int ty) {
    x[n] = tx, y[n] = ty;
    ++n;
  }
  bool cal() {
    int x1 = inf, x2 = 0, y1 = inf, y2 = 0;
    rep(i, n) {
      x1 = min(x1, x[i]);
      x2 = max(x2, x[i]);
      y1 = min(y1, y[i]);
      y2 = max(y2, y[i]);
    }
    w = y2 - y1 + 1;
    h = x2 - x1 + 1;
    rep(i, n) x[i] -= x1, y[i] -= y1;
    return w <= 3 && h <= 3;
  }
} b[10];

int ans[5][5], sans[20][20], tmp[5][5];
bool put(int d, int s) {
  if (s == 9) return 1;
  int h = b[d].h, w = b[d].w;
  rep(i, 3) rep(j, 3) if (i + h <= 3 && j + w <= 3) {
    bool ok = 1;
    rep(k, b[d].n) {
      int tx = b[d].x[k];
      int ty = b[d].y[k];
      if (tmp[i + tx][j + ty] != -1) {
        ok = 0; break;
      }
    }
    if (ok) {
      rep(k, b[d].n) {
        int tx = b[d].x[k];
        int ty = b[d].y[k];
        tmp[i + tx][j + ty] = d;
      }
      if (put(d + 1, s + b[d].n)) return 1;
      rep(k, b[d].n) {
        int tx = b[d].x[k];
        int ty = b[d].y[k];
        tmp[i + tx][j + ty] = -1;
      }
    }
  }
  return 0;
}

int main() {
  clr(r, 0xff);
  dfs(0, 0);
  int n, m; scanf("%d%d", &n, &m);
  rep(i, n) scanf(" %s", mp[i]);
  int k = 0;
  rep(i, n) rep(j, m) {
    if (mp[i][j] == 'X') {
      p[k].x = i, p[k].y = j;
      r[i][j] = k; ++k;
    }
  }
  int ant = inf;
  int dt[10];
  rep(z, cnt) {
    dsu.init();
    rep(i, n) rep(j, m) if (r[i][j] >= 0) {
      rep(d, 4) {
        int ti = i + dir[d][0], tj = j + dir[d][1];
        if (ti >= 0 && ti < n && tj >= 0 && tj < m && r[ti][tj] >= 0) {
          int r1 = r[i][j], r2 = r[ti][tj];
          if (g[z][r1] == g[z][r2]) dsu.uni(r1, r2);
        }
      }
    }
    Rep(i, 9) dt[i] = 0;
    rep(i, 9) dt[g[z][i]]++;
    bool flag = 1;
    rep(i, 9) {
      int t = g[z][i];
      if (dt[t] > 0 && dt[t] != -dsu.p[dsu.find(i)]) flag = 0;
    } 
    if (!flag) continue;
    int v = f[z];
    Rep(i, v) b[i].n = 0;
    rep(i, 9) {
      int num = g[z][i];
      b[num].add(p[i].x, p[i].y);
    }
    Rep(i, v) {
      if (!b[i].cal()) {
        flag = 0; break;
      } 
    }
    if (!flag) continue;
    rep(i, 3) rep(j, 3) tmp[i][j] = -1;
    if (put(0, 0)) {
      if (v < ant) {
        ant = v;
        rep(i, 3) rep(j, 3) ans[i][j] = tmp[i][j];
        rep(i, n) rep(j, m) sans[i][j] = -1;
        rep(i, 9) {
          sans[p[i].x][p[i].y] = g[z][i];
        }
      }
    }
  }
  printf("%d\n", ant);
  rep(i, n) {
    rep(j, m) {
      if (sans[i][j] == -1) putchar('.');
      else putchar('A' + sans[i][j] - 1);
    }
    puts("");
  }
  puts("");
  rep(i, 3) {
    rep(j, 3) putchar('A' + ans[i][j] - 1);
    puts("");
  }
  return 0;
}

