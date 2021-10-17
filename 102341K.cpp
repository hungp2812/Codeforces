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

const int N = 3e5 + 5, B = 500, H = 2, p = 379;

#define defop(type, op) \
	friend inline type operator op (type a, const type &b) { return a op##= b; } \
	type& operator op##= (const type &oth)

template<class T> struct hashmod_int {
	constexpr int mod(int id) { return T::mod[id]; }

	array<int, H> val;

	hashmod_int(int _val = 0) {
		fill(val.begin(), val.end(), _val);
	}

	hashmod_int(array<int, H> _val) : val(_val) {}

	inline int norm(long long a, int id) { return a % mod(id); }
	
	hashmod_int neg() const {
		array<int, H> nval;
		for (int i = 0; i < H; i++)
			nval[i] = val[i] == 0 ? 0 : mod(i) - val[i];
		return nval;
	}

	hashmod_int operator - () const { return neg(); }
	hashmod_int operator + () const { return hashmod_int(*this); }

	hashmod_int& operator -- () { 
		for (int i = 0; i < H; i++) {
			if (val[i] == 0) val[i] = mod(i); -- val[i];
		}
		return *this;
	}
	friend hashmod_int operator -- (hashmod_int& a, int) { hashmod_int r = a; --a; return r; }
	hashmod_int& operator ++ () {
		for (int i = 0; i < H; i++) {
			++ val[i]; if (val[i] == mod(i)) val[i] = 0;
		}
		return *this;
	}
	friend hashmod_int operator ++ (hashmod_int& a, int) { hashmod_int r = a; ++a; return r; }
	
	defop(hashmod_int, +) {
		for (int i = 0; i < H; i++)
			if ((val[i] += oth.val[i]) >= mod(i)) val[i] -= mod(i);
		return *this;
	}
	defop(hashmod_int, -) {
		for (int i = 0; i < H; i++)
			if ((val[i] -= oth.val[i]) < 0) val[i] += mod(i);
		return *this;
	}
	defop(hashmod_int, *) {
		for (int i = 0; i < H; i++)
			val[i] = norm(1ll * val[i] * oth.val[i], i);
		return *this;
	}

	hashmod_int pow(long long b) const {
		hashmod_int a = *this, r = 1;
		while (b) {
			if (b&1) r *= a;
			b >>= 1; a *= a;
		}
		return r;
	}
	hashmod_int inv() const { return pow(mod - 2); }

	defop(hashmod_int, /) { 
		return *this *= oth.inv();
	}

#define compare(op) friend bool operator op \
(const hashmod_int& lhs, const hashmod_int& rhs) { return lhs.val op rhs.val; }
	compare(==) compare(!=) compare(<) compare(<=) compare(>) compare(>=)
#undef compare
};

// const int mod1 = 998244353, mod2 = 1e9 + 7, mod3 = 1e9 + 123;
// struct hash_mod { static constexpr int mod[H] = {mod1, mod2, mod3}; };

struct hash_mod { static int mod[H]; };
int hash_mod::mod[H];

using hash_t = hashmod_int<hash_mod>;

vector<int> random_mod_list = {
	1023335503, 992584841, 992585963, 923335277, 923336329,
	1023336011, 989213707, 989212907, 989212907, 972408737,
	1002125009, 983213431, 983213927, 953213377, 953213483,
	1002127387, 794408851, 854409121, 720130171, 770129873,
	1010001089, 894375133, 740129413, 874408853, 822014023,
	1000100779, 679341473, 830063599, 896529031, 998244853,
	1030027337, 340312901, 171919661, 362561081, 923331589,
	1010023697, 592684123, 932861861, 769854577, 474653891,
	1003201153, 861433589, 957110953, 524863957, 564080779,
	1000001311, 998244853, 408245471, 700001539, 810002429
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

hash_t pw[N], hsh[N];

struct __init__ {
	__init__() {
		shuffle(random_mod_list.begin(), random_mod_list.end(), rng);
		for (int i = 0; i < H; i++)
			hash_mod::mod[i] = random_mod_list[i];
		pw[0] = 1;
		for (int i = 1; i < N; i++)
			pw[i] = pw[i - 1] * p;
	}
} __init__;


int ln, n, q, pi[N], res[N];
char s[N];

void recompute() { // include
	fill(res, res + n + 1, 0);
	for (int i = 0; i < n; i++)
		res[pi[i]] ++;
	for (int i = n - 1; i; i--)
		res[pi[i - 1]] += res[i];
	for (int i = 0; i <= n; i++)
		res[i] ++;
	ln = n + 1;
}

inline hash_t get(int l, int r) {
	return hsh[r] - hsh[l] * pw[r - l];
}

void Hollwo_Pelw() {
	cin >> q;
	for (int last = 0, i = 1; i <= q; i++) {
		string tp; cin >> tp;
		if (tp == "add") {
			char c; cin >> c;
			s[n] = (c - 'a' + last) % 26 + 'a';
			// prefix function

			if (n > 0) {
				int j = pi[n - 1];
				while (j > 0 && s[j] != s[n])
					j = pi[j - 1];
				pi[n] = s[j] == s[n] ? j + 1 : j;
				// if (n == 3)
				// 	cout << j << ' ' << pi[n] << '\n';
			}


			hsh[n + 1] = hsh[n] * p + s[n];

			if ((++ n) % B == 0)
				recompute();
		} else {
			int k; cin >> k;
			k = (k - 1 + last) % n + 1;

			last = res[k];

			hash_t v = get(0, k);
			for (int i = max(ln, k); i <= n; i++)
				last += get(i - k, i) == v;

			cout << last << '\n';
		}
	}
}
