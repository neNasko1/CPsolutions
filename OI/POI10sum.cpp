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

///We calculate dp[k](smallest number === k(mod minimum element)) for every group of congruent elements mod minimum element.

const ll MAX_N = 5e4  +10;
int arr[MAX_N], n;
int dp[MAX_N];
int mn = mod;

void prec(int now) {
    int lcm = (mn) / __gcd(mn, now);
    int ed = mn / lcm;
    for(int start = 0; start < ed; start ++) {
        for(int j = 0, curr = dp[start % mn]; j < lcm; j ++, curr += now) {
            chkmin(dp[curr % mn], curr);
            curr = dp[curr % mn];
        }
        for(int j = 0, curr = dp[start % mn]; j < lcm; j ++, curr += now) {
            chkmin(dp[curr % mn], curr);
            curr = dp[curr % mn];
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(ll i = 0; i < n; i ++) {
        cin >> arr[i];
        chkmin(mn, arr[i]);
    }
    dp[0] = 0;
    for(ll i = 1; i < MAX_N; i ++) {
        dp[i] = 2 * mod;
    }
    for(ll i = 0; i < n; i ++) {
        prec(arr[i]);
    }
    ll q;
    cin >> q;
    while(q --) {
        ll k;
        cin >> k;
        if(dp[k % mn] <= k) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }
    }
    return 0;
}
