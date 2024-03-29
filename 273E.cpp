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
const int MAXN = 2020;
const int inf = 2e9;
const ll linf = 1e18;
const ld eps = 1e-9;
#define int long long

int l[MAXN], r[MAXN], g[MAXN], n, p, cnt[MAXN], dp[MAXN][4], idx;

inline int mex(int a, int b){
    for (int i = 0; ; i++)
        if (i != a && i != b) return i; 
}

void sadd(int & a, int b){
    a = (a + b % mod) % mod;
}

void __pre_calc__() {
    l[0] = 1, r[0] = 3, g[0] = 0;
    while (1) {
        if (r[idx] > p){
            r[idx] = p + 1;
            break ;
        }
        ++ idx;
        l[idx] = r[idx - 1];
        int len = inf, v1, v2;
        {
            int to = l[idx] / 3, pos = 0;
            while (to >= r[pos] && pos < idx) pos ++;
            len = min(len, r[pos] - to), v1 = g[pos];
        }
        {
            int to = l[idx] - l[idx] / 3, pos = 0;
            while (to >= r[pos] && pos < idx) pos ++;
            len = min(len, r[pos] - to), v2 = g[pos];
        }
        r[idx] = l[idx] + len;
        g[idx] = mex(v1, v2);
        if (g[idx] == g[idx - 1])
            r[idx - 1] = r[idx], idx --; 
    }
    // for (int i = 0; i <= idx; i++)
    //     cout << l[i] << ' ' << r[i] << ' ' << g[i] << endl;
    for (int i = 0; i <= idx; i++)
        sadd(cnt[g[i]], (2 * p - l[i] - r[i] + 1) * (r[i] - l[i]) / 2);
}

void Hollwo_Pelw() {
    cin >> n >> p;
    __pre_calc__();
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= 3; j++)
            for (int k = 0; k <= 3; k++){
                sadd(dp[i][j], dp[i - 1][k] * cnt[k ^ j]);
            }
    int ans = 0;
    for (int i = 1; i <= 3; i++)
        sadd(ans, dp[n][i]);
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