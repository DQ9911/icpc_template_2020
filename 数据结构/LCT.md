```c++
namespace LCT {
	int ch[N][2], fa[N], stk[N], top;
	bool rev[N];
	void up(int x) {}
	void down(int x) {
		if(rev[x]) {
			rev[x] = 0;
			rev[ch[x][0]] ^= 1;
			rev[ch[x][1]] ^= 1;
			swap(ch[x][0], ch[x][1]);
		}
	}
	bool isroot(int x) { return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	void rot(int x) {
		int y = fa[x], z = fa[y];
		int k = ch[y][1] == x;
		if(!isroot(y)) ch[z][ch[z][1]==y] = x;
		fa[x] = z;
		ch[y][k] = ch[x][k^1]; fa[ch[x][k^1]] = y;
		ch[x][k^1] = y; fa[y] = x;
		up(x), up(y);
	}
	void splay(int x) {
		stk[top = 0] = x;
		for(int i = x; !isroot(i); i = fa[i]) stk[++top] = fa[i];
		for(int i = top; i >= 0; i--) down(stk[i]);
		while(!isroot(x)) {
			int y = fa[x], z = fa[y];
			if(!isroot(y)) {
				if((ch[y][0]==x)!=(ch[z][0]==y)) rot(x);
				else rot(y);
			}
			rot(x);
		}
	}
	void access(int x) { for(int t=0; x; splay(x),ch[x][1]=t,up(x),t=x,x=fa[x]);}
	void makeroot(int x) { access(x); splay(x); rev[x]^=1;}
	int findroot(int x) { access(x); splay(x); while(ch[x][0])x=ch[x][0]; return x;}
	void split(int x, int y) { makeroot(x); access(y); splay(y);}
	int anc[N];
	// 针对基环树...
	void link(int x, int y) {
		makeroot(x);
		anc[x] = 0;
		if(findroot(y) == x) anc[x] = y;
		else fa[x] = y;
	}
	void cut(int x) {
		int y = findroot(x);
		makeroot(x);
		ch[x][0] = fa[ch[x][0]] = 0;
		if(anc[y]&&findroot(y)!=findroot(anc[y])) {
			link(y, anc[y]);
		} else if(y == x) anc[y] = 0;
	}
}
using namespace LCT;
```

