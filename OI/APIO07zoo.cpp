#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

///Dp with states beg, end where beg is the bitmask of the first 5 animal cages (1-on, 0-off), end = last 5 bits;

const int MAX_N = 5e4 + 10;
vector<pair<int, int> >  kids[MAX_N];

ll findMatching(ll mask, int e) {
    int ret = 0;
    for(auto it : kids[e]) {
        if((mask & it.first) != it.first) {
            ret ++;
        } else if(mask & (it.second)) {
            ret ++;
        }
    }
    return ret;
}

int dp[MAX_N][1 << 6][1 << 6];

void solve() {
    int n, c;
    cin >> n >> c;
    for(int i = 0; i < n; i ++) {
        kids[i].clear();
    }
    for(int i = 0; i < c; i ++) {
        int e, f, l;
        cin >> e >> f >> l;
        int scary = 0, happy = 0;
        for(int j = 0; j < f; j ++) {
            int a;
            cin >> a;
            a += n;
            scary |= (1 << ((a - e) % n));
        }
        for(int j = 0; j < l; j ++) {
            int a;
            cin >> a;
            a += n;
            happy |= (1 << ((a - e) % n));
        }
        kids[e - 1].push_back({scary, happy});
    }
    for(int k = 0; k <= n; k ++) {
        for(int i = 0; i < (1 << 5); i ++) {
            for(int j = 0; j < (1 << 5); j ++) {
                dp[k][i][j] = -mod;
            }
        }
        for(int i = 0; i < (1 << 5); i ++) {
            dp[k][i][i] = 0;
        }
    }
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < (1 << 5); j ++) {
            for(int k = 0; k < (1 << 5); k ++) {
                int newk;
                newk = k / 2;
                chkmax(dp[i + 1][j][newk], dp[i][j][k] + findMatching(k, i));
                newk = k / 2 + (1 << 4);
                chkmax(dp[i + 1][j][newk], dp[i][j][k] + findMatching(k, i));
            }
        }
    }
    int ret = 0;
    for(int i = 0; i < (1 << 5); i ++) {
        chkmax(ret, dp[n][i][i]);
    }
    cout << ret << endl;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}


