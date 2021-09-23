/*
// is short or still long ???
hollwo_pelw's template(short)
// Note : -Dhollwo_pelw_local
*/

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/trie_policy.hpp>
// #include <ext/rope>

using namespace std;
// using namespace __gnu_pbds;
// using namespace __gnu_cxx;

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
	FAST_IO("hollwo_pelw.inp", "hollwo_pelw.out");
#endif
	int testcases = 1;
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = chrono::steady_clock::now();
	cout << "\nExcution time : " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif
	return 0;
}

const int N = 2e5 + 5;

int n, m, q, tin[N], tout[N], low[N], timer;
vector<pair<int, int>> adj[N];

vector<int> nadj[N], st;
int comp[N], comp_cnt;

void tarjan(int u, int id) {
	tin[u] = low[u] = ++ timer;
	st.push_back(u);
	for (auto vw : adj[u]) if (vw.second != id) {
		int v = vw.first;
		if (tin[v]) {
			low[u] = min(low[u], tin[v]);
		} else {
			tarjan(v, vw.second);
			low[u] = min(low[u], low[v]);
		}
	}
	// no back edge
	if (tin[u] <= low[u]) {
		++ comp_cnt;
		while (st.back() != u) {
			comp[st.back()] = comp_cnt;
			st.pop_back();
		}
		comp[st.back()] = comp_cnt;
		st.pop_back();
	}
}

int par[18][N], dir[18][N];

void compress_graph() {
	for (int i = 1; i <= n; i++)
		if (!tin[i]) tarjan(i, -1);

	for (int i = 1; i <= n; i++) for (auto vw : adj[i])
		if (comp[vw.first] != comp[i]) nadj[comp[i]].push_back(comp[vw.first]);

	n = comp_cnt, timer = 0;
	fill(tin + 1, tin + n + 1, 0);
	fill(tout + 1, tout + n + 1, 0);
}

void pre_dfs(int u, int p) {
	par[0][u] = p, tin[u] = ++ timer;
	for (int i = 1; i <= 17; i++)
		par[i][u] = par[i - 1][par[i - 1][u]];

	for (auto v : nadj[u])
		if (v != p) pre_dfs(v, u);

	tout[u] = timer;
}

bool is_ancestor(int u, int v) {
	return tin[u] <= tin[v] && tout[v] <= tout[u];
}

inline int lca(int u, int v) {
	if (is_ancestor(u, v)) return u;
	if (is_ancestor(v, u)) return v;

	for (int i = 17; ~i; i--)
		if (!is_ancestor(par[i][u], v))
			u = par[i][u];
	return par[0][u];
}

void update(int u, int v, int w) {
	for (int i = 17; ~i; i--)
		if (!is_ancestor(par[i][u], v)) {
			dir[i][u] |= w;
			u = par[i][u];
		}
	dir[0][u] |= w;
}

void Hollwo_Pelw() {
	cin >> n >> m >> q;
	for (int i = 1, u, v; i <= m; i++)
		cin >> u >> v, adj[u].emplace_back(v, i), adj[v].emplace_back(u, i);
	compress_graph(), pre_dfs(1, 0), tout[0] = timer;

	for (int s, t; q --; ) {
		cin >> s >> t, s = comp[s], t = comp[t];
		if (s == t) continue ;
		int l = lca(s, t);
		if (!l) return cout << "No", (void) 0;
		if (s != l) update(s, l, 1);
		if (t != l) update(t, l, 2);
	}

	for (int i = 17; ~i; i--) {
		for (int j = 1; j <= n; j++) {
			if (dir[i][j] == 3) return cout << "No", (void) 0;
			if (i) {
				dir[i - 1][j] |= dir[i][j];
				dir[i - 1][par[i - 1][j]] |= dir[i][j];
			}
		}
	}

	cout << "Yes";
}
