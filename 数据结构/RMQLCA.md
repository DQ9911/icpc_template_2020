```C++
struct RMQLCA {
	int n, dfs_clock;
//	vector<vector<int> > E;
	vector<int> seq, iseq, id;
	SparseTable rmq;
	RMQLCA() {}
	RMQLCA(/*vector<vector<int> > &_E, */int _n, int root) {
		n = _n;
		dfs_clock = 0;
//		E = _E;
		seq.resize(2 * n - 1);
		iseq.resize(2 * n - 1);
		id.resize(n);
		dfs(root, -1);
		rmq = SparseTable(seq);
	}
	void dfs(int u, int fa) {
		id[u] = dfs_clock;
		seq[dfs_clock++] = id[u];
		iseq[id[u]] = u;
		for(auto &e : E[u]) {
			int v, w; tie(v, w) = e;
			if(v == fa) continue;
			dfs(v, u);
			seq[dfs_clock++] = id[u];
		}
	}
	int lca(int u, int v) {
		if(id[u] > id[v]) swap(u, v);
		return iseq[rmq.query(id[u], id[v])];
	}
};

```

