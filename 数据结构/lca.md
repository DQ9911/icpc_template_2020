```c++
const int N = 1e5 + 10;

int fa[N];
int Find(int x) {
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

vector<pii> E[N];
// E[u].emplace_back(v, cost)
vector<pii> q[N];
// q[u].emplace_back(v, id)
int d[N], ans[N];
void prepare(int u, int f) {
    for(auto &e : E[u]) {
    		int v = e.fi;
        if(v == f) continue;
        d[v] = d[u] + e.se;
        prepare(v, u);
    }
}

bool vis[N];
void tarjan(int u, int f) {
    vis[u] = 1;
    for(auto &e : E[u]) {
        int v = e.fi;
        if(v == f) continue;
        tarjan(v, u);
        fa[v] = u;
    }
    for(auto &e : q[u]) {
        int v = e.fi;
        if(vis[v]) {
            ans[e.se] = d[u] + d[v] - 2 * d[Find(v)];
            // lca(u, v) = Find(v);
        }
    }
}
```

