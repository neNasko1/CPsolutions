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

///We will solve it differently for every number of places the beetle goes to. If the positions are a1->a2->a3...a->k then the amount of water you can get is k * m - k * a1 - (k - 1) * (a1 - a2)....
///Dp on interval [l, r] and a flag, dp[l][r][0] means we are in the left end and dp[l][r][1] means we are in the right. The transitions are to dp[l - 1][r][0], dp[l][r + 1][1];

const ll MAX_N = 3e2 + 10;
ll dp[MAX_N][MAX_N][2];
ll arr[MAX_N], n, m;

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    for(ll i = 0; i < n; i ++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    if(arr[n - 1] < 0) {
        for(ll i = 0; i < n; i ++) {
            arr[i] *= -1;
        }
    }
    ll first = n - 1;
    while(first - 1 >= 0 && arr[first - 1] >= 0) {
        first --;
    }
    ll ret = 0;
    for(ll need = 1; need <= n; need ++) {
        for(ll i = 0; i < n; i ++) {
            for(ll j = 0; j < n; j ++) {
                dp[i][j][0] = dp[i][j][1] = mod;
            }
        }
        if(first < n) {
            dp[first][first][0] = need * arr[first];
            dp[first][first][1] = need * arr[first];
        }
        if(first > 0) {
            dp[first - 1][first - 1][0] = -need * arr[first - 1];
            dp[first - 1][first - 1][1] = -need * arr[first - 1];
        }
        for(ll len = 1; len <= need; len ++) {
            for(ll l = 0; l + len - 1 < n; l ++) {
                ll r = l + len - 1, pos;
                //cout << l << " " << r << " " << dp[l][r][0] << " " << dp[l][r][1] << endl;
                pos = arr[l];
                if(l > 0) {
                    chkmin(dp[l - 1][r][0], dp[l][r][0] + (need - len) * abs(pos - arr[l - 1]));
                }
                if(r + 1 < n) {
                    chkmin(dp[l][r + 1][1], dp[l][r][0] + (need - len) * abs(pos - arr[r + 1]));
                }
                pos = arr[r];
                if(l > 0) {
                    chkmin(dp[l - 1][r][0], dp[l][r][1] + (need - len) * abs(pos - arr[l - 1]));
                }
                if(r + 1 < n) {
                    chkmin(dp[l][r + 1][1], dp[l][r][1] + (need - len) * abs(pos - arr[r + 1]));
                }
            }
        }
        for(ll l = 0; l + need - 1 < n; l ++) {
            ll r = l + need - 1;
            chkmax(ret, need * m - dp[l][r][0]);
            chkmax(ret, need * m - dp[l][r][1]);
        }
        //cout << need << " " << ret << endl;
    }
    cout << ret << endl;
    return 0;
}


