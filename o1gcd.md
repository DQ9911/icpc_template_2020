```c++
// O(N)预处理,O(1)计算...
const int N = 1e7 + 10;
const int B = sqrt(N) + 10;
bitset<N> np;
int p[N>>3], pn, d[N][3];
int g[B][B];
void init() {
	for(int i = 0; i < B; i++) {
		g[i][0] = g[0][i] = i;
		for(int j = 1; j <= i; j++)
			g[i][j] = g[j][i] = g[i % j][j];
	}
	d[1][0] = d[1][1] = d[1][2] = 1;
	for(int i = 2; i < N; i++) {
		d[i][0] = d[i][1] = d[i][2] = 1;
		if(!np[i]) p[pn++] = i, d[i][0] = i;
		for(int j = 0, z; j < pn && (z = i * p[j]) < N; j++) {
			np[z] = 1;
			d[z][2] *= p[j];
			if(d[z][2] > d[z][1]) {
				swap(d[z][2], d[z][1]);
				if(d[z][1] > d[z][0]) {
					swap(d[z][1], d[z][0]);
				}
			}
			if(i % p[j] == 0) break;
		}
	}
}
int quickgcd(int a, int b) {
	if(!a || !b) return a + b;
	if(a < b) swap(a, b);
	int r = 1;
	for(int i = 0, z; i < 3; i++) {
		if(d[b][i] == 1) break;
		z = d[b][0];
		if(z < B) {
			z = g[a % z][z];
			r *= z; a /= z;
		} else if(a % z == 0) {
			a /= z; r *= z;
		}
	}
	return r;
}
```

