```C++
typedef long long ll;
typedef unsigned long long ull;
typedef long double ldb;
const ldb eps = 1e-6;
ull mul(ull a, ull b, ull m) {
#ifndef WIN64
  if(a >= m) a %= m; if(b >= m) b %= m;
  ull res = a * b - ull(ldb(a) * b / m + eps) * m;
  return ll(res) < 0 ? res + m : res;
#else
  return (__uint128_t) a * b % m;
#endif
}
ull power_mod(ull a, ull b, ull m) {
  ull res = 1;
  for(a %= m; b; b >>= 1, a = mul(a, a, m))
    if(b & 1) res = mul(res, a, m);
  return res;
}
bool chk(ull a, ull n) {
  if(a >= n) return 1;
  ull s = __builtin_ctzll(n - 1), d = (n - 1) >> s;
  ull x = power_mod(a, d, n);
  while(d != n - 1 && x != n - 1 && x != 1) {
    x = mul(x, x, n);
    d <<= 1;
  }
  return x == n - 1 || (d & 1);
}
bool isprime(ull n) {
  static vector<ull> a =  {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  if(n <= 1 || ((~n & 1) && n > 2)) return false;
  for(auto &e : a) if(!chk(e, n)) return false;
  return true;
}
mt19937_64 gen(time(0));
#define all(x) (x).begin(),(x).end()
vector<ull> pollard_rho(ull n) {
	if(n == 1) return {};
  if(isprime(n)) {
    return {n};
  }
  auto f = [n](ull x){ return (mul(x,x,n)+1)%n;};
  while(1) {
    ull x = gen() % n, y = f(x);
    while(x != y) {
      ull t;
      if(~n & 1) t = 2;
      else t = __gcd(x - y + n, n);
      if(t != 1) {
        auto l = pollard_rho(t), r = pollard_rho(n / t);
        l.insert(l.end(),all(r));
        return l;
      }
      x = f(x), y = f(f(y));
    }
  }
}
```

