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
	FAST_IO("100541E.inp", "100541E.out");
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

const int N = 5e4 + 5, K = 151;

int n, m, mod, p[K], idx[K], pr[35];

struct __init__ {
	__init__() {
		iota(p + 1, p + K, 1);
		fill(idx, idx + K, -1);
		for (int i = 2, c = 0; i < K; i++) if (p[i] == i) {
			pr[c] = i, idx[i] = c ++;
			for (int j = i * i; j < K; j += i) p[j] = i;
		}
	}
} __init__;

struct segment_tree {
#define tm (tl + tr >> 1)
#define left id << 1, tl, tm
#define right id << 1 | 1, tm + 1, tr

	int64_t st[N << 2];
	int lz[N << 2];
	
	inline void clear() {
		for (int i = 1; i < n << 2; i++)
			st[i] = lz[i] = 0;
	}

	inline void apply(int id, int tl, int tr, int v) {
		st[id] += 1ll * (tr - tl + 1) * v, lz[id] += v;
	}

	inline void push(int id, int tl, int tr) {
		apply(left, lz[id]), apply(right, lz[id]), lz[id] = 0;
	}

	void update(int l, int r, int v, int id, int tl, int tr) {
		if (l > tr || tl > r) return ;
		if (l <= tl && tr <= r) return apply(id, tl, tr, v);
		push(id, tl, tr), update(l, r, v, left), update(l, r, v, right);
		st[id] = st[id << 1] + st[id << 1 | 1];
	}

	int64_t query(int l, int r, int id, int tl, int tr) {
		if (l > tr || tl > r) return 0;
		if (l <= tl && tr <= r) return st[id];
		return push(id, tl, tr), query(l, r, left) + query(l, r, right);
	}

	inline void update(int l, int r, int v) {
		// cout << "update " << l << ' ' << r << ' ' << v << '\n';
		(l > r ? update(l, n, v, 1, 1, n), update(1, r, v, 1, 1, n) : update(l, r, v, 1, 1, n));
	}

	inline int64_t query(int l, int r) {
		// cout << "query " << l << ' ' << r << '\n';
		return (l > r ? query(l, n, 1, 1, n) + query(1, r, 1, 1, n) : query(l, r, 1, 1, n));
	}
} segtree[35];

inline int binpow(int a, int64_t b) {
	int r = 1;
	while (b) {
		if (b&1) r = 1ll * r * a % mod;
		b >>= 1; a = 1ll * a * a % mod;
	}
	return r;
}

void Hollwo_Pelw() {
	cin >> n >> m;

	for (int i = 0; i < 35; i++)
		segtree[i].clear();

	for (int t, l, r, v; m --; ) {
		cin >> t >> l >> r;
		if (t == 0) {
			cin >> mod;
			int res = 1;
			for (int i = 0; i < 35; i++) {
				res = 1ll * res * binpow(pr[i], segtree[i].query(l, r)) % mod;
			}
			cout << res << '\n';
		} else {
			cin >> v;
			while (v > 1) {
				int x = p[v], c = 0;
				while (v % x == 0)
					v /= x, c ++;
				segtree[idx[x]].update(l, r, t == 1 ? c : -c);
			}
		}
	}
}
