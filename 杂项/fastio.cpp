namespace Fastio {
	const int SZ = 1<<20;
	char buf[SZ], *p1 = buf, *p2 = buf;
	bool ioeof = 0;
	inline char nc() {
		return (ioeof||(p1==p2&&(p2=(p1=buf)+fread(buf,1,SZ,stdin),p1==p2))?(ioeof=1,EOF):*p1++;
	}
	int scan(char *s) {
		while(isblank(*s = nc()));
		if(*s == EOF) return *s = '\0', EOF;
		s++;
		while(!isblank(*s = nc())) s++;
		return *s = '\0', 1;
	}
	template<typename Head>
	int scan(Head &x) {
		char c; while(!isdigit(c = nc()) && c != EOF);
		if(c == EOF) return c;
		for(x = 0; isdigit(c); c = nc())
			x = x * 10 + c - '0';
		return 1;
	}
	template<typename Head, typename...Tail>
	int scan(Head &x, Tail&...tail) {
		return scan(x), scan(tail...);
	}
	struct FO {
		int tot = 0;
		char obuf[SZ + 200];
		char t[41], *o1 = t + 40, *o2 = t + 40;
		~FO() { fflush(); fclose(stdout);}
		void fflush() {
			fwrite(obuf, 1, tot, stdout);
			tot = 0;
		}
		void print(int x) {
			if(x < 0) x = -x, obuf[tot++] = '-';
			if(x == 0) obuf[tot++] = '0';
			else {
				while(x) *--o1 = x % 10 + '0', x /= 10;
				memcpy(obuf + tot, o1, o2 - o1);
				tot += o2 - o1; o1 = o2;
			}
			if(tot > SZ) fflush();
		}
		void addchar(char ch) {
			obuf[tot++] = ch;
			if(tot > SZ) fflush();
		}
		void println(int x) {
			print(x); addchar('\n');
		}
	} os;
}
using Fastio::os;
using Fastio::scan;
