/*
 /+==================================================+\
//+--------------------------------------------------+\\
|.|\\...>>>>>>> Hollwo_Pelw(ass) 's code <<<<<<<...//|.|
\\+--------------------------------------------------+//
 \+==================================================+/
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
#define len(a)              a.length()
// I/O
#define open(file, in, out) if (fopen(file in, "r")) {        \
                                freopen(file in, "r", stdin);  \
                                freopen(file out, "w", stdout); \
                            }
#define FAST_IO             std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define setpre(n)           fixed << setprecision(n)
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
#define debug(x)            cout << #x << " : " << endl << x << endl;
#define Ptest(x)            return cout << x << endl, (void) 0;
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
// constant
const int mod1 = 998244353, mod = 1e9 + 7;
const int MAXN = 2e5 + 5 , MAXM = 3e5 + 5;
const int inf = 2e9; const ll linf = 1e18;
// code
#define left node << 1, tl, tm
#define right node << 1 | 1, tm + 1, tr
#define int long long

int n, m, val[MAXN];
pii pf[MAXN], sf[MAXN];

string s;

void Solve() {
    cin >> n >> m >> s;
    int cur = 0;
    for (int i = 1; i <= n; i++){
        if (s[i - 1] == '+') cur ++;
        if (s[i - 1] == '-') cur --;
        val[i] = cur;
    }
    pf[0] = {0, 0};
    sf[n + 1] = {val[n], val[n]};
    for (int i = 1; i <= n; i++){
        pf[i] = pf[i - 1];
        pf[i].F = max(pf[i].F, val[i]);
        pf[i].S = min(pf[i].S, val[i]);
    }
    for (int i = n; i >= 1; i--){
        sf[i] = sf[i + 1];
        sf[i].F = max(sf[i].F, val[i]);
        sf[i].S = min(sf[i].S, val[i]);
    }
    while(m --){
        int l, r;
        cin >> l >> r;
        // cout << pf[l - 1].F << ' ' << pf[l - 1].S << endl;
        // cout << sf[r + 1].F << ' ' << sf[r + 1].S << endl;
        int v = val[l - 1] - val[r];
        pii bst = pf[l - 1];
        // cout << bst.F << ' ' << bst.S << endl;
        bst.F = max(bst.F, v + sf[r + 1].F);
        bst.S = min(bst.S, v + sf[r + 1].S);
        // cout << bst.F << ' ' << bst.S << ' ';
        cout << bst.F - bst.S + 1 << endl;
    }
}

signed main(){
    open("", ".inp", ".out");
    FAST_IO; int TC = 1;
    cin >> TC;
    while(TC--) Solve();
    return 0;
}
/*

\/-=====>>><<<-------- DEBUG -------->>><<<=====-\/
/\.............................................../\
+====================== INP ======================+


+====================== OUT ======================+


+======================*****======================+
\/...............................................\/
/\-=====>>><<<--------= END =-------->>><<<=====-/\

*/
