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
typedef double db;
int const N = 3030;
db e[N];
db a[N];

int main() {
  int n; db t;
  scanf("%d %lf", &n, &t);
  rep(i, n) scanf("%lf", &a[i]);
  e[n] = 0;
  for (int i = n - 1; i >= 0; --i) {
    db best = 1e10;
    db s = 0, y = 0;
    db p = 1;
    for (int j = i; j < n; ++j) {
      db cost = j - i + 1 + t;
      db pt = p * a[j];
      y += s * 2;
      y += pt * (cost + 1 + e[j]);
      p *= (1 - a[j]);
      db tx = 1 - a[i];
      db ty = y + p * (cost + e[j + 1]);
      best = min(best, ty / tx);
      s += pt;
    }
    e[i] = best;
  }
  printf("%.15lf\n", e[0]);
  return 0;
}

