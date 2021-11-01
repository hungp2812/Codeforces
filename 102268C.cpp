#include <bits/stdc++.h>
using namespace std;

const int N = 3e5 + 5;

int n, a[N], b[N], p[N];
int64_t k;

signed main() {
	cin.tie(0), cout.tie(0) -> sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1, x; i <= n; i++) 
		cin >> x, a[x] = i - n - 1;
	for (int i = 1; i <= n; i++)
		cin >> p[i], b[i] = n;

	for (int i = 1; i <= n; i++) {
		if (k >= p[i]) {
			b[p[i]] = - n;
			k -= p[i] - 1;
		} else {
			if (k == 0) break ;
			vector<int> v;
			for (int j = 1; j < p[i]; j++)
				v.push_back(a[j]);
			sort(v.begin(), v.end());
			b[p[i]] = - 1 - v[-- k];
			break ;
		}
	}
	cout << "Yes\n";
	for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
	for (int i = 1; i <= n; i++) cout << b[i] << " \n"[i == n];
}