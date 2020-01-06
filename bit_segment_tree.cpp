struct bit_segment_tree {
	int ch[N*80][2], val[N*80], tot;
	int root[N], n, m;
	void init(int _n, int _m) {
		tot = 0;
		n = _n; m = _m;
		for(int i = 1; i <= n; i++) root[i] = 0;
	}
	int newnode() {
		++tot;
		val[tot] = 0;
		memset(ch[tot], 0, sizeof ch[tot]);
		return tot;
	}
	void ins(int &o, int l, int r, int x, int v) {
		if(!o) o = newnode();
		val[o] += v;
		if(l == r) return;
		int mid = (l + r) >> 1;
		if(mid >= x) ins(ch[o][0], l, mid, x, v);
		else ins(ch[o][1], mid + 1, r, x, v);
	}
	int query(int o, int l, int r, int ql, int qr) {
		if(!o || ql <= l && r <= qr) return val[o];
		int mid = (l + r) >> 1, res = 0;
		if(mid >= ql) res += query(ch[o][0], l, mid, ql, qr);
		if(mid < qr) res += query(ch[o][1], mid + 1, r, ql, qr);
		return res;
	}
	void update(int x, int y, int v) {
		for(; x <= n; x += x&-x)
			ins(root[x], 1, m, y, v);
	}
	int query(int x, int ql, int qr) {
		int res = 0;
		for(; x; x -= x&-x)
			res += query(root[x], 1, m, ql, qr);
		return res;
	}
	int query(int x1, int x2, int y1, int y2) {
		return query(x2, y1, y2) - query(x1 - 1, y1, y2);
	}
} t1;
