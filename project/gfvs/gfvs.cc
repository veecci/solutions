#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>

// macro {{
#define inf 0x3f3f3f3f
#define Inf 0x3FFFFFFFFFFFFFFFLL
#define rep(i, n) for (int i = 0; i < (n); ++i)
#define Rep(i, n) for (int i = 1; i <= (n); ++i)
#define clr(x, a) memset(x, (a), sizeof x)
#define cpy(a, b) memcpy((a), (b), sizeof (b));
// }}

using namespace std;

// const {{
int const N = 10010;
int const M = 1000010;
int const MaxIter = 3;
//double const alpha = 0.88;
// }}

int n0;

// Graph {{
int n, m;
struct Edges { int u, next; } e[M];
int p[N], idx;
int deg_in[N], deg_out[N];
inline void addEdge(int u, int v) {
	++deg_in[v];
	++deg_out[u];
	e[idx].u = v;
	e[idx].next = p[u];
	p[u] = idx++;
}
inline void init() {
	idx = 0;
	clr(p, 0xff);
	clr(deg_in, 0);
	clr(deg_out, 0);
}
struct lines {
	int a, b;
	friend bool operator < (lines A, lines B) {
		if (A.a == B.a) return A.b < B.b;
		else return A.a < B.a;
	}
} l[M], pl[M], ol[M];
int pre[N], nxt[N];
int o_n, o_m;
int p_n, p_m, p_edges[M][2];
// }}

void delR() {
	if (m == 0) return;
	int tm = 1;
	sort(l, l + m);
	for (int i = 1; i < m; ++i) {
		if (l[i].a == l[i - 1].a && l[i].b == l[i - 1].b) continue;
		l[tm].a = l[i].a, l[tm].b = l[i].b; ++tm;
	}
	m = tm;
}
void build() {
	init();
	rep(i, m) {
		addEdge(l[i].a, l[i].b);
		pre[l[i].b] = l[i].a;
		nxt[l[i].a] = l[i].b;
	}
}

// input {{
inline int getInt() {
	int ret (0); char tmp; 
	while (!isdigit(tmp = getchar()));
	do ret = (ret << 3) + (ret << 1) + tmp - '0';
	while (isdigit(tmp = getchar()));
	return ret;
}
inline void input() {
	init();
	clr(pre, 0xff), clr(nxt, 0xff);
	n0 = o_n = n = getInt(), m = o_m = getInt();
	rep(i, m) {
		l[i].a = ol[i].a = getInt();
		l[i].b = ol[i].b = getInt();
	}
	build();
}
// }}
void outputEdges () {
	rep(i, m) {
		printf("(%d %d)\n", l[i].a, l[i].b);
	}
	puts("");
}



int added[N], acc;
bool ignored[N];
bool deled[N];
void rebuild() {
	int mt = 0;
	rep(i, m) {
		if (!ignored[l[i].a] && !ignored[l[i].b]) {
			l[mt].a = l[i].a;
			l[mt].b = l[i].b;
			++mt;
		}	
	}
	m = mt;
	delR();
	build();
}
void reduce() {
	bool updated = 1;
	while (updated) {
		updated = 0;
		rep(i, m) {
			if (!ignored[l[i].a] && l[i].a == l[i].b) {
				added[acc++] = l[i].a;
				ignored[l[i].a] = 1;
				updated = 1;
			}
		}
		Rep(i, n) if (!ignored[i]) {
			if (!deg_in[i] || !deg_out[i]) {
				ignored[i] = 1;
				updated = 1;
			}
		}
		if (updated) {
			rebuild();
			continue;
		}
		Rep(i, n) {
			if (!ignored[i] && deg_in[i] == 1) {
				ignored[i] = 1;
				int u = pre[i], sel = -1;
				rep(j, m) {
					if (l[j].a == u && l[j].b == i) sel = j;
					else if (l[j].a == i) l[j].a = u;
				}
				l[sel].a = l[m - 1].a;
				l[sel].b = l[m - 1].b;
				--m;
				delR();
				build();
				updated = 1;
				break;
			}
			if (!ignored[i] && deg_out[i] == 1) {
				ignored[i] = 1;
				int v = nxt[i], sel = -1;
				rep(j, m) {
					if (l[j].a == i && l[j].b == v) sel = j;
					else if (l[j].b == i) l[j].b = v;
				}
				l[sel].a = l[m - 1].a;
				l[sel].b = l[m - 1].b;
				--m;
				delR();
				build();
				updated = 1;
				break;
			}
		}
	}
}

// judge DAG {{
int vis[N];
bool cdfs(int u) {
	if (~vis[u]) return vis[u]; vis[u] = 1;
	for (int i = p[u]; ~i; i = e[i].next) if (cdfs(e[i].u)) return 1;
	return vis[u] = 0;
}
bool check() {
	clr(vis, 0xff);
	Rep(i, n) if (!~vis[i] && cdfs(i)) return 1; 
	return 0;
}
// }}

// ConstructGreedyRandomizedSolution {{
struct consNode {
	int id, deg_in, deg_out; bool av;
	consNode(int id = 0, int deg_in = 0, int deg_out = 0, bool av = 0) : id(id), deg_in(deg_in), deg_out(deg_out), av(av) {}
} cons[N], constmp;
int consAdd[N], cc;

