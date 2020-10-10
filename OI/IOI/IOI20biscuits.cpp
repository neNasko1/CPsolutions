#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
template<class T, class T2> inline ostream &operator <<(ostream &out, const pair<T, T2> &x) { out << x.first << " " << x.second; return out;}
template<class T, class T2> inline istream &operator >>(istream &in, pair<T, T2> &x) { in >> x.first >> x.second; return in;}
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "

long long count_tastiness(long long x, std::vector<long long> a) {
    const ll MAX_BIT = 63;
    vector<ll> b(MAX_BIT), dp(MAX_BIT);
    a.resize(MAX_BIT);
    b[0] = a[0];
    for(ll i = 1; i < MAX_BIT; i ++) {
        b[i] = b[i - 1] / 2ll + a[i];
    }
    dp[0] = 1;
    for(ll i = 0; i < MAX_BIT - 1; i ++) {
        ll need = max(x - a[i], 0ll) * 2ll;
        for(ll j = i - 1; j >= 0 && need <= b[j]; j --) {
            if(b[j] >= need + x) {
                dp[i + 1] += dp[j];
                need = max(0ll, need + x - a[j]) * 2ll;
            } else {
                need = max(0ll, need - a[j]) * 2ll;
            }

        }
        if(!need) {
            dp[i + 1] ++;
        }
        dp[i + 1] += dp[i];
    }
	return dp[MAX_BIT - 1];
}

