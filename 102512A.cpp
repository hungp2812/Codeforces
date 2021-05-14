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
const int MAXN = 5e5 + 5;
const int inf = 2e9;
const ll linf = 1e18;
const ld eps = 1e-9;
// #define int long long

int n, m, q, compCnt, nodeCnt;
vector<int> adj[MAXN];

int tin[MAXN], tout[MAXN];
int low[MAXN], timer;

bool art[MAXN], artnode[MAXN];
vector<int> comp[MAXN], st;

int node[MAXN];

void tarjan(int u, int p){
	tin[u] = low[u] = ++ timer;
	st.push_back(u);
	for (auto v : adj[u]) if (v != p){
		if (tin[v]) {
			low[u] = min(low[u], tin[v]);
		}else {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if (tin[u] <= low[v]){
				art[u] = tin[u] > 1 || tin[v] > 2;
				comp[++ compCnt].push_back(u);
				while (comp[compCnt].back() != v && !st.empty()){
					comp[compCnt].push_back(st.back());
					st.pop_back();
				}
			}
		}
	}
}

void build_tree() {
	tarjan(1, -1);
	for (int i = 1; i <= n; i++) adj[i].clear();
	for (int i = 1; i <= n; i++){
		if (art[i]) {
			node[i] = ++nodeCnt;
			artnode[nodeCnt] = 1;
		}
	}
	for (int i = 1; i <= compCnt; i++){
		++ nodeCnt;
		for (auto j : comp[i]) {
			if (!art[j]) {
				node[j] = nodeCnt;
			}else{
				adj[nodeCnt].push_back(node[j]);
				adj[node[j]].push_back(nodeCnt);
				// cout << compCnt << ' ' << node[j] << "\n"; 
			}
		}
	}
	n = nodeCnt;
}

int pre[MAXN], par[MAXN][20];

void dfs(int u, int p){
	tin[u] = ++ timer;
	pre[u] = pre[p] + artnode[u];
	
	par[u][0] = p;
	for (int i = 1; i <= 19; i++)
		par[u][i] = par[par[u][i - 1]][i - 1];

	for (auto v : adj[u]) if (v != p){
		dfs(v, u);
	}

	tout[u] = timer;
}

bool is_ancestor(int u, int v){
	return tin[u] <= tin[v] && tout[v] <= tout[u]; 
}

int lca(int u, int v) {
	if (is_ancestor(u, v)) return u;
	if (is_ancestor(v, u)) return v;

	for (int i = 19; i >= 0; i--){
		if (!is_ancestor(par[u][i], v))
			u = par[u][i];
	}
	return par[u][0];
}

void Hollwo_Pelw() {
	cin >> n >> m;
	for (int i = 1, u, v; i <= m; i++){
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	build_tree();
	tin[0] = timer;
	dfs(1, 0);
	tout[0] = timer;
	cin >> q;
	for (int i = 1, u, v, l; i <= q; i++){
		cin >> u >> v;
		u = node[u];
		v = node[v];
		l = lca(u, v);
		if (u == v) {
			cout << 0 << "\n";
		}else{
			cout << pre[u] + pre[v] - 2 * pre[l] 
					+ artnode[l] - artnode[u] - artnode[v] << "\n";
		}
	}
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