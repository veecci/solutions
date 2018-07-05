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
int const N = 16010, M = 110;
struct Zone {
  int n, q, idx;
  friend bool operator<(Zone a, Zone b) {
    return a.q > b.q;
  }
} z[M];
struct Stu {
  int p, w, idx;
  friend bool operator<(Stu a, Stu b) {
    return a.w > b.w;
  }
} s[N];
int ans[N];

int main() {
  int k; scanf("%d", &k);
  rep(i, k) z[i].idx = i + 1;
  rep(i, k) scanf("%d", &z[i].n);
  rep(i, k) scanf("%d", &z[i].q);
  sort(z, z + k);
  int n = 0; rep(i, k) n += z[i].n;
  rep(i, n) scanf("%d", &s[i].p);
  rep(i, n) scanf("%d", &s[i].w);
  rep(i, n) s[i].idx = i;
  sort(s, s + n);
  rep(i, n) {
    bool f = 0;
    rep(j, k) if (s[i].p > z[j].q && z[j].n > 0) {
      z[j].n--;
      ans[s[i].idx] = z[j].idx;
      f = 1; break;
    }
    if (!f) {
      rep(j, k) if (z[j].n > 0) {
        z[j].n--;
        ans[s[i].idx] = z[j].idx;
        break;
      }
    }
  }
  rep(i, n) {
    if (i == n - 1) printf("%d\n", ans[i]);
    else printf("%d ", ans[i]);
  }
  return 0;
}

