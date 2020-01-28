```c++
template<typename T>
vector<int> getfail(const T &s, int n) {
    vector<int> fail(n + 1, -1);
    for(int i = 1, t = -1; i <= n; i++) {
        while(t != -1 && s[t] != s[i]) t = fail[t];
        fail[i] = ++t;
    }
    return fail;
}
```

