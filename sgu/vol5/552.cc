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
int const N = 200200;
int const M = 13;

ll hs(char *s) {
  unsigned long long t = 0;
  for (int i = 0; s[i]; ++i) {
    t = t * 13331 + s[i];
  } 
  return t;
}

map<ll, int> mp;
int main() {
  char buf[20];
  ll ids[10];
  int n, m, k; scanf("%d", &n);
  rep(i, n) {
    scanf("%d", &k);
    rep(j, k) {
      cin >> buf;
      ll id = hs(buf);
      ids[j] = id;
    }
    sort(ids, ids + k);
    rep(j, 1<<k) if (j > 0) {
      ll msk = 0;
      rep(l, k) {
        if (j >> l & 1) {
          msk = msk * 1000000007LL + ids[l];
        }
      }
      mp[msk]++;
    }
  }
  scanf("%d", &m);
  rep(i, m) {
    scanf("%d", &k);
    int ans = 0;
    rep(j, k) {
      scanf(" %s", buf);
      ll id = hs(buf);
      if (id == -1) ans = -1;
      ids[j] = id;
    }
    if (ans == -1) puts("0");
    else {
      ll msk = 0;
      sort(ids, ids + k);
      rep(j, k) msk = msk * 1000000007LL + ids[j];
      cout << mp[msk] << endl;
    }
  }
  return 0;
}


