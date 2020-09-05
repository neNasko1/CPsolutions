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

///Sos dp on mask - the state is which subset of words are we building a trie on given that we have already gotten their common letters.

const int MAX_N = 16, ALPH = 30;
ll dp[1 << MAX_N];
ll cnt[MAX_N][ALPH];
ll eq[1 << MAX_N];
int n;

ll rec(ll mask) {
    if(dp[mask] != -1) {
        return dp[mask];
    }
    if(mask == 0) {return 0;}
    if((mask & (mask - 1)) == 0) {return 0;}
    ll currPref = eq[mask];
    dp[mask] = mod * mod;
    for(int i = (mask - 1) & mask; i > 0; i = (i - 1) & mask) {
        chkmin(dp[mask], rec(i) + rec(mask ^ i) + eq[i] + eq[mask ^ i] - 2 * eq[mask]);
        //cout << mask << " " << i << " " << (mask ^ i) << " " << dp[mask] << endl;
    }
    //cout << mask << " " << dp[mask] << endl;
    return dp[mask];
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i = 0; i < n; i ++) {
        string in;
        cin >> in;
        for(auto it : in) {
            cnt[i][it - 'a'] ++;
        }
    }
    for(int mask = 0; mask < (1 << n); mask ++) {
        eq[mask] = 0;
        dp[mask] = -1;
        for(int c = 0; c < ALPH; c ++) {
            int mn = mod;
            for(int i = 0; i < n; i ++) if((1 << i) & mask) {
                chkmin(mn, cnt[i][c]);
            }
            eq[mask] += mn;
        }
    }
    cout << rec((1 << n) - 1) + eq[(1 << n) - 1] + 1 << endl;
    return 0;
}


