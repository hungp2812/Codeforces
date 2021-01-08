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
const int MAXN = 1e5 + 5 , MAXM = 3e5 + 5;
const int inf = 2e9; const ll linf = 1e18;
// code
#define left node << 1, tl, tm
#define right node << 1 | 1, tm + 1, tr
// #define int long long
#define endl "\n"
int vis[1010][1010];
bool blk[1010][1010];
pair<pii, int> tr[1010][1010];
int n, m, sx, sy, ex, ey;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
string dir = "ULDR";

bool inb(int i, int j){
    return 1 <= i && i <= n && 1 <= j && j <= m;
}

void Solve(){
    cin >> n >> m >> sx >> sy >> ex >> ey;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            vis[i][j] = blk[i][j] = 0;
            char c; cin >> c;
            blk[i][j] = (c != '.');
        }
    }
    if (sx == ex && sy == ey){
        cout << 0 << endl << endl;
        return ;
    }
    queue<pii> q;
    q.push({sx, sy});
    vis[sx][sy] = 1;
    while(!q.empty()){
        auto [i, j] = q.front(); q.pop();
        // cout << i << ' ' << j << endl;
        if (i == ex && j == ey){
            string res = "";
            while(i != sx || j != sy){
                auto [lst, d] = tr[i][j];
                res += dir[(d + 2) % 4];
                i = lst.F;
                j = lst.S;
            }
            reverse(all(res));
            cout << res.size() << endl;
            cout << res << endl;
            return;
        }
        for (int d = 0; d < 4; d++){
            int x = i + dx[d], y = j + dy[d];
            if (inb(x, y)){
                if (!vis[x][y] && !blk[x][y]){
                    q.push({x, y});
                    vis[x][y] = 1;
                    tr[x][y] = {{i, j}, d};
                }
            }
        }
    }
    cout << -1 << endl;
}

signed main(){
    open("", ".inp", ".out");
    FAST_IO; int TC = 1;
    cin >> TC;
    while(TC--) Solve();
    return 0;
}
/*
./-=====>>><<<-------- DEBUG -------->>><<<=====-\.
/.................................................\

+====================== INP ======================+


+====================== OUT ======================+


\................................................./
.\-=====>>><<<--------= END =-------->>><<<=====-/.
*/