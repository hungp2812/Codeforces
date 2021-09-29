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
const int modm = allmod[0];
const int MAXN = 2e5 + 5;
const int inf = 2e9;
const ll linf = 1e18;
const ld eps = 1e-9;
#define int long long

int __calc_phi__(int mod) {
    int phi = mod;
    for (int i = 2; i * i <= mod; i++){
        if (mod % i == 0) {
            phi /= i;
            phi *= (i - 1);
            while (mod % i == 0)
                mod /= i;
        }
    }
    if (mod > 1){
        phi /= mod;
        phi *= (mod - 1);
    }
    return phi;
}

int mod, n, phi, sz[MAXN], res, inv10;
vector<pair<int, int>> adj[MAXN];

inline int mul(int a, int b){
    return a * b % mod;
}

int binpow(int a, int x){
    int r = 1;
    while (x) {
        if (x&1) r = mul(r, a); 
        x >>= 1; a = mul(a, a);
    }
    return r;
}

bool mark[MAXN];


int dfs_sz(int u, int p){
    sz[u] = 1;
    for (auto vw : adj[u]) if (vw.first != p && !mark[vw.first])
        sz[u] += dfs_sz(vw.first, u);
    return sz[u];
}

int find_cen(int u, int p, int tot){
    for (auto vw : adj[u]) if (vw.first != p && !mark[vw.first])
        if (sz[vw.first] > tot / 2) return find_cen(vw.first, u, tot);
    return u;
}

map<int, int> allup, alldown, subup, subdown;
int h[MAXN], up[MAXN], down[MAXN];

void dfsall(int u, int p){
    allup[up[u]] ++, alldown[mul(down[u], binpow(inv10, h[u]))] ++;
    
    cout << u << ' ' << up[u] << ' ' << down[u] << endl;

    for (auto vw : adj[u]) if (vw.first != p && !mark[vw.first]) {
        h[vw.first] = h[u] + 1;
        up[vw.first] = (up[u] + mul(vw.second, binpow(10, h[u]))) % mod;
        down[vw.first] = (down[u] * 10 + vw.second) % mod;
        dfsall(vw.first, u);
    }
} 

void dfssub(int u, int p){
    subup[up[u]] ++, subdown[mul(down[u], binpow(inv10, h[u]))] ++;
    allup[up[u]] --, alldown[mul(down[u], binpow(inv10, h[u]))] --;

    for (auto vw : adj[u]) if (vw.first != p && !mark[vw.first]) {
        dfssub(vw.first, u);
    }
}

void centroid_decomp(int r){
    int tot = dfs_sz(r, r);
    r = find_cen(r, r, tot);
    
    cout << "root : " << r << endl;
    allup.clear(), alldown.clear();
    up[r] = down[r] = 0;
    dfsall(r, r);


    for (auto vw : adj[r]){
        if (!mark[vw.first]) {
            subup.clear(), subdown.clear();
            dfssub(vw.first, r);
            for (auto vp : subup)
                res += vp.S * alldown[(mod - vp.F) % mod];
            for (auto vp : subdown)
                res += vp.S * allup[(mod - vp.F) % mod];

            for (auto vp : subup)
                allup[vp.F] += vp.S;
            for (auto vp : subdown)
                alldown[vp.F] += vp.S;
        }
    }

    cout << res << endl;

    mark[r] = 1;
    for (auto vw : adj[r]) 
        if (!mark[vw.first]) centroid_decomp(vw.first);
}

void Hollwo_Pelw() {
    cin >> n >> mod;
    phi = __calc_phi__(mod);
    inv10 = binpow(10, phi);

    for (int i = 1, u, v, w; i < n; i++){
        cin >> u >> v >> w, ++ u, ++ v; 
        adj[u].emplace_back(v, w), adj[v].emplace_back(u, w);
    }

    centroid_decomp(1);
    cout << res;
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
