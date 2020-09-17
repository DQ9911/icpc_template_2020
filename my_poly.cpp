namespace Poly {
	using FFT::multiply_mod;
	using FFT::sqr_mod;
	inline int add(int x, int y) {return (x+=y)>=mod?x-mod:x;}
	inline int sub(int x, int y) {return (x-=y)<0?x+mod:x;}
	int exgcd(int a, int b, int &x, int &y) {
		if(!b) return x = 1, y = 0, a;
		int d = exgcd(b, a % b, y, x);
		return y -= a / b * x, d;
	}
	int inv(int a, int mod) {
		int x, y, d = exgcd(a, mod, x, y);
		assert(d == 1);
		return add(x, mod);
	}
	poly inv(const poly &a) {
		if(a.size()==1) return {inv(a[0],mod)};
		int n = a.size(), n2 = (n + 1) / 2;
		poly r2 = inv(poly(a.begin(),a.begin()+n2));
		poly r = multiply_mod(a, sqr_mod(r2, r2));
		r.resize(n);
		for(int i = n2; i < n; i++) r[i] = add(mod,-r[i]);
		return r;
	}
}
