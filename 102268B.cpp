#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, k, a[N];

inline bool calc(int l, int r, int s) {
	if (l > r) {
		for (int j = l + 1; j <= n; j++)
			if (a[j] + a[l] <= s && a[j] + a[r] <= s)
				return 1;
		for (int j = 1; j < r; j++)
			if (a[j] + a[l] <= s && a[j] + a[r] <= s)
				return 1;
		return 0;
	}
	for (int j = l + 1; j < r; j++)
		if (a[j] + a[l] <= s && a[j] + a[r] <= s)
			return 1;
	return 0;
}

inline bool solve(int s) {
	vector<int> b;
	for (int i = 1; i <= n; i++)
		if (a[i] <= s / 2) b.push_back(i);
	if (b.size() < 2) return 0;

	int res = b.size();
	for (int i = 0; i < b.size(); i++) {
		res += calc(b[i], b[(i + 1) % b.size()], s);
	}
	return res >= k;
}

signed main() {
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	int64_t l = 2, r = 2e9, res = 2e9;
	while (l <= r) {
		int64_t m = l + r >> 1;
		if (solve(m))
			res = m, r = m - 1;
		else
			l = m + 1;
	}
	cout << res;
}