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

int n, dp[21][1 << 20], vis[20], a[20];

inline int solve(int l, int r) {
	if (l == r) {
		if (l && a[l - 1] == 2)
			return a[l];
		if (r + 1 < n && a[r + 1] == 2)
			return a[r];
		return dp[1][a[l]];
	}

	int res = 0, mask = 0;
	if (l && a[l - 1] == 2)
		res ^= a[l ++];
	if (r + 1 < n && a[r + 1] == 2)
		res ^= a[r --];
	for (int i = l; i <= r; i++)
		mask = mask << 1 | a[i];

	return res ^ dp[r - l + 1][mask];
}

void Hollwo_Pelw() {
	for (int n = 1; n <= 20; n++) {
		for (int mask = 0; mask < 1 << n; mask++) {
			memset(vis, 0, sizeof vis);

			bool debug = mask == 1 && n == 3;

			for (int i = 0; i < n; i++) {
				if (mask >> i & 1) {
					// 111 type
					// => 101
					{
						int nl = i, lmask = mask & ((1 << nl) - 1);
						int nr = n - i - 1, rmask = mask >> (n - nr);
						vis[dp[nl][lmask] ^ dp[nr][rmask]] = 1;
					}
					// => 110
					vis[dp[n][mask ^ (1 << i)]] = 1;
				} else {
					// 110 type
					int g = 0;
					if (i > 0) {
						int nl = i - 1, lmask = mask & ((1 << nl) - 1);
						g ^= dp[nl][lmask];
						if (mask >> (i - 1) & 1)
							g ^= 1;
					}
					if (i + 1 < n) {
						int nr = n - i - 2, rmask = mask >> (n - nr);
						g ^= dp[nr][rmask];
						if (mask >> (i + 1) & 1)
							g ^= 1;
					}
					vis[g] = 1;
				}
			}

			while (vis[dp[n][mask]]) dp[n][mask] ++;
		}
	}

	int t; for (cin >> t; t --; ) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			string s; cin >> s;
			if (s == "I.I")
				a[i] = 3;
			else if (s == ".I.")
				a[i] = 2;
			else if (s == "III")
				a[i] = 1;
			else
				a[i] = 0;
		}

		int res = 0;
		for (int i = 0; i < n; i++) {
			if (a[i] > 1) continue ;

			int j = i;
			while (j + 1 < n && a[j + 1] <= 1) j ++;

			res ^= solve(i, j), i = j;
		}

		cout << (res ? "First\n" : "Second\n");
	}
}
