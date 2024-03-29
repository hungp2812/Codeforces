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
// loop
//#define For(i, l, r)        for (int i = l; i < r; i++)
//#define ForE(i, l, r)       for (int i = l; i <= r; i++)
//#define Ford(i, r, l)       for (int i = r; i > l; i--)
//#define FordE(i, r, l)      for (int i = r; i >= l; i--)
//#define Fora(i, a)          for (auto i : a)
// I/O
#define open(file, in, out) if (fopen(file in, "r")) {        \
                                freopen(file in, "r", stdin);  \
                                freopen(file out, "w", stdout); \
                            }
#define FAST_IO             std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define setpre(n)           fixed << setprecision(n)
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
const int mod1 = 998244353, mod = 1e9+7;
const int MAXN = 100005, MAXM = 200010;
// code
//#define int long long

vector<int> grp[MAXM], adj[MAXM];
int nb[MAXM], leaf[MAXM], out[MAXM];
int n, k;

void Solve() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        grp[i].clear(); adj[i].clear();
        nd[i] = leaf[i] = out[i] = 0;
    }
    for (int i = 1, x, y; i < n; i++){
        cin >> x >> y;
        grp[x].pb(y);
        grp[y].pb(x);
    }
    if(k == 1){
        cout << n-1 << endl;
        return;
    }
    for (int i = 1; i <= n; i++){
        if (grp[i].size() == 1) leaf[i] = 1;
    }
    for (int i = 1; i <= n; i++){
        nb[i] = grp[i].size();
        for (int j : grp[i]){
            if (leaf[j]){
                adj[i].pb(j);
            }
        }
    }

    priority_queue<pii> pq;
    for (int i = 1; i <= ; i++){
        if (!leaf[i]) pq.push({adj[i].size(), i});
    }
    int ans = 0;
    while (!pq.empty()){
        int u = pq.top().S, xx = pq.top().F; pq.pop();
        if (adj[u].size() != xx) continue;
        if (adj[u].size() < k) break;
        while(adj[u].size() >= k){
            ans ++;
            for (int i = 0; i < k; i++){
                int v = adj[u].back();
                adj[u].pop_back();
                out[v] = 1, nb[v] --;
            }
        }
        if (nb[u] == 1){ // u can be use as leaf now
            for (int v: g[u]){
                if (!out[v]){
                    adj[v].pb(u);
                    pq.push({adj[v].size(), v});
                }
            }
        }else{
            pq.push({adj[u].size(), u});
        }
    }
    cout << ans << endl;
}

signed main(){
    open("", ".inp", ".out");
    FAST_IO;
    int TC = 1;
    //cin >> TC;
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
