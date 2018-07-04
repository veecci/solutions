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
int const N = 2001000;
ll f[N];

int main() {
  ll q, c; cin >> q >> c;
  int idx = 0, mod = (c + 1) * 2;
  while (1) {
    ++idx;
    int i = idx % mod;
    if (idx <= c) f[i] = 0;
    else if (idx == c + 1) f[i] = 1;
    else {
      int j = i - 1; if (j < 0) j += mod;
      int k = i - c - 1; if (k < 0) k += mod;
      f[i] = f[j] + f[k] + 1;
    }
    if (f[i] >= q) {
      cout << idx << endl;
      break;
    }
  }
  return 0;
}

