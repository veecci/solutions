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
int const N = 55;
vector<int> f[N];
bool v[N], r[N];

int main() {
  int n, x; scanf("%d%d", &n, &x);
  Rep(i, n) {
    int d; scanf("%d", &d);
    rep(j, d) {
      int k; scanf("%d", &k);
      f[i].push_back(k);
    }
  }
  v[x] = 1;
  rep(i, f[x].size()) {
    v[f[x][i]] = 1;
    int t = f[x][i];
    rep(j, f[t].size()) r[f[t][j]] = 1;
  }
  vector<int> ans;
  Rep(i, n) if (!v[i] && r[i]) ans.push_back(i);
  printf("%lu\n", ans.size());
  rep(i, ans.size()) {
    printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
  }
  return 0;
}

