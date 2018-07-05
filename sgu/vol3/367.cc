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
int const M = 1000010;
struct Edges {
  int u, next;
} e[M];
int p[N], idx;
void init() { clr(p, 0xff); idx = 0; }
void addedge(int u, int v) { e[idx].u = v, e[idx].next = p[u], p[u] = idx++; }
int a[N];
int deg[N];
priority_queue<pair<int, int> > q;
vector<int> ans;

int main() {
  int n, m, t; scanf("%d%d", &n, &t);
  Rep(i, n) scanf("%d", &a[i]);
  init(); scanf("%d", &m);
  rep(i, m) {
    int x, y; scanf("%d%d", &x, &y);
    ++deg[y]; addedge(x, y);
  }
  Rep(i, n) if (deg[i] == 0) {
    q.push(make_pair(-a[i], i));
  }
  int ac = 0, cur = 0, at = 0;
  while (!q.empty()) {
    int u = q.top().second; q.pop();
    cur += a[u];
    if (cur > t) break;
    ans.push_back(u);
    ++ac;
    at += cur;
    for (int i = p[u]; ~i; i = e[i].next) {
      int v = e[i].u;
      --deg[v];
      if (deg[v] == 0) {
        q.push(make_pair(-a[v], v));
      }
    }
  }
  printf("%d %d\n", ac, at);
  if (ac > 0) {
    rep(i, ac) {
      if (i == ac - 1) printf("%d\n", ans[i]);
      else printf("%d ", ans[i]);
    }
  }
  return 0;
}

