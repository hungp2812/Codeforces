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
    cin >> testcases;
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
// #define int long long

int n, m1, m2;

struct query {
    int u, v, w;
};
vector<query> edges, q1, q2;

void add_edges(int u, int v, int w){
    edges.pb({u, v, w});
}

void add_sm(int u, int v, int p){
    add_edges(u, v, p);
}

void add_lg(int u, int v, int p){
    add_edges(v, u, -p);
}

void add_eq(int u, int v, int p){
    add_sm(u, v, p), add_lg(u, v, p);
}

int dis[3030];

bool bellman_ford(){
    for (int i = 0; i <= n + 5; i ++) 
        dis[i] = i == n + 1 ? 0 : inf;
    for (int i = 0; i < n + 5; i ++){
        for (auto q : edges){
            int u = q.u, v = q.v, w = q.w;
            if (dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                if (i == n + 4) return 0;
            }
        }
    }
    return 1;
}

bool chk(int x){
    edges.clear();
    add_eq(n, 0, x);
    for (auto q : q1) 
        add_lg(q.v, q.u - 1, q.w);
    for (auto q : q2)
        add_sm(q.v, q.u - 1, x - q.w);
    for (int i = 0; i <= n; i++){
        if (i)
            add_sm(i, i - 1, 1), add_lg(i, i - 1, 0);
        add_edges(n + 1, i, 0);
    }
    return bellman_ford();
}

void Hollwo_Pelw () {
    cin >> n >> m1 >> m2;
    q1.clear(), q2.clear();
    for (int i = 1, l, r, w; i <= m1; i++)
        cin >> l >> r >> w, q1.pb({l, r, w});
    for (int i = 1, l, r, w; i <= m2; i++)
        cin >> l >> r >> w, q2.pb({l, r, w});
    int l = 0, r = n, ans = n;
    while (l <= r) {
        int m = l + r >> 1;
        if (chk(m)){
            ans = m;
            r = m - 1;
        }else{
            l = m + 1;
        }
    }
    cout << ans << "\n";
}

/*

./-=====>>><<<-------- DEBUG -------->>><<<=====-\.
/.................................................\
+====================== INP ======================+



+====================== OUT ======================+



+======================*****======================+
\................................................./
.\-=====>>><<<--------= END =-------->>><<<=====-/.
kekw
*/