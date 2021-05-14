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
const int MAXN = 1e6 + 10;
const int inf = 2e9;
const ll linf = 1e18;
const ld eps = 1e-9;
#define int long long

int n, q, ans[MAXN];
vector<pair<int, int>> adj[MAXN], query[MAXN];


int sz[MAXN], mark[MAXN];

int dfs_sz(int u, int p){
    sz[u] = 1;
    for (auto vw : adj[u]) if (vw.F != p && !mark[vw.F]){
        sz[u] += dfs_sz(vw.F, u);
    }
    return sz[u];
}

int find_cen(int u, int p, int tot){
    for (auto vw : adj[u]) if (vw.F != p && !mark[vw.F])
        if (sz[vw.F] > tot / 2) return find_cen(vw.F, u, tot);
    return u;
}

vector<int> all_dep;
int h[MAXN];

void dfs_dep(int u, int p, int d = 0){
    h[u] = d;
    all_dep.push_back(d);
    for (auto vw : adj[u]) if (vw.F != p && !mark[vw.F])
        dfs_dep(vw.F, u, d + vw.S);
}

vector<int> nodes, sub_dep;

void dfs_sub(int u, int p){
    sub_dep.push_back(h[u]);
    nodes.push_back(u);
    for (auto vw : adj[u]) if (vw.F != p && !mark[vw.F])
        dfs_sub(vw.F, u);
}

void solve(int r){
    int tot = dfs_sz(r, -1);
    r = find_cen(r, -1, tot);
    
    all_dep.clear();
    dfs_dep(r, -1);
    mark[r] = 1;
    
    sort(all(all_dep));

    for (auto qr : query[r]){
        int l = qr.F, id = qr.S;
        ans[id] += upper_bound(all(all_dep), l) - all_dep.begin();
    }

    for (auto uw : adj[r]) {
        int u = uw.F, w = uw.S;
        if (!mark[u]) {
            nodes.clear();
            sub_dep.clear();
            dfs_sub(u, r);
            sort(all(sub_dep));
            for (auto v : nodes){
                for (auto qr : query[v]){
                    int l = qr.F, id = qr.S;
                    ans[id] += upper_bound(all(all_dep), l - h[v]) - all_dep.begin();
                    ans[id] -= upper_bound(all(sub_dep), l - h[v]) - sub_dep.begin();
                }
            }
        }
    }

    for (auto uw : adj[r])
        if (!mark[uw.F]) solve(uw.F);
}

void Hollwo_Pelw() {
    cin >> n >> q;
    for (int i = 1, u, v, w; i < n; i++){
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }
    for (int i = 1, u, l; i <= q; i++){
        cin >> u >> l;
        query[u].emplace_back(l, i);
    }
    solve(1);
    for (int i = 1; i <= q; i++)
        cout << ans[i] << "\n";
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