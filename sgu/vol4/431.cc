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
int n, m;
char s[22][22], ds[22][22];
int ls[22], ld[22];
char om[22];
char msk[22];
int lim, rl;
bool f[22][22];
bool match(int l, char *str, int sl) {
  rep(i, sl + 1) rep(j, l + 1) f[i][j] = 0;
  f[0][0] = 1;
  rep(i, sl + 1) rep(j, l) if (f[i][j]) {
    if (msk[j] == '*') {
      for (int k = i; k <= sl; ++k) f[k][j + 1] = 1;
    } else if (msk[j] == '?') {
      f[i + 1][j + 1] = 1;
    } else {
      f[i + 1][j + 1] |= (msk[j] == str[i]);
    }
  }
  return f[sl][l];
}

bool check1(int l) {
  rep(i, n) if (!match(l, s[i], ls[i])) return 0;
  return 1;
}

bool check2(int l) {
  rep(i, n) {
    if (!match(l, s[i], ls[i])) return 0;
  }
  rep(i, m) {
    if (match(l, ds[i], ld[i])) return 0;
  }
  rl = l;
  puts(msk);
  return 1;
}

bool dfs(int d, int l, int r) {
  msk[l] = '*'; msk[l + 1] = 0;
  if (!check1(l + 1)) return 0;
  if (d == lim) {
    msk[l] = 0;
    if (l > 0 && check2(l)) return 1;
    msk[l] = '*'; msk[l + 1] = 0; 
    if (check2(l + 1)) return 1;
    rep(i, r) {
      msk[l + i] = '?';
      msk[l + i + 1] = 0;
      if (check2(l + i + 1)) return 1;
    }
    return 0;
  }
  msk[l] = '*';
  msk[l + 1] = om[d];
  if (dfs(d + 1, l + 2, r)) return 1;
  rep(i, r + 1) {
    rep(j, i) msk[l + j] = '?';
    msk[l + i] = om[d];
    if (dfs(d + 1, l + i + 1, r - i)) return 1;
  }
  return 0;
}

set<string> hs;
bool has(char *str, int l) {
  string z = "";
  rep(i, l) z += str[i];
  if (hs.find(z) == hs.end()) {
    hs.insert(z);
    return 0;
  }
  return 1;
}

int main() {
  scanf("%d%d", &n, &m);
  rep(i, n) scanf(" %s", s[i]);
  rep(i, m) scanf(" %s", ds[i]);
  rep(i, n) ls[i] = strlen(s[i]);
  rep(i, m) ld[i] = strlen(ds[i]);
  int md = 0; rl = -1;
  Rep(i, n - 1) if (ls[i] < ls[md]) md = i;
  int len = ls[md];
  rep(i, (1 << len)) {
    int idx = 0;
    rep(j, len) if (i >> j & 1) om[idx++] = s[md][j];
    if (has(om, idx)) continue;
    lim = idx;
    if (dfs(0, 0, 11 - idx)) {
      break;
    }
  }
  if (rl == -1) {
    puts("OOPS");
  }
  return 0;
}

