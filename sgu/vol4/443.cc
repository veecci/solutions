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
int cal(int n) {
  vector<int> v;
  for (int i = 2; i <= n; ++i) {
    if (n % i == 0) {
      v.push_back(i);
      while (n % i == 0) n /= i;
    }
  }
  if (n > 1) v.push_back(n);
  int x = 0, s = 0;
  rep(i, v.size()) {
    s += v[i];
    x = max(v[i], x);
  }
  return x * 2 - s;
}
int main() {
  int a, b;
  scanf("%d%d", &a, &b);
  if (cal(a) < cal(b)) puts("b");
  else puts("a");
  return 0;
}

