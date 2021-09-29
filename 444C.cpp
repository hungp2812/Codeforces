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

const int N = 1e5 + 5, B = 350;

int n, m, col[N], lzcol[B], blk[N];
int64_t a[N], lz[B], res, tot[B];

inline int tl(int x) {
	return (x - 1) * B + 1;
}

inline int tr(int x) {
	return min(x * B, n);
}

void Hollwo_Pelw() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		blk[i] = (i + B - 1) / B, col[i] = i;

	for (int t, l, r, x; m --; ) {
		cin >> t >> l >> r, res = 0;
		int lb = blk[l], rb = blk[r];
		if (t == 1) {
			cin >> x;
			for (int i = lb + 1; i < rb; i++) {
				if (lzcol[i]) {
					lz[i] += abs(lzcol[i] - x), tot[i] += 1ll * abs(lzcol[i] - x) * (tr(i) - tl(i) + 1);
				} else {
					for (int j = tl(i); j <= tr(i); j++)
						a[j] += abs(col[j] - x), tot[i] += abs(col[j] - x);
				}
				lzcol[i] = x;
			}
			if (lzcol[lb]) {
				for (int j = tl(lb); j <= tr(lb); j++) 
					col[j] = lzcol[lb]; lzcol[lb] = 0;
			}
			if (lzcol[rb]) {
				for (int j = tl(rb); j <= tr(rb); j++) 
					col[j] = lzcol[rb]; lzcol[rb] = 0;
			}
			while (l <= r && blk[l] == lb)
				a[l] += abs(col[l] - x), tot[lb] += abs(col[l] - x), col[l ++] = x;
			while (l <= r && blk[r] == rb)
				a[r] += abs(col[r] - x), tot[rb] += abs(col[r] - x), col[r --] = x;
		} else {
			for (int i = lb + 1; i < rb; i++) res += tot[i];
			while (l <= r && blk[l] == lb) res += a[l ++] + lz[lb];
			while (l <= r && blk[r] == rb) res += a[r --] + lz[rb];
			cout << res << '\n';
		}
	}
}
