```c++
// fail[i]等于满足s[0...z-1]=s[i-z...i-1]最大的z
template<typename T>
vector<int> getfail(const T &s, int n) {
	vector<int> fail(n + 1, -1);
	for(int i = 0, t = -1; i < n; i++) {
		while(t != -1 && s[t] != s[i]) t = fail[t];
		fail[i + 1] = ++t;
	}
	return fail;
}
```

