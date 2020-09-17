cdq分治求解二维lis(三维偏序)
```c++
typedef long long ll;
typedef pair<int, double> pid;
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
const int N = 5e4 + 7;

int m;
pid bit[N];
void up(pid &a, const pid&b){
    if(a.fi < b.fi) a = b;
    else if(a.fi == b.fi) a.se += b.se;
}
void add(int x, const pid &b) {
    for(; x <= m; x += x&-x) up(bit[x], b);
}
void clear(int x) {
    for(; x <= m; x += x&-x) bit[x] = pid(0, 0);
}
pid query(int x) {
    pid res = pid(0, 0);
    for(; x; x -= x&-x) up(res, bit[x]);
    return res;
}

struct Info {
    int h, v, id;
    bool operator < (const Info &rhs)const {
        if(h != rhs.h) return h < rhs.h;
        if(v != rhs.v) return v < rhs.v;
        return id < rhs.id;
    }
} info[N], t[N];


pid la[N], ra[N], *ans;
void bruteforce(int l, int r){
    for(int i = l; i <= r; i++) {
        for(int j = i + 1; j <= r; j++) {
            if(info[j].h >= info[i].h && info[j].v >= info[i].v) {
                pid t = ans[info[i].id]; t.fi++;
                up(ans[info[j].id], t);
            }
        }
    }
}
void work(int l, int r) {
    if(l == r) return;
    int mid = (l + r) >> 1;
    work(l, mid);
    for(int i = mid + 1; i <= r; i++) t[i] = info[i];
    sort(t + mid + 1, t + r + 1);
    int p = l, q = mid + 1;
    while(q <= r) {
        if(p <= mid && info[p].h <= t[q].h) {
            add(info[p].v, ans[info[p].id]);
            p++;
        } else {
            pid tt = query(t[q].v); tt.fi++;
            up(ans[t[q].id], tt);
            q++;
        }
    }
    for(int i = l; i < p; i++) clear(info[i].v);
    work(mid + 1, r);
    inplace_merge(info + l, info + mid + 1, info + r + 1);
}
```

