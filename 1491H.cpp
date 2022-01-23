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

const int N = 1e5 + 5, S = 8, B = 1 << S;

int n, q, par[N], anc[N], blk[N], lz[N];

inline int get_par(int u) {
	return u == 1 ? 0 : max(1, par[u] - lz[blk[u]]);
}

inline int get_anc(int u) {
	return anc[u] == u ? get_par(u) : anc[u];
}

void build(int l, int r) {
	for (int i = l; i <= r; i++) {
		int p = get_par(i);
		anc[i] = blk[i] != blk[p] ? i : anc[p];
	}
	anc[1] = 0;
}

void Hollwo_Pelw() {
	cin >> n >> q;
	int ok = 1;
	for (int i = 2; i <= n; i++) {
		cin >> par[i];

		ok &= par[i] == 1;
	}

	for (int i = 1; i <= n; i++)
		blk[i] = (i + B - 1) >> S;
	
	build(1, n);
	anc[1] = 0;

	for (int t, l, r, x, u, v; q --; ) {
		cin >> t;
		if (t == 1) {
			cin >> l >> r >> x;
			if (l > r) swap(l, r);

			int lb = blk[l], rb = blk[r];

			for (; l <= r && blk[l] == lb; l ++)
				par[l] = max(1, par[l] - x);
			for (; l <= r && blk[r] == rb; r --)
				par[r] = max(1, par[r] - x);

			if (lb == rb) {
				if (lz[lb] < B) build((lb - 1) * B + 1, min(n, lb * B));
			} else {
				if (lz[lb] < B) build((lb - 1) * B + 1, min(n, lb * B));
				if (lz[rb] < B) build((rb - 1) * B + 1, min(n, rb * B));

				for (int i = lb + 1; i < rb; i++) {
					if (lz[i] < B) {
						lz[i] += x;
						build((i - 1) * B + 1, min(n, i * B));
					} else {
						lz[i] += x;
					}
					lz[i] = min(lz[i], n);
				}
			}

		} else {
			cin >> u >> v;

			for (; get_anc(u) ^ get_anc(v); u = get_anc(u)) {
				if (u < v) swap(u, v);

				// cout << "anc -> " << u << ' ' << v << '\n'; 
			}

			for (; u ^ v; u = get_par(u)) {
				if (u < v) swap(u, v);

				// cout << "par -> " << u << ' ' << v << '\n';
			}
			
			cout << u << '\n';
		}
	}
}
