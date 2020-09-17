template<typename T>
struct graph {
	struct edge {
		int u, v;
		T w;
		edge() {}
		edge(int _u,int _v,T _w=1):u(_u),v(_v),w(_w) {}
	};
	vector<edge> edges;
	vector<vector<int> > adj;
	int n;
	graph(int _n = 0):adj(_n + 1), n(_n) {}
	void add_edge(int u, int v, T w = 1) {
		adj[u].push_back(edges.size());
		edges.emplace_back(u, v, w);
		adj[v].push_back(edges.size());
		edges.emplace_back(v, u, w);
	}
};
