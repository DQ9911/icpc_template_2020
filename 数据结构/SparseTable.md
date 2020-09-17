```c++
struct SparseTable {
	int n;
	vector<vector<int>> dp;
	SparseTable() { n = 0;}
	SparseTable(const vector<int> &a) {
		n = a.size();
		dp.emplace_back(a);
		for(int i = 1, L = 2; L < n; L <<= 1, i++) {
			dp.emplace_back(n - L + 1);
			for(int j = 0; j + L - 1 < n; j++) {
				dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + L / 2]);
			}
		}
	}
	int query(int l, int r) {
		int lgt = __lg(r - l + 1);
		return min(dp[lgt][l], dp[lgt][r - (1 << lgt) + 1]);
	}
};
```

