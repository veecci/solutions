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
int const N = 111;
string s[N];
bool cmp(string s1, string s2) {
  string a = s1 + s2;
  string b = s2 + s1;
  return a < b;
}
int main() {
  int n; cin >> n;
  rep(i, n) cin >> s[i];
  sort(s, s + n, cmp);
  rep(i, n) cout << s[i];
  cout << endl;
  return 0;
}

