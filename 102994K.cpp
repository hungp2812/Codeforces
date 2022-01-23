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
	cin >> testcases;
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

const int N = 3e5 + 5, B = 200;

int n, q, d[N], tin[N], tout[N], timer, pos[N], rev[N];
vector<int> adj[N], node[N];

struct fenwick {
	int n;
	vector<int> bit;

	fenwick() {}
	fenwick(int _n) : n(_n) {
		bit.clear();
		bit = vector<int> (n, 0);
	}

	inline void add(int p, int v) {
		for (; p < n; p |= (p + 1))
			bit[p] += v;
	}

	inline int query(int p) {
		int r = 0;
		for (; p >= 0; p = (p & (p + 1)) - 1)
			r += bit[p];
		return r;
	}

} bit[N];

struct query_t {
	int u, mod, rem, val;
	query_t () {}
	query_t (int _u, int _mod, int _rem, int _val)
		: u(_u), mod(_mod), rem(_rem), val(_val) {}
} query[N];

void pre_dfs(int u) {
	tin[u] = ++ timer;
	node[d[u]].push_back(tin[u]);

	rev[tin[u]] = u;

	for (auto v : adj[u])
		d[v] = d[u] + 1, pre_dfs(v);
	
	tout[u] = timer;
}

inline int get_low(const vector<int>& v, int p) {
	return lower_bound(v.begin(), v.end(), p) - v.begin();
}

inline int get_upp(const vector<int>& v, int p) {
	return upper_bound(v.begin(), v.end(), p) - v.begin();
}

void Hollwo_Pelw() {
	cin >> n >> q;
	for (int i = 0; i <= n; i++)
		adj[i].clear(), node[i].clear();

	for (int i = 2, p; i <= n; i++)
		cin >> p, adj[p].push_back(i);
	
	d[1] = timer = 0;
	pre_dfs(1);

	for (int i = 0; i < n; i++)
		bit[i] = fenwick(node[i].size());

	for (int i = 1, tp, u, mod, rem, val; i <= q; i++) {
		cin >> tp;
		if (tp == 1) {
			cin >> u >> mod >> rem >> val;
			query[i] = {u, mod, rem, val};
		} else {
			cin >> u;
			query[i] = {u, 0, 0, 0};
		}
	}

	for (int i = 1; i <= q; i++) {

		auto &[u, mod, rem, val] = query[i];

		if (mod == 0) { // answer

			val = bit[d[u]].query(get_low(node[d[u]], tin[u]));

		} else if (mod > B) { // big query
			
			int l = tin[u], r = tout[u];

			for (int cd = d[u] + rem; cd < n; cd += mod) {
				int pl = get_low(node[cd], l), pr = get_upp(node[cd], r);
				if (pl == pr) break ;
				
				bit[cd].add(pl, + val);
				bit[cd].add(pr, - val);

				// cout << "add " << cd << ' ' << pl << ' ' << pr << '\n';
			}
		}
	}

	for (int md = 1; md <= B; md++) {
		for (int i = 0; i < md; i++)
			node[i].clear();

		for (int i = 1; i <= n; i++) {
			int cd = d[rev[i]] % md;
			pos[rev[i]] = node[cd].size();
			node[cd].push_back(i);
		}
		
		for (int i = 0; i < md; i++)
			bit[i] = fenwick(node[i].size());

		for (int i = 1; i <= q; i++) {
			
			auto &[u, mod, rem, val] = query[i];

			if (mod == 0) {

				val += bit[d[u] % md].query(pos[u]);

			} else if (mod == md) {

				int l = tin[u], r = tout[u], cd = (d[u] + rem) % md;
				int pl = get_low(node[cd], l), pr = get_upp(node[cd], r);
				if (pl != pr) {
					bit[cd].add(pl, + val);
					bit[cd].add(pr, - val);
				}
			}
		}
	}

	for (int i = 1; i <= q; i++)
		if (!query[i].mod) cout << query[i].val << '\n';
}