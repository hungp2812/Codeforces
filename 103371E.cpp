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

#define int long long

const int N = 65, K = 1005, inf = 2e18;

int n, m, p, c[N], w[N], mlt[N], rem[N], dp[N][K][K];

inline void chkmax(int &a, int b) { a = a > b ? a : b; }
inline void chkmin(int &a, int b) { a = a < b ? a : b; }

void Hollwo_Pelw() {
	cin >> n >> m >> p;
	for (int i = 1; i <= n; i++)
		cin >> c[i] >> w[i];
	c[0] = 1;

	for (int i = 1; i <= n; i++) {
		mlt[i] = c[i] / c[i - 1];
		
		rem[i] = p % mlt[i], p /= mlt[i];
	}

	if (rem[1] || p > m)
		return cout << -1, (void) 0;
	
	// minimum
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++) for (int k = 0; k <= m; k++) {
			if (i == 1 && j == 0 && k == 0) {
				dp[i][j][k] = 0; continue ;
			}
			dp[i][j][k] = inf;
			
			if (j && k)
				chkmin(dp[i][j][k], dp[i][j - 1][k - 1] + w[i]);

			if (i > 1 && j * mlt[i] + rem[i] <= k)
				chkmin(dp[i][j][k], dp[i - 1][j * mlt[i] + rem[i]][k]);
		}
	
	if (dp[n][p][m] == inf)
		return cout << -1, (void) 0;
	cout << dp[n][p][m] << ' ';

	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= m; j++) for (int k = 0; k <= m; k++) {
			if (i == 1 && j == 0 && k == 0) {
				dp[i][j][k] = 0; continue ;
			}
			dp[i][j][k] = -inf;

			if (j && k)
				chkmax(dp[i][j][k], dp[i][j - 1][k - 1] + w[i]);

			if (i > 1 && j * mlt[i] + rem[i] <= k)
				chkmax(dp[i][j][k], dp[i - 1][j * mlt[i] + rem[i]][k]);
		}
	
	if (dp[n][p][m] == -inf)
		return cout << -1, (void) 0;
	cout << dp[n][p][m] << ' ';
}
