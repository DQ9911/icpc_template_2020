```c++
namespace SAIS {
#define rep(i, n) for(int i = 0; i < n; i++)
#define per(i, n) for(int i = n - 1; i >= 0; i--)
	int sa[N], rk[N], ht[N], s[N<<1], t[N<<1], p[N], cnt[N], cur[N];
	void sais(int n, int m, int *s, int *t, int *p) {
		int n1 = t[n-1] = 0, ch = rk[0] = -1, *s1 = s+n;
		auto pushS = [&](int x) {sa[cur[s[x]]--] = x;};
		auto pushL = [&](int x) {sa[cur[s[x]]++] = x;};
		auto inducedSort = [&](int *v) {
			fill_n(sa, n, -1); fill_n(cnt, m, 0);
			rep(i, n) cnt[s[i]]++;
			rep(i, m-1) cnt[i+1] += cnt[i];
			rep(i, m) cur[i] = cnt[i]-1;
			per(i, n1) pushS(v[i]);
			rep(i, m-1) cur[i+1] = cnt[i];
			rep(i, n) if (sa[i] > 0 && t[sa[i]-1]) pushL(sa[i]-1);
			rep(i, m) cur[i] = cnt[i]-1;
			per(i, n) if (sa[i] > 0 && !t[sa[i]-1]) pushS(sa[i]-1);
		};
		per(i, n-1) t[i] = s[i] == s[i+1] ? t[i+1] : s[i] > s[i+1];
		rep(i, n-1) rk[i+1] = t[i] && !t[i+1] ? (p[n1] = i+1, n1++) : -1;
		inducedSort(p);
		for (int i = 0, x, y; i < n; i++) {
			if(rk[sa[i]] == -1) continue;
			x = rk[sa[i]];
			if (ch >= 1 && p[x+1] - p[x] == p[y+1] - p[y]) {
				for (int j = p[x], k = p[y]; j <= p[x+1]; j++, k++) {
					if (s[j]*2+t[j] != s[k]*2+t[k]) {
						ch++; break;
					}
				}
			} else ch++;
			s1[y = x] = ch;
		}
		if (ch+1 < n1) {
			sais(n1, ch+1, s1, t+n, p+n1);
		} else rep(i, n1) sa[s1[i]] = i;
		rep(i, n1) s1[i] = p[sa[i]];
		inducedSort(s1);
	}
	int sz;
	template<typename T>
	int mapCharToInt(int n, const T *str) {
		int m = *max_element(str, str+n);
		fill_n(rk, m+1, 0);
		rep(i, n) rk[str[i]] = 1;
		rep(i, m) rk[i+1] += rk[i];
		rep(i, n) s[i] = rk[str[i]] - 1;
		return rk[m];
	}
	// Ensure that str[n] is the unique lexicographically smallest character in str.
	template<typename T>
	void suffixArray(int n, const T *str) {
		sz = n;
		int m = mapCharToInt(++n, str);
		sais(n, m, s, t, p);
		rep(i, n) rk[sa[i]] = i;
		for (int i = 0, h = ht[0] = 0; i < n-1; i++) {
			int j = sa[rk[i]-1];
			while (i+h < n && j+h < n && s[i+h] == s[j+h]) h++;
			if (ht[rk[i]] = h) h--;
		}
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
		rep(i, n+1) cout << i << ' ' << s + sa[i] << endl;
		rep(i, n+1) cout << i << ' ' << ht[i] << endl;
	}
#else
#define debug(...) if(0) cout << "a" << endl;
#endif
#undef rep
#undef per
}
using SAIS::lcp;
using SAIS::sa;
using SAIS::ht;
using SAIS::rk;
```

