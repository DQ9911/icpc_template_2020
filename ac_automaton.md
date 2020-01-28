```c++
struct Trie {
	int nxt[N][26], cnt[N], fail[N], len[N], tot, root;
	void init() {
		tot = 0;
		len[0] = -1;
		for(int i = 0; i < 26; i++) nxt[0][i] = 1;
		root = newnode();
	}
	int newnode(int last = 0) {
		memset(nxt[++tot], 0, sizeof nxt[0]);
		cnt[tot] = fail[tot] = 0;
		len[tot] = len[last] + 1;
		return tot;
	}
	template<typename T>
	int ins(const T &s, int n) {
		int t = root;
		for(int i = 0; i < n; i++) {
			if(!nxt[t][s[i]-'a']) {
				nxt[t][s[i]-'a'] = newnode(t);
			}
			t = nxt[t][s[i]-'a'];
		}
		cnt[t]++;
		return t;
	}
	void build() {
		queue<int> q;
		q.push(root);
		while(!q.empty()) {
			int t = q.front(); q.pop();
			// cnt[t] += cnt[fail[t]];
			for(int i = 0; i < 26; i++) {
				if(nxt[t][i]) {
					fail[nxt[t][i]] = nxt[fail[t]][i];
					q.push(nxt[t][i]);
				} else nxt[t][i] = nxt[fail[t]][i];
			}
		}
	}
} tr;
```

