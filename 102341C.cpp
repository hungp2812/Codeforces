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
	FAST_IO(".inp", ".out");
#endif
	int testcases = 1;
	// cin >> testcases;
	for (int test = 1; test <= testcases; test++){
		// cout << "Case #" << test << ": ";
		Hollwo_Pelw();
	}
#ifdef hollwo_pelw_local
	auto end = chrono::steady_clock::now();
	cout << endl;
	cout << "Excution time : " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif
	return 0;
}

const int N = 2002;

int n, a[N][N], sx, sy, ex, ey, px, py;

inline int ask(int i, int j) {
	if (i > n || j > n || i <= 0 || j <= 0) return -1;
	if (!a[i][j]) {
		cout << "? " << i << ' ' << j << endl;
		cin >> a[i][j];
		if (a[i][j] > a[px][py]) px = i, py = j;
	}
	return a[i][j];
}

void Hollwo_Pelw() {
	cin >> n, sx = 1, sy = 1, ex = n, ey = n;

	while (1) {
		if (ex - sx <= 0 && ey - sy <= 0) {
			cout << "! " << sx << ' ' << sy << endl;
			break ;
		}

		if (ex - sx >= ey - sy) {
			// binary search on x
			int mid = sx + ex >> 1, besty = sy; ask(mid, besty);
			for (int i = sy; i <= ey; i++)
				if (ask(mid, i) > a[mid][besty]) besty = i;

			for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= +1; y++)
					ask(x + mid, y + besty);

			if (px == mid) {
				cout << "! " << px << ' ' << py << endl;
				break ;
			}

			(px < mid ? ex = mid - 1 : sx = mid + 1);
		} else {
			// binary search on y
			int mid = sy + ey >> 1, bestx = sx; ask(bestx, mid);
			for (int i = sx; i <= ex; i++)
				if (ask(i, mid) > a[bestx][mid]) bestx = i;

			for (int x = -1; x <= 1; x++)
				for (int y = -1; y <= 1; y++)
					ask(x + bestx, y + mid);

			if (py == mid) {
				cout << "! " << px << ' ' << py << endl;
				break ;
			}

			(py < mid ? ey = mid - 1 : sy = mid + 1);
		}
	}
}
