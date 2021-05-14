/*
 /+===================================================+\
//+---------------------------------------------------+\
|.|\...>>>>>>> Hollwo_Pelw's 2nd template<<<<<<<...//|.|
\+---------------------------------------------------+//
 \+===================================================+/
*/
#include <bits/stdc++.h>
using namespace std;
// type
typedef long long ll;
typedef long double ld;
// pair
#define F                   first
#define S                   second
#define pii                 pair<int, int>
#define pll                 pair<ll, ll>
#define pdd                 pair<ld, ld>
// vector & !!?(string)
#define eb                  emplace_back
#define pb                  push_back
#define all(a)              a.begin(), a.end()
#define rall(a)             a.rbegin(), a.rend()
#define sz(a)               a.size()
// I/O
#define setpre(n)           fixed << setprecision(n)
#define Ptest(x)            return cout << x << endl, (void) 0;
bool endline = false;
template<class T>
istream& operator >> (istream& inp, vector<T>& v){
    for (auto& it : v) inp >> it;
    return inp;
}
template<class T>
ostream& operator << (ostream& out, vector<T>& v){
    for (auto& it : v) out << it << (endline ? "\n" : " ");
    return out;
}
template<class T, class U>
istream& operator >> (istream& inp, pair<T, U>& v){
    inp >> v.F >> v.S;
    return inp;
}
template<class T, class U>
ostream& operator << (ostream& out, pair<T, U>& v){
    out << v.F << ' ' << v.S;
    return out;
}
void debug(){
    cout << endl;
}
template <typename H, typename... T>
void debug(H a, T... b){
    cout << a << ' ';
    debug(b...);
}
// geometry calculate
#define pi                  acos(-1.0)
#define g_sin(a)            sin(a*pi/180)
#define g_cos(a)            cos(a*pi/180)
#define g_tan(a)            tan(a*pi/180)
// set val
#define ms0(a)              memset(a,        0, sizeof(a));
#define ms1(a)              memset(a,        1, sizeof(a));
#define msn1(a)             memset(a,       -1, sizeof(a));
#define msinf(a)            memset(a, 0x3f3f3f, sizeof(a));

void FAST_IO(string filein = "", string fileout = "", string fileerr = ""){
    if (fopen(filein.c_str(), "r")){
        freopen(filein.c_str(), "r", stdin);
        freopen(fileout.c_str(), "w", stdout);
        #ifdef hollwo_pelw_local
            freopen(fileerr.c_str(), "w", stderr);
        #endif
    }
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
}

void Hollwo_Pelw();

signed main(){
    #ifdef hollwo_pelw_local
        FAST_IO("input.inp", "output.out", "error.err");
        auto start = chrono::steady_clock::now();
    #else
        FAST_IO(".inp", ".out");
    #endif
    int testcases = 1;
    // cin >> testcases;
    for (int test = 1; test <= testcases; test++){
        // cout << "Case #" << test << ": ";
        Hollwo_Pelw();
    }
    #ifdef hollwo_pelw_local
        auto end = chrono::steady_clock::now();
        cout << endl;
        cout << "Excution time : " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
    #endif
    return 0;
}

// constant
const int allmod[3] = {(int) 1e9 + 7, 998244353, (int) 1e9 + 9};
const int mod = allmod[0];
const int MAXN = 2e5 + 5;
const int inf = 2e9;
const ll linf = 1e18;
const ld eps = 1e-9;
// #define int long long

int n, m;

struct disjoint_set_union {
    int par[MAXN];
    disjoint_set_union () {
        for (int i = 1; i < MAXN; i++)
            par[i] = i;
    }
    int find(int u){
        return par[u] = (par[u] == u ? u : find(par[u]));
    }

    bool merge(int u, int v){
        if ((u = find(u)) == (v = find(v)))
            return 0;
        par[u] = v; return 1;
    }
} dsu;

struct edge {
    int u, v, w, id;
    bool operator < (const edge & oth) const {
        return w < oth.w;
    }
};

vector<pii> adj[MAXN];
int par[MAXN][19], mn[MAXN][19];
int S[MAXN], E[MAXN], timer;
int sz[MAXN], nxt[MAXN];

void get_sz(int u, int p, int w){
    par[u][0] = p, mn[u][0] = w;
    for (int i = 1, v; i <= 18; i++){
        v = par[u][i - 1]; par[u][i] = par[v][i - 1];
        mn[u][i] = max(mn[v][i - 1], mn[u][i - 1]);
    }
    sz[u] = 1;
    nxt[u] = u;
    for (auto &v : adj[u]){
        if (v.F == p)
            swap(adj[u].back(), v);
        if (v.F == p) 
            continue;
        get_sz(v.F, u, v.S);
        sz[u] += sz[v.F];
        if (sz[v.F] > sz[adj[u][0].F])
            swap(adj[u][0], v);
    }
    if (adj[u].back().F == p)
        adj[u].pop_back();
}

