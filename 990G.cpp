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
	FAST_IO("990G.inp", "990G.out");
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

int n, a[N], sz;
vector<int> d[N], adj[N];

int64_t res[N];

bool used[N], vis[N];

void dfs(int u, int d) {
	vis[u] = 1, ++ sz;
	for (auto v : adj[u])
		if (!vis[v] && a[v] % d == 0) dfs(v, d);
}

vector<int> node[N];

void Hollwo_Pelw() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i], used[a[i]] = 1;
	for (int i = 1, u, v; i < n; i++)
		cin >> u >> v, adj[u].push_back(v), adj[v].push_back(u);

	for (int i = 1; i < N; i++) {
		for (int j = i; j < N; j += i)
			if (used[j]) d[j].push_back(i);
	}

	for (int i = 1; i <= n; i++)
		for (auto j : d[a[i]]) 
			node[j].push_back(i);

	for (int i = 1; i < N; i++) if (!node[i].empty()) {
		for (auto v : node[i]) if (!vis[v]) {
			sz = 0, dfs(v, i), res[i] += 1ll * sz * (sz + 1) / 2;
		}
		for (auto v : node[i]) vis[v] = 0;
	}

	for (int i = N - 1; i; i--) {
		for (int j = 2 * i; j < N; j += i)
			res[i] -= res[j];
	}

	for (int i = 1; i < N; i++) if (res[i])
		cout << i << ' ' << res[i] << '\n';
	
}
