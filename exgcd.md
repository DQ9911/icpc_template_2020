```c++
template<typename T>
T exgcd(T a, T b, T &x, T &y) {
    if(!a || !b) return x = !!a, y = !!b, a + b;
    T d = exgcd(b, a % b, y, x);
    return y -= a / b * x, d;
}
```

