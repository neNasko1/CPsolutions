#include "friend.h"
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

// Find out best sample

///We will use a different strategy on every protocol:
///Protocol 0 - we can treat the case similar as dp on tree, we will pretend to get i and then we can compensate later.
///Protocol 1 - the same as subtask 2 we get either host[i] or i
///Protocol 2 - we can compress i and host[i] in one vertex

const int MAX_N = 1e6 + 10;
int dp[MAX_N];

int findSample(int n, int confidence[], int host[], int protocol[]){
    int ans = 0;
    for(int i = 0; i < n; i ++) {
        dp[i] = confidence[i];
    }
    for(int i = n - 1; i > 0; i --) {
        if(protocol[i] == 0) {
            dp[host[i]] -= min(dp[i], dp[host[i]]);
            ans += dp[i];
        } else if(protocol[i] == 1) {
            dp[host[i]] += dp[i];
        } else {
            chkmax(dp[host[i]], dp[i]);
        }
    }
	return ans + dp[0];
}

