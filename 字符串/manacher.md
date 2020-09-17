```C++
// 以i为中心的最长奇回文子串为s[i - f[i] + 1, i + f[i] - 1]...
template<typename T>
vector<int> manacher(const T &s, int n) {
    string ts(2 * n + 3, '0');
    for(int i = 1; i <= n; i++) {
        ts[i * 2] = s[i - 1];
        ts[i * 2 + 1] = '#';
    }
    ts[0] = '!'; ts[1] = '#';
    ts[2 * n + 2] = '$';
    vector<int> f(2 * n + 1);
    int mid = 1, r = 1;
    for(int i = 1; i <= 2 * n; i++) {
        f[i] = i < r ? min(r - i, f[2 * mid - i]) : 1;
        while(ts[i - f[i]] == ts[i + f[i]]) f[i]++;
        if(i + f[i] > r) r = i + f[i], mid = i;
    }
    return f;
}
```

