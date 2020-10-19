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
 
const ll MAX_N = 2e5 + 10;
ll n, k;
string in;
ll dp[4][MAX_N];
 
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> k >> in;
	string JOI = "#JOI";
	for(ll j = 1; j <= 3; j ++) {
		dp[j][0] = mod;
		deque<ll> dq;
		for(ll i = 1; i <= n; i ++) {
			char curr = in[i - 1];
			if(curr == JOI[j]) {
				dq.push_back(i);
			}		
			while(dq.size() > k) {
				dq.pop_front();
			}
			dp[j][i] = dp[j][i - 1] + 1;
			if(dq.size() == k) {
				chkmin(dp[j][i], i - dq.front() + 1 - k + dp[j - 1][dq.front() - 1]);
			}
		}
	}
	ll ret = mod;
	for(ll i = 0; i <= n; i ++) {
		chkmin(ret, dp[3][i]);
	}
	if(ret < MAX_N) {
		cout << ret << endl;
	} else {
		cout << -1 << endl;
	}
    return 0;
}