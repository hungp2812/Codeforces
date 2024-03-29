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

const int N = 20, K = 4e5 + 5;

int n, dp[1 << N], sum[1 << N], low[N], cnt[N][K], res;

void Hollwo_Pelw() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		
		int &cur = sum[1 << i], &mn = low[i];

		for (auto c : s) {
			cur += c == '(' ? 1 : -1;
			mn = min(mn, cur);
			
			if (mn == cur)
				cnt[i][- mn] ++;
		}
	}

	memset(dp, -1, sizeof dp);
	dp[0] = 0;
	for (int mask = 0; mask < 1 << n; mask++) if (dp[mask] >= 0) {
		for (int i = 0; i < n; i++) if ((mask >> i & 1) == 0) {
			int val = dp[mask] + cnt[i][sum[mask]];
			res = max(res, val);

			if (sum[mask] + low[i] >= 0) {
				sum[mask ^ 1 << i] = sum[mask] + sum[1 << i];
				dp[mask ^ 1 << i] = max(dp[mask ^ 1 << i], val);
			}
		}
	}

	cout << res;
}