inline bool cmp0(consNode const &a, consNode const &b) {
	return a.deg_in + a.deg_out > b.deg_in + b.deg_out;
}
inline bool cmp1(consNode const &a, consNode const &b) {
	return a.deg_in * a.deg_out > b.deg_in * b.deg_out;
}
inline bool cmp2(consNode const &a, consNode const &b) {
	return max(a.deg_in, a.deg_out) > max(b.deg_in, b.deg_out);
}

void construct(int g) {
	cc = 0; int cur = 1;
	Rep(i, n) cons[i] = consNode(i, deg_in[i], deg_out[i], 1);

	if (g == 0) sort(cons + 1, cons + n + 1, cmp0);
	else if (g == 1) sort(cons + 1, cons + n + 1, cmp1);
	else sort(cons + 1, cons + n + 1, cmp2);
	int nn = n;
	while (check() && cur <= nn) {
		while (cur <= nn && ignored[cons[cur].id]) {
			++cur;
		}
		if (cur > nn) break;
		constmp = cons[cur++];
		ignored[constmp.id] = 1;
		consAdd[cc++] = constmp.id;
		//printf("DEL %d\n", oriID[constmp.id]);
		
		//rebuild
		rebuild();
		reduce();
	}	
	//cout<<cur<<":"<<nn<<endl;
	//cout<<check()<<" "<<acc+cc<<endl;
}
// }}

void localSearch() {

}
int bestNum;
int bestSolution[N];
void output() {
	sort(bestSolution, bestSolution + bestNum);
	printf("%d\n{", bestNum);
	rep(i, bestNum) {
		if (i == bestNum - 1) printf("%d}\n", bestSolution[i]);
		else printf("%d, ", bestSolution[i]);
	}
}

bool pig[N];

void work() {
	clr(ignored, 0); acc = 0; 
	reduce(); int bcc = acc;
	rep(i, acc) bestSolution[i] = added[i];
	bestNum = n0;
	p_n = n, p_m = m; rep(i, m) pl[i].a = l[i].a, pl[i].b = l[i].b; Rep(i, n) pig[i] = ignored[i];
	rep(k, MaxIter) {
		if (k) { 
			n = p_n, m = p_m; rep(i, m) l[i].a = pl[i].a, l[i].b = pl[i].b; Rep(i, n) ignored[i] = pig[i];
			build();
		}
		acc = 0;
		construct(k % 3);
		localSearch();
		if (bcc + cc + acc < bestNum) {
			bestNum = bcc;
			rep(i, cc) bestSolution[bestNum++] = consAdd[i];
			rep(i, acc) bestSolution[bestNum++] = added[i];
		}
		
	}
}
bool mark[N];

int main() {
	//freopen("P50-100.dat", "r", stdin);
	//freopen("P50-150.dat", "r", stdin);
	//freopen("P50-200.dat", "r", stdin);
	//freopen("P50-250.dat", "r", stdin);
	//freopen("P50-300.dat", "r", stdin);
	//freopen("P50-500.dat", "r", stdin);
	//freopen("P50-600.dat", "r", stdin);
	//freopen("P50-700.dat", "r", stdin);
	//freopen("P50-800.dat", "r", stdin);
	//freopen("P50-900.dat", "r", stdin);
	//freopen("P100-200.dat", "r", stdin);
	//freopen("P100-300.dat", "r", stdin);
	//freopen("P100-400.dat", "r", stdin);
	//freopen("P100-500.dat", "r", stdin);
	//freopen("P100-600.dat", "r", stdin);
	//freopen("P100-1000.dat", "r", stdin);
	//freopen("P100-1200.dat", "r", stdin);
	//freopen("P100-1300.dat", "r", stdin);
	//freopen("P100-1400.dat", "r", stdin);
	//freopen("P500-1000.dat", "r", stdin);
	//freopen("P500-1500.dat", "r", stdin);
	//freopen("P500-2000.dat", "r", stdin);
	//freopen("P500-2500.dat", "r", stdin);
	//freopen("P500-3000.dat", "r", stdin);
	//freopen("P500-5000.dat", "r", stdin);
	//freopen("P500-5500.dat", "r", stdin);
	//freopen("P500-6000.dat", "r", stdin);
	//freopen("P500-6500.dat", "r", stdin);
	//freopen("P500-7000.dat", "r", stdin);
	//freopen("P1000-3000.dat", "r", stdin);
	//freopen("P1000-3500.dat", "r", stdin);
	//freopen("P1000-4000.dat", "r", stdin);
	//freopen("P1000-4500.dat", "r", stdin);
	//freopen("P1000-5000.dat", "r", stdin);
	//freopen("P1000-10000.dat", "r", stdin);
	//freopen("P1000-15000.dat", "r", stdin);
	//freopen("P1000-20000.dat", "r", stdin);
	//freopen("P1000-25000.dat", "r", stdin);
	//freopen("P1000-30000.dat", "r", stdin);
	input();
	work();
	output();
	//checker
	n = o_n, m = o_m; rep(i, m) l[i].a = ol[i].a, l[i].b = ol[i].b; 
	clr(mark, 0); rep(i, bestNum) mark[bestSolution[i]] = 1; 
	init();
	rep(i, m) {
		if (!mark[l[i].a] && !mark[l[i].b]) {
			addEdge(l[i].a, l[i].b);
		}
	}
	if (!check()) puts("check OK"); else puts("Wrong!");
	return 0;
}





