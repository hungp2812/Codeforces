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

const int N = 1e5 + 5, S = 320;

int n, q, z, a[N], blockcnt, ans;
int cnt[S][N];
int nval[S][N / S + 100], oval[S][N / S + 100], nsz[S], osz[S];

inline void sadd(int & a, int b){
    a += b; if (a > n) a -= n;
}

void build() {
    for (int l = 1; l <= n; l += S){
        int r = min(n, l + S - 1);
        for (int i = l; i <= r; i++){
            ++ cnt[blockcnt][a[i]];
            nval[blockcnt][nsz[blockcnt] ++] = a[i];
            oval[blockcnt][osz[blockcnt] ++] = a[i];
        }
        ++ blockcnt;
    }
}

void rebuild() {
    int k = 0;
    for (int i = 0; i < blockcnt; i++){
        for (int j = 0; j < nsz[i]; j++)
            a[++ k] = nval[i][j];
        nsz[i] = 0;

        for (int j = 0; j < osz[i]; j++)
            cnt[i][oval[i][j]] = 0;
        osz[i] = 0;
    }
    blockcnt = 0;
    build();
}

int erase(int id) {
    int tot = 0;
    for (int i = 0; i < blockcnt; i++){
        tot += nsz[i];
        if (tot >= id){
            int p = nsz[i] - (tot - id) - 1;
            cnt[i][nval[i][p]] --;
            int res = nval[i][p];
            for (int j = p; j < nsz[i]; j++)
                nval[i][j] = nval[i][j + 1];
            nsz[i] --;
            return res;
        }
    }
}

void insert(int id, int x){
    int tot = 0;
    for (int i = 0; i < blockcnt; i++){
        tot += nsz[i];
        if (tot >= id){
            oval[i][osz[i] ++] = x;
            cnt[i][x] ++;
            int p = id - (tot - nsz[i]);
            for (int j = nsz[i]; j > p; j--)
                nval[i][j] = nval[i][j - 1];
            nval[i][p] = x;
            ++ nsz[i];
        }
    }
}

void shift(int l, int r){
    int x = erase(r);
    insert(l - 1, x);
    if (++ z > 800)
        rebuild(), z = 0;
}

int query(int r, int k){
    int tot = 0, res = 0;
    for (int i = 0; i < blockcnt; i++){
        tot += nsz[i];
        if (tot <= r){
            res += cnt[i][k];
        }else{
            tot -= nsz[i];
            for (int j = 0; j + tot < r; j++)
                if (nval[j][j] == k) res ++;
            return res;
        }   
    }
}

int query(int l, int r, int k){
    return query(r, k) - query(l - 1, k);
}

void Hollwo_Pelw() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    build();
    cin >> q;
    while (q--){
        int t, l, r;
        cin >> t >> l >> r;
        sadd(l, ans), sadd(r, ans);
        if (l > r) swap(l, r);

        if (t == 1){
            shift(l, r);
        }else{
            cin >> t; sadd(t, ans);
            cout << (ans = query(l, r, t)) << "\n";
        }
    }
}

