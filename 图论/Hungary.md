```c++
const int N = 1010;
struct Hungary {
  int n, m, now, tot;
  int vis[N], linker[N], head[N];
  struct edge{ int v, nxt;} e[N*4];
  void init(int _n, int _m) {
    n = _n; m = _m; tot = 0;
    memset(vis, -1, m*4);
    memset(linker, -1, m*4);
    memset(head, -1, n*4);
  }
  void add(int u, int v) {
    e[tot]={v, head[u]}, head[u]=tot++;
  }
  bool dfs(int u){
    for(int i=head[u];~i;i=e[i].nxt){
      int v=e[i].v;
      if(vis[v]==now)continue;
      vis[v]=now;
      if(linker[v]==-1||dfs(linker[v])){
        linker[v]=u; return true;
      }
    }
    return false;
  }
  int maxmatch(){
    int ret=0;
    for(now=0;now<n;now++){
      if(dfs(now))ret++;
    }
    return ret;
  }
} bp;

```

