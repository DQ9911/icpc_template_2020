namespace fft {
  const double pi = acos(-1.0);
  struct Complex {
    double r, i;
    Complex(double x = 0, double y = 0) : r(x), i(y) {}
    Complex operator+ (const Complex& b) const {
      return Complex(r + b.r, i + b.i);
    }
    Complex operator- (const Complex& b) const {
      return Complex(r - b.r, i - b.i);
    }
    Complex operator* (const Complex& b) const {
      return Complex(r * b.r - i * b.i, r * b.i + i * b.r);
    }
  };
  Complex conj(Complex a) {
    return Complex(a.r, -a.i);
  }

  int base = 1;
  vector<int> rev = { 0, 1 };
  vector<Complex> roots = { { 0, 0 }, { 1, 0 } };

  void ensure_base(int nbase) {
    if (nbase <= base) {
      return;
    }
    rev.resize(1 << nbase);
    for (int i = 0; i < (1 << nbase); i++) {
      rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
    }
    roots.resize(1 << nbase);
    while (base < nbase) {
      double angle = 2 * pi / (1 << (base + 1));
      for (int i = 1 << (base - 1); i < (1 << base); i++) {
        roots[i << 1] = roots[i];
        double angle_i = angle * (2 * i + 1 - (1 << base));
        roots[(i << 1) + 1] = Complex(cos(angle_i), sin(angle_i));
      }
      base++;
    }
  }
  void fft(vector<Complex> &a, int n = -1) {
    if (n == -1) {
      n = a.size();
    }
    assert((n & (n - 1)) == 0);
    int zeros = __builtin_ctz(n);
    ensure_base(zeros);
    int shift = base - zeros;
    for (int i = 0; i < n; i++) {
      if (i < (rev[i] >> shift)) {
        swap(a[i], a[rev[i] >> shift]);
      }
    }
    for (int k = 1; k < n; k <<= 1) {
      for (int i = 0; i < n; i += 2 * k) {
        for (int j = 0; j < k; j++) {
          Complex z = a[i + j + k] * roots[j + k];
          a[i + j + k] = a[i + j] - z;
          a[i + j] = a[i + j] + z;
        }
      }
    }
  }

  vector<Complex> fa, fb;
  vector<int> multiply(const vector<int> &a, const vector<int> &b) {
    int need = a.size() + b.size() - 1;
    int nbase = need > 1 ? 32 - __builtin_clz(need - 1) : 0;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if (sz > (int) fa.size()) {
      fa.resize(sz);
    }
    for (int i = 0; i < sz; i++) {
      int x = (i < (int) a.size() ? a[i] : 0);
      int y = (i < (int) b.size() ? b[i] : 0);
      fa[i] = Complex(x, y);
    }
    fft(fa, sz);
    Complex r(0, -0.25 / sz);
    for (int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      Complex z = (fa[j] * fa[j] - conj(fa[i] * fa[i])) * r;
      if (i != j) {
        fa[j] = (fa[i] * fa[i] - conj(fa[j] * fa[j])) * r;
      }
      fa[i] = z;
    }
    fft(fa, sz);
    vector<int> res(need);
    for (int i = 0; i < need; i++) {
      res[i] = fa[i].r + 0.5; // watch out that fa[i].r < 0
    }
    return res;
  }
  vector<int> multiply_mod(const vector<int> &a, const vector<int> &b, int m, int eq = 0) {
    int need = a.size() + b.size() - 1;
    int nbase = need > 1 ? 32 - __builtin_clz(need - 1) : 0;
    ensure_base(nbase);
    int sz = 1 << nbase;
    if (sz > (int) fa.size()) {
      fa.resize(sz);
    }
    for (int i = 0; i < (int) a.size(); i++) {
      int x = (a[i] % m + m) % m;
      fa[i] = Complex(x & ((1 << 15) - 1), x >> 15);
    }
    fill(fa.begin() + a.size(), fa.begin() + sz, Complex {0, 0});
    fft(fa, sz);
    if (sz > (int) fb.size()) {
      fb.resize(sz);
    }
    if (eq) {
      copy(fa.begin(), fa.begin() + sz, fb.begin());
    } else {
      for (int i = 0; i < (int) b.size(); i++) {
        int x = (b[i] % m + m) % m;
        fb[i] = Complex(x & ((1 << 15) - 1), x >> 15);
      }
      fill(fb.begin() + b.size(), fb.begin() + sz, Complex {0, 0});
      fft(fb, sz);
    }
    double ratio = 0.25 / sz;
    Complex r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);
    for (int i = 0; i <= (sz >> 1); i++) {
      int j = (sz - i) & (sz - 1);
      Complex a1 = (fa[i] + conj(fa[j]));
      Complex a2 = (fa[i] - conj(fa[j])) * r2;
      Complex b1 = (fb[i] + conj(fb[j])) * r3;
      Complex b2 = (fb[i] - conj(fb[j])) * r4;
      if (i != j) {
        Complex c1 = (fa[j] + conj(fa[i]));
        Complex c2 = (fa[j] - conj(fa[i])) * r2;
        Complex d1 = (fb[j] + conj(fb[i])) * r3;
        Complex d2 = (fb[j] - conj(fb[i])) * r4;
        fa[i] = c1 * d1 + c2 * d2 * r5;
        fb[i] = c1 * d2 + c2 * d1;
      }
      fa[j] = a1 * b1 + a2 * b2 * r5;
      fb[j] = a1 * b2 + a2 * b1;
    }
    fft(fa, sz);
    fft(fb, sz);
    vector<int> res(need);
    for (int i = 0; i < need; i++) {
      long long aa = fa[i].r + 0.5;
      long long bb = fb[i].r + 0.5;
      long long cc = fa[i].i + 0.5;
      res[i] = (aa + ((bb % m) << 15) + ((cc % m) << 30)) % m;
    }
    return res;
  }
  vector<int> square_mod(const vector<int> &a, int m) {
    return multiply_mod(a, a, m, 1);
  }
}

