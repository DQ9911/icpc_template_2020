```C++
namespace SAM {
    const int M = N << 1;
    int nxt[M][26], len[M], fa[M], sz, last;
    int newnode(int ps=0) {
      memcpy(nxt[sz], nxt[ps], sizeof nxt[sz]);
      return sz++;
    }
    void init() {
      sz = 1;
      last = newnode();
    }
    void extend(int ch) {
        int p = last, np = last = newnode();
        len[np] = len[p] + 1;
        for (; p && !nxt[p][ch]; p = fa[p]) nxt[p][ch] = np;
        if (!p) { fa[np] = 1; return; }
        int q = nxt[p][ch];
        if (len[p] + 1 == len[q]) fa[np] = q;
        else {
            int nq = newnode(q);
            len[nq] = len[p] + 1;
            fa[nq] = fa[q];
            fa[np] = fa[q] = nq;
            for (; nxt[p][ch] == q; p = fa[p]) nxt[p][ch] = nq;
        }
    }
};
```



