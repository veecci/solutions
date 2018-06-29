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
int const N = 10100, M = 100100;
struct Edges { int u, next; } e[M];
int p[N], idx;
void addedge(int u, int v) { e[idx].u = v, e[idx].next = p[u], p[u] = idx++; }
void init() { clr(p, 0xff); }
int n, b;
int sum[N];
void pf(int u, int pre = -1) {
  sum[u] = 1;
  for (int i = p[u]; ~i; i = e[i].next) {
    int v = e[i].u;
    if (v == pre) continue;
    pf(v, u);
    sum[u] += sum[v];
  }
}
int city[N], gov[N], col;
void fs(int u, int c, int pre = -1) {
  city[u] = c;
  for (int i = p[u]; ~i; i = e[i].next) {
    int v = e[i].u;
    if (v == pre) continue;
    fs(v, c, u);
  }
}
void dfs(int u, int s, int pre = -1) {
  city[u] = col; s++;
  vector<pair<int, int> > ve;
  for (int i = p[u]; ~i; i = e[i].next) {
    int v = e[i].u;
    if (v == pre) continue;
    ve.push_back(make_pair(sum[v], v));
  } 
  sort(ve.begin(), ve.end());
  int sz = ve.size();
  bool ck = 0;
  rep(i, sz) {
    int k = ve[i].first;
    int v = ve[i].second;
    if (k < b) {
      if (s + k <= 2 * b) {
        s += k;
        fs(v, col, u);
      } else {
        s = k;
        gov[++col] = u;
        fs(v, col, u);
      }
    } else {
      if (!ck && s > 0) {
        if (s < b) {
          if (col != city[u]) {
            bool found = 0;
            for (int j = i - 1; j >= 0; --j) {
              if (s - ve[j].first < 0) break;
              found = 1;
              s -= ve[j].first;
              fs(ve[j].second, city[u], u);
            }
            if (found) --col;
          }
        } else s = 0;
        ck = 1;
      }
      if (s == 0) {
        gov[++col] = u;
      }
      if (s + k <= 3 * b) {
        fs(v, col, u);
      } else {
        dfs(v, s, u);
      }
      s = 0;
    }
  }
  if (s > 0 && s < b) {
    for (int i = sz - 1; i >= 0; --i) {
      if (s - ve[i].first < 0) break;
      s -= ve[i].first;
      fs(ve[i].second, city[u], u);
    }
    --col;
  }
}

int main() {
  scanf("%d%d", &n, &b);  
  init();
  rep(i, n - 1) {
    int x, y; scanf("%d%d", &x, &y);
    addedge(x, y); addedge(y, x);
  }
  if (n < b) { puts("0"); return 0; }
  pf(1);
  gov[col = 1] = 1;
  dfs(1, 0);
  printf("%d\n", col);
  Rep(i, n) printf("%d%c", city[i], i == n ? '\n' : ' ');
  Rep(i, col) printf("%d%c", gov[i], i == col ? '\n' : ' ');
  return 0;
}