void dfs_hld(int u){
    S[u] = ++ timer;
    for (auto &v : adj[u]){
        if (v == adj[u][0])
            nxt[v.F] = nxt[u];
        dfs_hld(v.F);
    }
    E[u] = timer;
}

void init_hld(){
    get_sz(1, 1, -inf);
    dfs_hld(1);
}

bool is_ancestor(int u, int v){
    return S[u] <= S[v] && E[v] <= E[u];
}

int lca(int u, int v){
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = 18; i >= 0; i--){
        if (!is_ancestor(par[u][i], v))
            u = par[u][i];
    }
    return par[u][0];
}

int lift_val(int u, int p){
    if (u == p) return -inf;
    int res = -inf;
    for (int i = 18; i >= 0; i--){
        if (!is_ancestor(par[u][i], p)){
            res = max(res, mn[u][i]);
            u = par[u][i];
        }
    }
    return max(res, mn[u][0]);
}

int lift(int u, int p){
    for (int i = 18; i >= 0; i--){
        if (!is_ancestor(par[u][i], p)){
            u = par[u][i];
        }
    }
    return u;
}

struct segment_tree {
    #define left id << 1, tl, tm
    #define right id << 1 | 1, tm + 1, tr
    int st[MAXN << 2], lz[MAXN << 2];
    segment_tree() {
        for (int i = 1; i < (MAXN << 2); i++)
            st[i] = lz[i] = inf;
    }
    void apply(int id, int v) {
        lz[id] = min(lz[id], v);
        st[id] = min(st[id], v);
    }
    void push(int id){
        apply(id << 1, lz[id]);
        apply(id << 1 | 1, lz[id]);
    }
    void upd(int l, int r, int v, int id = 1, int tl = 1, int tr = n){
        if (l > r || l > tr || tl > r) return ;
        if (l <= tl && tr <= r) return apply(id, v);
        int tm = tl + tr >> 1; push(id);
        upd(l, r, v, left), upd(l, r, v, right);
        st[id] = min(st[id << 1], st[id << 1 | 1]);
    }
    int query(int p, int id = 1, int tl = 1, int tr = n){
        if (tl == tr) return st[id];
        int tm = tl + tr >> 1;
        push(id);
        if (p <= tm)
            return query(p, left);
        return query(p, right);
    }
} segtree;

void upd_path(int u, int p, int w){
    while (1) {
        if (nxt[u] == nxt[p]){
            // cerr << "upd " << S[p] << " " << S[u] << " " << w << endl;
            segtree.upd(S[p], S[u], w);
            return ;
        }
        // cerr << "upd " << S[nxt[u]] << " " << S[u] << " " << w << endl;
        segtree.upd(S[nxt[u]], S[u], w);
        u = par[nxt[u]][0];
    }
}

int get_path(int u, int v, int w){
    int l = lca(u, v);
    if (l != u) upd_path(u, lift(u, l), w);
    if (l != v) upd_path(v, lift(v, l), w);
    return max(lift_val(u, l), lift_val(v, l));
}

int ans[MAXN];

void Hollwo_Pelw() {
    cin >> n >> m;
    vector<edge> edges;
    for (int i = 1, u, v, w; i <= m; i++){
        cin >> u >> v >> w;
        edges.pb({u, v, w, i});
    }
    sort(all(edges));
    vector<edge> mst, query;
    for (auto ed : edges){
        int u = ed.u, v = ed.v, w = ed.w;
        if (dsu.merge(u, v)){
            // cout << u << ' ' << v << ' ' << w << endl;
            adj[u].eb(v, w);
            adj[v].eb(u, w);
            mst.pb(ed);
        }else{
            query.pb(ed);
        }
    }
    init_hld();
    // for (int i = 1; i <= n; i++){
    //     cerr << S[i] << " " << E[i] << endl;
    // }
    for (auto ed : query){
        ans[ed.id] = get_path(ed.u, ed.v, ed.w);
    }
    for (auto ed : mst){
        int u = ed.u, v = ed.v;
        if (par[v][0] == u)
            swap(u, v);
        ans[ed.id] = segtree.query(S[u]);
        if (ans[ed.id] == inf) ans[ed.id] = 0;
    }
    for (int i = 1; i <= m; i++){
        cout << ans[i] - 1 << " ";
    }
}

/*

./-=====>>><<<-------- DEBUG -------->>><<<=====-\.
/.................................................\
+====================== INP ======================+



+====================== OUT ======================+



+======================*****======================+
\................................................./
.\-=====>>><<<--------= END =-------->>><<<=====-/.

*/