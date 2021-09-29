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
const int MAXN = 1e5 + 6;
const int inf = 2e9;
const ll linf = 1e18;
#define int long long

const int SZ = 316;

struct query {
    int l, r, id;
    query() {}
    query(int _l, int _r, int _id) 
        : l(_l), r(_r), id(_id) {}

    int tob() {
        return l / SZ;
    }
    bool operator < (query & oth) {
        if (tob() != oth.tob())
            return tob() < oth.tob();
        return (tob() & 1) ? r > oth.r : r < oth.r; 
    }
};

/*
 *   r\l----+-----------+-----+
 *    |     |    ->     |     |
 *    |     |           |     |
 *    |     |     |     |     |
 *    |     |     |     |     |
 *    |  |  |  ^  |  |  |  ^  |
 *    |  v  |  |  |  v  |  |  |
 *    |     |     |     |     |
 *    |     |     |     |     |
 *    |           |           |
 *    |    ->     |    ->     |
 *    +-----------+-----------+
 */

int a[MAXN], cnt[1 << 20];
ll res[MAXN], ans;
int n, m, k, pl = 0, pr = -1;

void add(int val) {
    ans += cnt[val ^ k];
    cnt[val] ++;
}

void del(int val){
    cnt[val] --;
    ans -= cnt[val ^ k];
}

void Hollwo_Pelw() {
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++){
        cin >> a[i], a[i] ^= a[i - 1];
    }
    vector<query> allquery(m);
    for (int i = 0, l, r; i < m; i++)
        cin >> l >> r, allquery[i] = query(l - 1, r, i);
    sort(all(allquery));
    for (auto qq : allquery) {
        int ql = qq.l, qr = qq.r, id = qq.id;
        // move to left, add a[pl] to current value range
        while (pl > ql) add(a[-- pl]);
        // move to right, add a[pr] to current value range
        while (pr < qr) add(a[++ pr]);
        // del a[pl] from current value range, move to right
        while (pl < ql) del(a[pl ++]);
        // del a[pr] from current value range, move to left
        while (pr > qr) del(a[pr --]);
        res[id] = ans;
    }
    for (int i = 0; i < m; i++)
        cout << res[i] << "\n";
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