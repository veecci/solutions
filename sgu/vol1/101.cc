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

int const N = 10;
int const M = 111;
int g[N][N];
int d[N];
int n, m;
int ans[M];
int cnt;
int l[M][2];

void mark(int u, int v) {
  Rep(i, m) {
    if (l[i][0] == u && l[i][1] == v) {
      ans[cnt++] = i;
      l[i][0] = l[i][1] = -1;
      break;
    } else if (l[i][0] ==v && l[i][1] == u) {
      ans[cnt++] = -i;
      l[i][0] = l[i][1] = -1;
      break;
    } 
  } 
}

void go(int u) {
  rep(i, n + 1) if (g[u][i] > 0) {
    --g[u][i], --g[i][u];
    go(i);
    mark(i, u);
  }
}
int main() {
  n = 6; scanf("%d", &m);
  Rep(i, m) {
    int x, y; scanf("%d%d", &x, &y);
    g[x][y]++, g[y][x]++;
    d[x]++, d[y]++;
    l[i][0] = x, l[i][1] = y;
  }
  int oc = 0, o = -1;
  rep(i, n + 1) if (d[i] > 0) {
    if (o == -1) o = i;
    if (d[i] % 2 != 0) {
      o = i; ++oc;
    }
  }
  if (oc > 2) puts("No solution");
  else {
    go(o);
    if (cnt != m) {
      puts("No solution");
      return 0;
    }
    rep(i, cnt) {
      if (ans[i] < 0) printf("%d -\n", -ans[i]);
      else printf("%d +\n", ans[i]);
    }
  }
  return 0;
}
