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
	FAST_IO("pvhoi20b6string.inp", "pvhoi20b6string.out");
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

const int N = 2005, mod = 1e9 + 7;

inline void sadd(int &a, int b) {
	if ((a += b) >= mod) a -= mod;
}

int n, m, dp[N][N], pre[N];
char s[N];

void Hollwo_Pelw() {
	cin >> n >> m >> (s + 1);
	dp[0][0] = pre[0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			sadd(dp[i][j], 1ll * pre[j] * (s[i] - 'a') % mod);
			for (int k = i - 1; ~k; --k) {
				if (j + (i - k) * (n + 1 - i) > m) break ;
				sadd(dp[i][j + (i - k) * (n + 1 - i)], 1ll * dp[k][j] * ('z' - s[i]) % mod);
			}
			sadd(pre[j], dp[i][j]);
		}
	}
	cout << pre[m];
}