namespace poly {
  // reference exgcd and fft::multiply_mod
  const int MOD = 1e9 + 9;
  vector<int> inv(const vector<int> &a) {
    if(a.size() == 1) {
      const int inv = exgcd(a[0], MOD).first;
      return vector<int>(1, inv < 0 ? inv + MOD : inv);
    }
    const int na = a.size(), nb = (na + 1) >> 1;
    vector<int> b(a.begin(), a.begin() + nb);
    b = inv(b);
    vector<int> c = fft::multiply_mod(b, b, MOD);
    c.resize(na);
    c = fft::multiply_mod(a, c, MOD);
    b.resize(na), c.resize(na);
    for(int i = 0; i < na; i++) {
      c[i] = (((2ll * b[i] - c[i]) % MOD) + MOD) % MOD;
    }
    return c;
  }

  // make mod function by yourself
  vector<int> divide(const vector<int> &a, const vector<int> &b) {
    const int n = a.size(), m = b.size();
    vector<int> A(a), B(b);
    reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
    A.resize(n - m + 1), B.resize(n - m + 1);
    B = inv(B);
    vector<int> C = fft::multiply_mod(A, B, MOD);
    C.resize(n - m + 1), reverse(C.begin(), C.end());
    return C;
  }

  vector<int> Mod(const vector<int> &a, const vector<int> &b) {
    vector<int> c = divide(a, b);
    c = fft::multiply_mod(b, c, MOD);
    c.resize(b.size() - 1);
    for(int i = 0; i < int(c.size()); i++) c[i] = (a[i] + MOD - c[i]) % MOD;
    return c;
  }
  vector<int> mul_mod(const vector<int> &a, const vector<int> &b, const vector<int> &_Mod) {
    vector<int> c = fft::multiply_mod(a, b, MOD);
    return Mod(c, _Mod);
  }
  inline void sub(int &x, int y) { if((x-=y)<0) x += MOD;}
  vector<int> Pow_mod(ll n, const vector<int> &Mod) {
    int pnt = 0, k = Mod.size();
    while((1ll<<pnt) <= n) pnt++;
    vector<int> res(k-1, 0); res[0] = 1;
    for(int i = pnt-1; ~i; i--) {
      res = mul_mod(res, res, Mod);
      if(n>>i&1) {
        res.push_back(0);
        for(int j = k-2; ~j; j--) res[j+1] = res[j]; res[0] = 0;
        for(int j = k-2; ~j; j--) sub(res[j],(ll)res[k-1]*Mod[j]%MOD);
        res.pop_back();
      }
    }
    return res;
  }
}
