```c++
namespace SA {
#define rep(i, n) for(int i = 0; i < n; i++)
#define per(i, n) for(int i = n - 1; i >= 0; i--)
	int sa[N], cnt[N], ar1[N], ar2[N], *rk, *ht;
	inline bool cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a + l] == r[b + l];
	}
	template<typename T>
	void suffix_array(const T *s, int n, int m) {
		int *x = ar1, *y = ar2;
		memset(cnt, 0, sizeof(cnt[0]) * m);
		rep(i, n) cnt[x[i] = s[i]]++;
		rep(i, m - 1) cnt[i + 1] += cnt[i];
		per(i, n) sa[--cnt[x[i]]] = i;
		for(int d = 1, p = 1; p < n; d <<= 1, m = p) {
			p = 0;
			rep(i, d) y[p++] = n - d + i;
			rep(i, n) if(sa[i] >= d) y[p++] = sa[i] - d;
			memset(cnt, 0, sizeof(cnt[0]) * m);
			rep(i, n) cnt[x[y[i]]]++;
			rep(i, m - 1) cnt[i + 1] += cnt[i];
			per(i, n) sa[--cnt[x[y[i]]]] = y[i];
			swap(x, y); x[sa[0]] = 0; p = 1;
			rep(i, n - 1) x[sa[i+1]]=cmp(y,sa[i],sa[i+1],d)?p-1:p++;
		}
		rk = x; ht = y;
		for(int i = 0, k = 0; i < n - 1; i++) {
			if(k > 0) k--;
			while(s[i + k] == s[sa[rk[i]-1] + k]) k++;
			ht[rk[i]] = k;
		}
	}
	int sz;
	template<typename T>
	void build(const T *s, int n) {
		// set s[n] = 0 if necessary
		sz = n;
		suffix_array(s, n + 1, *max_element(s, s + n) + 1);
		rmq.init(ht, n);
	}
	int lcp(int i, int j) {
		if(i == j) return sz - i;
		i = rk[i], j = rk[j];
		if(i > j) swap(i, j);
		return rmq.query(i + 1, j);
	}
#ifdef local
	template<typename T>
	void debug(const T *s, int n) {
		for(int i = 1; i <= n; i++) cout << i << ' ' << s + sa[i] << endl;
		for(int i = 1; i <= n; i++) cout << i << ' ' << ht[i] << endl;
	}
#else
#define debug(...) 42
#endif
}
using SA::build;
using SA::lcp;
```

