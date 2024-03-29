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
const int MAXN = 1e6 + 6;
const int inf = 2e9;
const ll linf = 1e18;
const ld eps = 1e-9;
// #define int long long


int n, a[MAXN];
long long ans;
int par[MAXN], sz[MAXN];

struct disjoint_set_union{
	disjoint_set_union() {
		for (int i = 1; i < MAXN; i++)
			par[i] = i, sz[i] = 1;
	}
	disjoint_set_union(int n){
		for (int i = 1; i <= n; i++)
			par[i] = i, sz[i] = 1;
	}
	int find(int u){
		return par[u] = (par[u] == u ? u : find(par[u]));
	}
	long long merge(int u, int v){
		u = find(u), v = find(v);
		if (u == v) return 0;
		if (sz[u] > sz[v]) swap(u, v);
		long long tmp = 1ll * sz[u] * sz[v];
		par[u] = v, sz[v] += sz[u];
		return tmp;
	}
};

vector<int> adj[MAXN], cost[MAXN];

void Hollwo_Pelw() {
	cin >> n;
	for (int i = 1; i <= n; i++){
		cin >> a[i], cost[a[i]].push_back(i);
	}
	for (int i = 1, u, v; i < n; i++){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	{
		disjoint_set_union dsu(n);
		for (int i = 1; i <= 1e6; i++){
			for (auto u : cost[i]) {
				for (auto v : adj[u]){
					if (a[v] <= a[u])
						ans += dsu.merge(u, v) * i;
				}
			}
		}
	}
	{
		disjoint_set_union dsu(n);
		for (int i = 1e6; i >= 1; i--){
			for (auto u : cost[i]) {
				for (auto v : adj[u])
					if (a[u] <= a[v])
						ans -= dsu.merge(u, v) * i;
			}
		}
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