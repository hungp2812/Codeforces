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

void FAST_IO(string filein = "", string fileout = ""){
    if (fopen(filein.c_str(), "r")){
        freopen(filein.c_str(), "r", stdin);
        freopen(fileout.c_str(), "w", stdout);
    }
    cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
}

void Hollwo_Pelw();

signed main(){
    #ifdef hollwo_pelw_local
        FAST_IO("input.inp", "output.out");
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
const int mod = allmod[1];
const int MAXN = 1e5 + 5;
const int inf = 2e9;
const ll linf = 1e18;
#define int long long


// :) :V :D :| :\ :( :'( :* :3 <(") (^^^) (y) (n) :O :P O_O T_T >_< -_- 8-) 8-| ^_^ 3:) O:) ;) >:(

int n, par[3030], sz[3030], nd[3030], tot, ok, ans;

struct edge {
    int u, v, c;
    bool operator < (const edge & oth) const {
        return c < oth.c;
    }
} edges[3030];

int find(int u){
    return par[u] = (par[u] == u ? u : find(par[u]));
}

void merge(int u, int v){
    u = find(u), v = find(v);
    sz[u] += sz[v];
    nd[u] += nd[v];
    par[v] = u;
    if (sz[u] > tot - nd[u])
        ok = 0;
}

void Hollwo_Pelw() {
    cin >> n;
    for (int i = 1, u, v, c; i < n; i++){
        cin >> u >> v >> c;
        edges[i] = {u, v, c};
    }

    ok = 1; 
    sort(edges + 1, edges + n);
    for (int i = 1; i <= n; i++){
        par[i] = i, sz[i] = 1;
        cin >> nd[i];
        tot += nd[i];
    }
    for (int i = 1; i <= n; i++)
        if (tot == nd[i]) Ptest(0);
    ans = edges[1].c;
    for (int i = 1; i < n; ){
        int j = i;
        while (j < n && edges[i].c == edges[j].c){
            merge(edges[j].u, edges[j].v), ++ j;
        }
        i = j;
        if (ok) ans = edges[i].c;
    }
    cout << ans;
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