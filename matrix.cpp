|
struct Matrix {
#define rep(i) for(int i=0;i<S;i++)
	static const int S = 64;
	int e[S][S];
	void clear() {memset(e, 0, sizeof e);}
	Matrix() { clear();}
	const int *operator [] (int i)const { return e[i];}
	int *operator [] (int i) { return e[i];}
	void E() { clear(); rep(i)e[i][i]=1;}
	Matrix operator * (const Matrix&rhs)const {
		Matrix res;
		rep(i)rep(k)if(e[i][k])rep(j)
			res[i][j]=(res[i][j]+(ll)e[i][k]*rhs[k][j])%mod;
		return res;
	}
	Matrix power(ll n) const {
		Matrix a = *this, res;
		for(res.E(); n; n>>=1,a=a*a)
			if(n&1) res=res*a;
		return res;
	}
#undef rep
};
