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
int const N = 1000010;
char s[N];
bool dlt[N];
int lastIndex[128];
int rmd[128];
int cnt[128];

int main() {
  scanf(" %s", s);
  int n = strlen(s);
  rep(i, 26) lastIndex[i] = n;
  rep(i, n) cnt[s[i] - 'A']++;
  int cc = 0; rep(i, 26) if (cnt[i] % 2 != 0) ++cc;
  if (cc > 1) { puts("-1"); return 0; }
  ll ans = 0;
  rep(i, n) {
    if (dlt[i]) continue;
    char ch = s[i];
    int li = lastIndex[ch - 'A'] - 1;
    while (s[li] != ch) {
      if (!dlt[li]) ++rmd[ch - 'A'];
      --li;
    } 
    if (li == i) {
      int un = 0;
      for (int j = i - 1; j >= 0; --j) if (!dlt[j]) ++un;
      if (un < n / 2) ans += n / 2 - un;
    } else {
      ans += rmd[ch - 'A'];
      dlt[li] = 1;
      rep(j, 26) if (j != ch - 'A') {
        if (lastIndex[j] < li) --rmd[j];
      }
      lastIndex[ch - 'A'] = li;
    }
  }
  cout << ans << endl;
  return 0;
}

