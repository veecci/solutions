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
int main() {
  int q; scanf("%d", &q);
  ll l = 1, r = 1e10, mid, ans = -1;
  while (l <= r) {
    int mid = (l + r) / 2;
    ll t = mid, c = 0;
    while (t > 0) { c += t / 5; t /= 5; }
    if (c >= q) {
      if (c == q) ans = mid;
      r = mid - 1;
    } else l = mid + 1;
  }
  if (ans == -1) puts("No solution");
  else printf("%lld\n", ans);
  return 0;
}

