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

const int N = 5e5 + 5;

int n, a[N], dp[N], pos[N], nxt[N];

int st[N << 2];

#define tm (tl + tr >> 1)
#define left id << 1, tl, tm
#define right id << 1 | 1, tm + 1, tr

void update(int l, int r, int v, int id = 1, int tl = 1, int tr = n) {
	if (tl > r || l > tr) return ;
	if (l <= tl && tr <= r) 
		return st[id] = max(st[id], v), (void) 0;
	update(l, r, v, left), update(l, r, v, right);
}

int query(int p, int id = 1, int tl = 1, int tr = n) {
	int res = -1e9;
	while (tl != tr) {
		res = max(res, st[id]);
		id <<= 1;
		if (p > tm)
			id |= 1, tl = tm + 1;
		else
			tr = tm;
	}
	return max(res, st[id]);
}

void Hollwo_Pelw() {
	static int stk[N], top;

	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], pos[a[i]] = i;
	a[n + 1] = n + 1;

	for (int i = 1; i <= n + 1; i++) {
		while (top && a[i] > a[stk[top]])
			nxt[stk[top --]] = i;
		stk[++ top] = i;
	}
	nxt[n + 1] = n + 1;

	memset(st, -0x3f, sizeof st);

	update(1, nxt[1] - 1, 0);
	int res = 0;
	for (int i = 1; i <= n; i++) {
		int p = pos[i];
		dp[p] = query(p) + 1;
		if (nxt[p] <= n)
			update(nxt[p], nxt[nxt[p]] - 1, dp[p]);
		res = max(res, dp[p]);
	}

	// for (int i = 1; i <= n; i++)
	// 	cout << dp[i] << " \n"[i == n];

	cout << n - res;
}
