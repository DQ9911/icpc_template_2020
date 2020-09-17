ull pool[N];
void radix_sort(int *s, int *t) {
    static int cc[256];
    ull *z = pool;
    int n = t - s;
    for(int k = 0, j = 0; j < 8; k += 8, j++, swap(s, z)){
        memset(cc, 0, sizeof cc);
        for(int i = 0; i < n; i++) cc[s[i]>>k&255]++;
        for(int i = 1; i < 256; i++) cc[i] += cc[i - 1];
        for(int i = n - 1; i >= 0; i--) z[--cc[s[i]>>k&255]] = s[i];
    }
}
