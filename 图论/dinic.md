```c++
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 10010;
const int M = 1200010;
const int inf = 0x3f3f3f3f;
#define clr(a, b) memset(a, b, sizeof a)
struct Dinic {
	struct E {
		int to, next, cap, flow;
	} es[M];
	int tot, head[N];
	void init() {
		tot = 0; clr(head, -1);
	}
	void adde(int u, int v, int w) {
		es[tot] = {v, head[u], w, 0}, head[u] = tot++;
		es[tot] = {u, head[v], 0, 0}, head[v] = tot++;
	}
	int Q[N], fr, tl;
	int dep[N], cur[N], stk[N];
	bool bfs(int s, int t, int n) {
		fr = tl = 0;
		clr(dep, -1);
		dep[s] = 0;
		Q[tl++] = s;
		while(fr < tl) {
			int u = Q[fr++];
			for(int i = head[u]; ~i; i = es[i].next) {
				int v = es[i].to;
				if(es[i].cap > es[i].flow && !~dep[v]) {
					dep[v] = dep[u] + 1;
					if(v == t) return true;
					Q[tl++] = v;
				}
			}
		}
		return false;
	}
	ll maxflow(int s, int t, int n) {
		ll ret = 0;
		while(bfs(s, t, n)) {
			for(int i = 1; i <= n; i++) cur[i] = head[i];
			int u = s; tl = 0;
			while(cur[s] != -1) {
				if(u == t) {
					int tp = inf;
					for(int i = tl - 1; ~i; i--)
						tp = min(tp, es[stk[i]].cap - es[stk[i]].flow);
					ret += tp;
					for(int i = tl - 1; ~i; i--) {
						es[stk[i]].flow += tp;
						es[stk[i]^1].flow -= tp;
						if(es[stk[i]].cap - es[stk[i]].flow == 0)
							tl = i;
					}
					u = es[stk[tl]^1].to;
				} else if(~cur[u] && es[cur[u]].cap > es[cur[u]].flow
				          && dep[u] + 1 == dep[es[cur[u]].to]) {
					stk[tl++] = cur[u];
					u = es[cur[u]].to;
				} else {
					while(u != s && cur[u] == -1)
						u = es[stk[--tl]^1].to;
					cur[u] = es[cur[u]].next;
				}
			}
		}
		return ret;
	}
} flow;

```

