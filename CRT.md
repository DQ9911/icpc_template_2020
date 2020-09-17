```c++
template<typename T>
T CRT(T *a, T *m, int n) {
    T a0 = a[0], m0 = m[0];
    for(int i = 1; i < n; i++) {
        T k0, k1, a1 = a[i], m1 = m[i];
        T d = abs(exgcd(m0, m1, k0, k1));
        k1 = -k1;
        if(d == 0 || (a1 - a0) % d != 0) return -1;
        T mm = m0 / d * m1;
        a0 = (((a1 - a0) / d * k0) % (m1 / d) * m0 + a0) % mm;
        if(a0 < 0) a0 += mm;
        m0 = mm;
    }
    return a0;
}
```

