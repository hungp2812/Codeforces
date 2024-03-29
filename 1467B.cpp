/*
 /+==================================================+\
//+--------------------------------------------------+\\
|.|\\...>>>>>>> Hollwo_Pelw(ass) 's code <<<<<<<...//|.|
\\+--------------------------------------------------+//
 \+==================================================+/
*/
#include <bits/stdc++.h>
using namespace std;
// type
typedef long long ll;
typedef long double ld;
// pair
#define F                   first
#define S                   second
#define pii                 pair<int, int>
#define pll                 pair<ll, ll>
#define pdd                 pair<ld, ld>
// vector & !!?(string)
#define eb                  emplace_back
#define pb                  push_back
#define all(a)              a.begin(), a.end()
#define rall(a)             a.rbegin(), a.rend()
#define sz(a)               a.size()
#define len(a)              a.length()
// I/O
#define open(file, in, out) if (fopen(file in, "r")) {        \
                                freopen(file in, "r", stdin);  \
                                freopen(file out, "w", stdout); \
                            }
#define FAST_IO             std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define setpre(n)           fixed << setprecision(n)        
bool endline = false;
template<class T>
istream& operator >> (istream& inp, vector<T>& v){
    for (auto& it : v) inp >> it;
    return inp;
}
template<class T>
ostream& operator << (ostream& out, vector<T>& v){
    for (auto& it : v) out << it << (endline ? "\n" : " ");
    return out;
}
template<class T, class U>
istream& operator >> (istream& inp, pair<T, U>& v){
    inp >> v.F >> v.S;
    return inp;
}
template<class T, class U>
ostream& operator << (ostream& out, pair<T, U>& v){
    out << v.F << ' ' << v.S;
    return out;
}
#define debug(x)            cout << #x << " : " << endl << x << endl;
#define Ptest(x)            return cout << x << endl, (void) 0;
// geometry calculate
#define pi                  acos(-1.0)
#define g_sin(a)            sin(a*pi/180)
#define g_cos(a)            cos(a*pi/180)
#define g_tan(a)            tan(a*pi/180)
// set val
#define ms0(a)              memset(a,        0, sizeof(a));
#define ms1(a)              memset(a,        1, sizeof(a));
#define msn1(a)             memset(a,       -1, sizeof(a));
#define msinf(a)            memset(a, 0x3f3f3f, sizeof(a));
// constant
const int mod1 = 998244353, mod = 1e9 + 7;
const int MAXN = 3e5 + 5 , MAXM = 3e5 + 5;
const int inf = 2e9; const ll linf = 1e18;
// code
#define left node << 1, tl, tm
#define right node << 1 | 1, tm + 1, tr
#define int long long

vector<int> a;
int n;

bool f(int i){
    if (i <= 0 || i > n) return 0;
    if (a[i] > max(a[i - 1], a[i + 1])) return 1;
    if (a[i] < min(a[i - 1], a[i + 1])) return 1;
    return 0;
}

void Solve(){
    cin >> n;
    a.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	int cnt = 0;
	for (int i = 2; i < n; i++) {
		if (f(i)) cnt++;
	}
	int ans = cnt;
	for (int k = 1; k < n; k++) {
		int ct = 0;
		int tmp = a[k];
		a[k] = a[k + 1];
		for (int i = max(2ll, k - 5); i <= min(n - 1, k + 5); i++) {
		    if(f(i)) ct++;
		}
		a[k] = tmp;
		tmp = 0;
		for (int i = max(2ll, k - 5); i <= min(n - 1, k + 5); i++) {
		    if (f(i)) tmp++;
		}
		ans = min(ans, cnt + ct - tmp);
	}
	for (int k = 2; k <= n; k++) {
		int ct = 0;
		int tmp = a[k];
		a[k] = a[k - 1];
		for (int i = max(2ll, k - 5); i <= min(n - 1, k + 5); i++) {
			if (f(i)) ct++;
		}
		a[k] = tmp;
		tmp = 0;
		for (int i = max(2ll, k - 5); i <= min(n - 1, k + 5); i++) {
			if (f(i)) tmp++;
		}
		ans = min(ans, cnt + ct - tmp);
	}
	cout << ans << '\n';
}

signed main(){
    open("", ".inp", ".out");
    FAST_IO; int TC = 1;
    cin >> TC;
    while(TC--) Solve();
    return 0;
}
/*
./-=====>>><<<-------- DEBUG -------->>><<<=====-\.
/.................................................\

+====================== INP ======================+


+====================== OUT ======================+


\................................................./ 
.\-=====>>><<<--------= END =-------->>><<<=====-/.
*/