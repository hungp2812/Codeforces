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

const int N = 505;

int n, m, a[N][N], f[N][N], pre[N][N];

bool check() {
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (f[i][j] && f[i][m] && f[n][j] && f[n][m])
				return 1;
		}
	}
	return 0;
}

void Hollwo_Pelw() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			char c; cin >> c;
			a[i][j] = c == 'B' ? 1 : 0;
		}
	}
	int res = 0;
	for (int i = n; i; i--) {
		for (int j = m; j; j--) {
			f[i][j] = a[i][j] ^ pre[i][j];
			pre[i][j - 1] ^= a[i][j];
			pre[i - 1][j] ^= a[i][j];
			pre[i - 1][j - 1] ^= a[i][j];
			res += f[i][j];
		}
	}
	cout << res - check() << '\n';
}
