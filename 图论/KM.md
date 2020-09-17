```c++
template<typename T, int N, T INF>
struct KM {
	T a[N][N];
	T U[N], V[N];
	T minDist[N];
	bool used[N];
	int way[N];
	int mt[N];
	int n;
	void init(int _n) {
		n = _n;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				cin >> a[i][j];
	}
	void hungarian() {
		memset(mt, 0, sizeof(mt[0]) * (n + 1));
		memset(U, 0, sizeof(U[0]) * (n + 1));
		memset(V, 0, sizeof(V[0]) * (n + 1));
		for (int it = 1; it <= n; it++) {
			for (int i = 0; i <= n; i++) {
				way[i] = 0;
				minDist[i] = INF;
				used[i] = false;
			}
			mt[0] = it;
			int col = 0;
			while(mt[col]) {
				used[col] = 1;
				int row = mt[col];
				int ncol = -1;
				T delta = INF;
				for (int c = 0; c <= n; c++) {
					if (used[c]) continue;
					if (minDist[c] > a[row][c] + V[row] + U[c]) {
						minDist[c] = a[row][c] + V[row] + U[c];
						way[c] = col;
					}
					if (minDist[c] < delta) {
						delta = minDist[c];
						ncol = c;
					}
				}
				for (int c = 0; c <= n; c++) {
					if (used[c]) {
						U[c] += delta;
						V[mt[c]] -= delta;
					} else {
						minDist[c] -= delta;
					}
				}
				col = ncol;
			}
			while(col) {
				int ncol = way[col];
				swap(mt[col], mt[ncol]);
				col = ncol;
			}
		}
	}
	T min_cost() {
		hungarian();
		T ret = 0;
		for(int i = 1; i <= n; i++) {
			ret -= U[i] + V[i];
		}
		return ret;
	}
};
```

