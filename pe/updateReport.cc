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
#include <sstream>

#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define Rep(i, n) for (int i = 1; i <= (n); ++i)
#define clr(x, a) memset(x, (a), sizeof x)
using namespace std;
typedef long long ll;
char buf[1010100];
char str[1010101];
int n;
map<string, int> rk;

struct Node {
  int day;
  string stat, pro, mon, year, tm;
  friend bool operator<(Node a, Node b) {
    if (a.year == b.year) {
      if (a.mon == b.mon) {
        if (a.day == b.day) {
          return a.tm < b.tm;
        } else {
          return a.day < b.day;
        }
      } else {
        return rk[a.mon] < rk[b.mon];
      }
    } else {
      return a.year < b.year;
    }
  }
} p[1111];

bool co(int x) {
  if (str[x] != 'C') return 0;
  if (x + 11 > n) return 0;
  return str[x + 2] == 'm' && str[x + 9] == ' ' && str[x + 10] == 'o';
}
bool cp(int x) {
  return str[x] == 'P' && str[x + 3] == 'b';
}
void pr(int x, int idx) {
  string s = "";
  rep(i, 40) {
    if (str[x + i] == '<') break;
    s += str[x+i];
  }
  p[idx].stat = s;
  istringstream is(s);
  string bf;
  is >> bf >> bf >> bf >> p[idx].day >> p[idx].mon >> p[idx].year >> p[idx].tm;
}
void pp(int x, int idx) {
  string s = "";
  rep(i, 40) {
    if (str[x + i] == '(') break;
    s += str[x+i];
  }
  p[idx].pro = s;
}
void prp(int x, int idx) {
  for (int i = x - 10; i >= 0; --i) {
    if (cp(i)) {
      pp(i, idx);
      break;
    }
  }
}
string mons[] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
int main() {
  rep(i, 12) rk[mons[i]] = i;
  //freopen("report.out", "w", stdout);
  freopen("report_byDate.out", "w", stdout);
  while (gets(buf)) {
    int m = strlen(buf);
    rep(i, m) {
      if (buf[i] == '\n') continue;
      str[n++] = buf[i];
    }
  }
  int cnt = 0;
  rep(i, n) {
    if (co(i)) {
      prp(i, cnt);
      pr(i, cnt);
      ++cnt;
    }
  }
  cout << cnt << endl;
  sort(p, p + cnt);
  rep(i, cnt) {
    cout << p[i].pro << p[i].stat << endl;
  }
  return 0;
}

