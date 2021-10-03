/* 
// is short or still long ???
hollwo_pelw's template(short)
// Note : -Dhollwo_pelw_local
*/

#include<bits/stdc++.h>
using namespace std;

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
	cout << endl;
	cout << "Excution time : " << chrono::duration_cast<chrono::milliseconds> (end - start).count() << "[ms]" << endl;
#endif
	return 0;
}

const int N = 1e5 + 5;

int n, q, a[N], b[N];

struct {
	int t, x, y;
} qr[N];

struct fenwick {
	vector<int> allp;

	long long tot;
	vector<long long> bit;
	
	inline int comp(int v) {
		return lower_bound(allp.begin(), allp.end(), v) - allp.begin();
	}

	inline void _add(int p, int v) {
		for (; p < bit.size(); p |= p + 1)
			bit[p] += v;
	}
	
	inline void add(int p, int v) {
		_add(comp(p), v), tot += v;
	}

	inline long long _query(int p) {
		long long res = 0;
		for (; p >= 0; p = (p & (p + 1)) - 1)
			res += bit[p];
		return res;
	}

	inline long long query(int p) {
		return tot - _query(comp(p) - 1);
	}

	inline void upd(int type, int p, int v) {
		(type ? add(p, v) : allp.push_back(p));
	}

	inline void process() {
		tot = 0;
		sort(allp.begin(), allp.end());
		allp.resize(unique(allp.begin(), allp.end()) - allp.begin());
		bit.assign(allp.size(), 0); 
	}

} st[N << 2];

int prv[N], lst[N];
set<int> posv[N];

#define tm (tl + tr >> 1)
#define left id << 1, tl, tm
#define right id << 1 | 1, tm + 1, tr

void build(int type, int id = 1, int tl = 1, int tr = n) {
	for (int i = tl; i <= tr; i++)
		st[id].upd(type, prv[i], i - prv[i]);
	if (tl == tr) return ;
	build(type, left), build(type, right);
}

void upd(int pos, int type, int p, int v, int id = 1, int tl = 1, int tr = n) {
	st[id].upd(type, p, v);
	if (tl == tr) return ;
	if (pos > tm)
		upd(pos, type, p, v, right);
	else
		upd(pos, type, p, v, left);	
}

long long query(int l, int r, int v, int id = 1, int tl = 1, int tr = n) {
	if (l > r || l > tr || tl > r) return 0;
	if (l <= tl && tr <= r) return st[id].query(v);
	return query(l, r, v, left) + query(l, r, v, right);
}

#undef tm
#undef left
#undef right

inline void add(int type, int pos) {
	upd(pos, type, prv[pos], pos - prv[pos]);
}

inline void del(int type, int pos) {
	if (type)
		upd(pos, type, prv[pos], prv[pos] - pos);
}

inline void erase_val(int type, int pos, int val) {
	del(type, pos);
	posv[val].erase(pos);

	auto it = posv[val].lower_bound(pos);
	if (it != posv[val].end()) {
		int npos = * it;
		del(type, npos);
		prv[npos] = prv[pos];
		add(type, npos);
	}
	
	a[pos] = prv[pos] = 0;
}

inline void insert_val(int type, int pos, int val) {
	auto it = posv[val].lower_bound(pos);
	if (it != posv[val].end()) {
		int npos = * it;
		del(type, npos);
		prv[npos] = pos;
		add(type, npos);
	}
	if (it != posv[val].begin())
		prv[pos] = * prev(it);

	add(type, pos);
	posv[a[pos] = val].insert(pos);
}

void Hollwo_Pelw() {
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = 1; i <= q; i++)
		cin >> qr[i].t >> qr[i].x >> qr[i].y;

	for (int type = 0; type < 2; type ++) {
		if (type) {
			for (int i = 1; i < N << 2; i++)
				st[i].process();
		}
		for (int i = 1; i <= n; i++)
			a[i] = b[i], lst[i] = 0, posv[i].clear();
		for (int i = 1; i <= n; i++) {
			prv[i] = lst[a[i]];
			lst[a[i]] = i;
			posv[a[i]].insert(i);
		}
		build(type);
		for (int i = 1; i <= q; i++) {
			if (qr[i].t == 1) {
				erase_val(type, qr[i].x, a[qr[i].x]);
				insert_val(type, qr[i].x, qr[i].y);
			} else if (type) {
				cout << query(qr[i].x, qr[i].y, qr[i].x) << '\n';
			}
		}
	}
}
