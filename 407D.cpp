#include <bits/stdc++.h>
using namespace std;
// type
typedef long long ll;
typedef long double ld;
// loop
//#define For(i, l, r, x)     for (int i = l; i < r; i+=x)
//#define ForE(i, l, r, x)    for (int i = l; i <= r; i+=x)
//#define Ford(i, r, l)       for (int i = r; i > l; i--)
//#define FordE(i, r, l)      for (int i = r; i >= l; i--)
//#define Fora(i, a)          for (auto i : a)
// I/O 
#define FAST_IO             std::ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
//#define PrintV(a)           Fora(ii, a) cout << ii << ' '; cout << rl;
//#define PrintVl(a)          Fora(ii, a) cout << ii << rl;
//#define PrintA(a, l, r)     for (int ii = l; ii <= r; ii++) cout << a[ii] << ' '; cout << rl;
//#define PrintAl(a, l, r)    for (int ii = l; ii <= r; ii++) cout << a[ii] << rl;
//#define Ptest(x)            return cout << x, 0;
#define setpre(n)           fixed << setprecision(n)
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
// geometry calc    
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
const int mod1 = 998244353, mod = 1e9+7;
const int MAX_N = 100005, MAX_M = 200010;
//
const int N = 401;

short posR[N*N][N], 
        maxR[N][N]; // nearest right pos of a number in a row // 
                                // large (right) value that the rectangle between (up) and (down) is inhomogeneous // (left is fixed)
int a[N][N], n, m, res;

void Solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < N*N; i++){
        for (int j = 0; j < N; j++){
            posR[i][j] = m+1;
        }
        maxR[i/N][i%N] = m+1;
    }
    for (int left = m; left >= 1; left--){
        for (int i = 1; i <= n; i++){
            maxR[i][i] = min(maxR[i][i], posR[a[i][left]][i]);
            res = max(res, maxR[i][i] - left);
        }
        for (int i = 1; i <= n; i++){
            posR[a[i][left]][i] = left; // nearest right pos of a number in row is fixed to be equal the current pos
        }
        for (int up = n; up >= 1; up--){
            for (int down = up+1; down <= n; down++){
                maxR[up][down] = min(maxR[up][down], min(maxR[up + 1][down], maxR[up][down - 1]));
                maxR[up][down] = min(maxR[up][down], min(posR[a[up][left]][down], posR[a[down][left]][up]));
                res = max(res, (down - up + 1) * (maxR[up][down] - left));
            }
        }
    }
    cout << res;
}

signed main(){
    FAST_IO;
    int TC = 1; 
	//cin >> TC;
    while(TC--) Solve();
    return 0;
}