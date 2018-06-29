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
int const N = 100;
int a[N];
int f[1<<25];
int n;

int main() {
  int T; scanf("%d%d", &T, &n);
  while (T--) {
    rep(i, n * 3) scanf("%d", &a[i]);
    sort(a, a + n * 3);
    reverse(a, a + n * 3);
    rep(i, 1 << n) f[i] = -1; f[0] = 0;
    rep(i, 1 << n) if (f[i] >= 0) {
      int cnt = __builtin_popcount(i);
      int p = 0;
      while (i >> p & 1) ++p;
      int r = i | (1 << p);
      int x = a[cnt + p];
      int y = a[n * 3 - cnt - 1];
      for (int k = n; k > p; --k) if (!(i >> k & 1)) {
        int z = a[cnt + k];
        int t = (x - y) * z;
        int tm = (r | (1 << k)) >> 1;
        f[tm] = max(f[tm], f[i] + t);
      } else break;
    }
    printf("%d\n", f[(1 << n) - 1]);
  }
  return 0;
}

