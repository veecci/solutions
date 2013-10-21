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
int const MaxIter = 10000;
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
int edges[M][2];
int pre[N], nxt[N];

int p_n, p_m, p_edges[M][2];
// }}


void build() {
	init();
	rep(i, m) {
		addEdge(edges[i][0], edges[i][1]);
		pre[edges[i][1]] = edges[i][0];
		nxt[edges[i][0]] = edges[i][1];
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
	n0 = n = getInt(), m = getInt();
	rep(i, m) {
		edges[i][0] = getInt();
		edges[i][1] = getInt();
	}
	build();
}
// }}

int added[N], acc;
bool ignored[N];
int newID[N];
void rebuild() {
	int mt = 0;
	rep(i, m) {
		if (!ignored[edges[i][0]] && !ignored[edges[i][1]]) {
			edges[mt][0] = edges[i][0];
			edges[mt][1] = edges[i][1];
			++mt;
		}	
	}
	m = mt;
	build();
}
void reduce() {
	bool updated = 1;
	clr(ignored, 0);
	while (updated) {
		updated = 0;
		rep(i, m) {
			if (!ignored[edges[i][0]] && edges[i][0] == edges[i][1]) {
				added[acc++] = edges[i][0];
				ignored[i] = 1;
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
				int u = pre[i], sel = -1;
				rep(j, m) {
					if (edges[j][0] == u && edges[j][1] == i) sel = j;
					else if (edges[j][0] == i) edges[j][0] = u;
				}
				edges[sel][0] = edges[m - 1][0];
				edges[sel][1] = edges[m - 1][1];
				--m;
				build();
				updated = 1;
				break;
			}
			if (!ignored[i] && deg_out[i] == 1) {
				int v = nxt[i], sel = -1;
				rep(j, m) {
					if (edges[j][0] == i && edges[j][1] == v) sel = j;
					else if (edges[j][1] == i) edges[j][1] = v;
				}
				edges[sel][0] = edges[m - 1][0];
				edges[sel][1] = edges[m - 1][1];
				--m;
				build();
				updated = 1;
				break;
			}
		}
	}
	//rebuild
	int id = 0;
	Rep(i, n) if (!ignored[i]) newID[i] = ++id;
	n = id;
	rep(i, m) {
		edges[i][0] = newID[edges[i][0]];
		edges[i][1] = newID[edges[i][1]];
	}
	build();
}

// judge DAG {{
bool vis[N];
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
	int id, deg_in, deg_out;
	consNode(int id = 0, int deg_in = 0, int deg_out = 0) : id(id), deg_in(deg_in), deg_out(deg_out) {}
	friend bool operator < (consNode a, consNode b) {
		return a.deg_in + a.deg_out < b.deg_in + b.deg_out;
		//return a.deg_in * a.deg_out < b.deg_in * b.deg_out;
		//return max(a.deg_in, a.deg_out) < max(b.deg_in, b.deg_out);
	}
} constmp;
priority_queue <consNode> consQ;
int consAdd[N], cc;

void construct() {
	clr(ignored, 0); cc = 0;
	while (!consQ.empty()) consQ.pop();
	Rep(i, n) consQ.push(consNode(i, deg_in[i], deg_out[i]));
	while (check()) {
		constmp = consQ.top(); consQ.pop();
		if (ignored[constmp.id]) continue;
		ignored[constmp.id] = 1;
		consAdd[cc++] = constmp.id;
		rebuild();
		reduce();
	}	
}
// }}

void localSearch() {
	
}

int bestNum;
int bestSolution[N];

void work() {
	acc = 0;
	reduce();
	rep(i, acc) bestSolution[i] = added[i];
	bestNum = n0;
	p_n = n, p_m = m; rep(i, m) p_edges[i][0] = edges[i][0], p_edges[i][1] = edges[i][1];
	rep(k, MaxIter) {
		if (k) { 
			n = p_n, m = p_m; rep(i, m) edges[i][0] = p_edges[i][0], edges[i][1] = p_edges[i][1]; 
		}
		construct();
		localSearch();
		if (acc + cc < bestNum) {
			bestNum = acc + cc;
			rep(i, cc) bestSolution[acc + i] = consAdd[i];
		}
	}
}

int main() {
	input();
	work();

	return 0;
}


