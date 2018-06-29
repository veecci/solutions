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
int const N = 222;
char s[N], t[N];
int main() {
  int n, a, b; scanf("%d%d%d", &n, &a, &b);
  scanf(" %s", s);
  rep(i, n) t[i] = s[i];
  rep(i, n) {
    if (t[i] == '0') --a;
    if (t[i] == '1') --b;
  }
  rep(i, n) {
    if (t[i] == '0') {
      if (a < 0 && b > 0) {
        ++a; --b;
        t[i] = '1';
      }
    } else if (t[i] == '1') {
      if (a > 0 && b < 0) {
        --a; ++b;
        t[i] = '0';
      }
    }
  }
  rep(i, n) {
    if (t[i] == '0') {
      if (a < 0) {
        ++a; t[i] = '2';
      }
    } else if (t[i] == '1') {
      if (b < 0) {
        ++b; t[i] = '2';
      }
    } else {
      if (a > 0) {
        --a; t[i] = '0';
      } else if (b > 0) {
        --b; t[i] = '1';
      }
    }
  }
  if (a != 0 || b != 0) {
    puts("-1");
    return 0;
  }
  int ans = 0;
  rep(i, n) if (s[i] != t[i]) ++ans;
  t[n] = 0;
  printf("%d\n", ans);
  puts(t);
  return 0;
}

