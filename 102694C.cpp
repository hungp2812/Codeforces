#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5, L = 19;

int n, q, d[N], up[N][L];
vector<int> adj[N];

void pre_dfs(int u, int p) {
	up[u][0] = p;
	for (int i = 1; i <= 18; i++)
		up[u][i] = up[up[u][i - 1]][i - 1];
	
	for (int &v : adj[u]) if (v != p) {
		d[v] = d[u] + 1;
		pre_dfs(v, u);
	}
}

inline int lift(int u, int cd) {
	for (int i = 18; i >= 0; i--)
		if (cd >> i & 1) {
			u = up[u][i];
		}
	return u;
}

inline int lca(int u, int v) {
	if (d[u] > d[v]) swap(u, v);
	v = lift(v, d[v] - d[u]);

	if (u == v) return u;

	for (int i = 18; i >= 0; i--)
		if (up[u][i] != up[v][i]) {
			u = up[u][i];
			v = up[v][i];
		}

	return up[u][0];
}

signed main() {
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);

	cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	pre_dfs(1, 0);

	cin >> q;
	for (int a, b, c; q --; ) {
		cin >> a >> b >> c;
		int x = lca(a, b);

		int dist = d[a] + d[b] - 2 * d[x];

		if (dist <= c) {
			cout << b << '\n';
		} else if (c <= d[a] - d[x]) {
			cout << lift(a, c) << '\n';
		} else {
			cout << lift(b, dist - c) << '\n';
		}
	}
}