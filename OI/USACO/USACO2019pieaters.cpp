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
const ll mod = 1e13 + 7;
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const ll MAX_N = 3e2 + 10;
ll dp[MAX_N][MAX_N];
ll bestOut[MAX_N/*l*/][MAX_N/*r*/][MAX_N/*k*/];
ll w[MAX_N][MAX_N];

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ifstream in;
    in.open("pieaters.in");
    ofstream out;
    out.open("pieaters.out");
    for(ll i = 0; i < MAX_N; i ++) {
        fill_n(dp[i], MAX_N, 0);
        for(ll j = 0; j < MAX_N; j ++) {
            fill_n(bestOut[i][j], MAX_N, -mod);
        }
        fill_n(w[i], MAX_N, -mod);
    }
    ll n, m;
    in >> n >> m;
    for(ll i = 0; i < m; i ++) {
        ll a, b, c;
        in >> c >> a >> b;
        w[a][b] = c;
    }

    for(ll len = 0; len < n; len ++) {
        for(ll l = 1; l + len <= n; l ++) {
            for(ll k = 1; k <= n; k ++) {
                if(l <= k && k <= l + len) {
                    bestOut[l][l + len][k] = w[l][l + len];
                } else {
                    continue;
                }
                chkmax(bestOut[l][l + len][k], max(bestOut[l + 1][l + len][k], bestOut[l][l + len - 1][k]));
            }
        }
    }
    for(ll len = 0; len < n; len ++) {
        for(ll l = 1; l + len <= n; l ++) {
            ll r = l + len;
            for(ll k = l; k <= r; k ++) {
                ll curr = dp[l][k - 1] + dp[k + 1][r];
                curr += bestOut[l][r][k];
                chkmax(dp[l][r], curr);
            }
        }
    }
    out << dp[1][n] << endl;
    return 0;
}

