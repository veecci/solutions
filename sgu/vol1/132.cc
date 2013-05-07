#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <ctime>

#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
using namespace std;
typedef long long ll;
int const maxn = 71;
int const maxm = 10;
int dp[2][1 << 14];
char str[maxn][maxm];
int mp[maxn];
int n, m;
int _now, _pre;
inline int f(int mask, int pos) { return (mask >> (pos + pos)) & 3; }
inline int g(int pos, int c) { return (c << (pos + pos)); }
void dfs(int pos, int msk, int now, int row, int c) {
  if (pos == m) {
		dp[_now][now] = min(dp[_now][now], dp[_pre][msk] + c);
		return;
	}
	int u = f(msk, pos);
	if (f(mp[row], pos) == 1 || u == 2) dfs(pos + 1, msk, now ^ g(pos, 1), row, c);
	else {
		if (pos > 0) {
			int pre = f(now, pos - 1);
			if (pre != 0 && (row == 1 || u != 0)) dfs(pos + 1, msk, now, row, c);
		}
		else {
			if (row == 1 || u != 0) dfs(pos + 1, msk, now, row, c);
		}
		// h
		if (pos + 1 < m) {
			int nm = f(mp[row], pos + 1);
			int nu = f(msk, pos + 1);
			if (nm == 0 && nu != 2) {
				dfs(pos + 2, msk, now ^ g(pos, 1) ^ g(pos + 1, 1), row, c + 1);
			}
		}
		// v
		if (row < n && f(mp[row + 1], pos) == 0) {
			dfs(pos + 1, msk, now ^ g(pos, 2), row, c + 1);
		}
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%s", str[i]);
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < m; ++j) {
			mp[i] = (mp[i] << 2) | (str[i][j] == '*');
		}
	}
	memset(dp, 0x3f, sizeof dp);
	_pre = 0, _now = 1;
	dp[_pre][0] = 0;
	int mx = 1 << (m + m);
	for (int i = 1; i <= n; ++i) {
		memset(dp[_now], 0x3f, sizeof dp[_now]);
		for (int j = 0; j < mx; ++j) {
			if (dp[_pre][j] != inf) {
				dfs(0, j, 0, i, 0);
			}
		}
		swap(_pre, _now);
	}
	int ret = inf;
	for (int i = 0; i < mx; ++i) ret = min(ret, dp[_pre][i]);
	printf("%d\n", ret);
	return 0;
}

