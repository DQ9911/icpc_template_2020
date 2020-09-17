

```c++
template<typename T>
vector<int> z_function(const T&s, int n) {
	vector<int> z(n);
	for(int i = 1, x = 0, y = 0; i < n; i++) {
		if(i <= y) z[i] = min(y - i, z[i - x]);
		while(i + z[i] < n && s[i + z[i]] == s[z[i]]) ++z[i];
		if(y <= i + z[i]) x = i, y = i + z[i];
	}
	z[0] = n;
	return z;
}
```