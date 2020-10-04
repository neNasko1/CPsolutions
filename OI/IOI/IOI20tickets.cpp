#include "tickets.h"
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
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

long long find_maximum(int k, vector<vector<int> > x) {
	ll n = x.size();
	ll m = x[0].size();
    vector<vector<int> > answer;
	vector<vector<pair<ll, ll> > > pr;
	priority_queue<pair<ll, ll> > pq;
	vector<ll> got;
	got.resize(n);
	ll ans = 0;
	for (ll i = 0; i < n; i++) {
        vector<int> row(m);
        for(ll j = 0; j < m; j++) {
            row[j] = -1;
		}
		for(ll j = m - k; j < m; j ++) {
            ans += x[i][j];
		}
		pq.push({-x[i][0] - x[i][m - k], i});
		answer.push_back(row);
	}
	ll iter = n * k / 2;
	for(ll i = 0; i < iter; i ++) {
        auto curr = pq.top(); pq.pop();
        ans += curr.first;
        got[curr.second] ++;
        if(got[curr.second] < k) {
            pq.push({-x[curr.second][got[curr.second]] - x[curr.second][m - k + got[curr.second]], curr.second});
        }
	}
    ll cnt = 0;
    for(ll i = 0; i < n; i ++) {
        for(ll j = 0; j < got[i]; j ++) {
            answer[i][j] = (cnt + j) % k;
        }
        cnt += got[i];
        ll group = cnt;
        for(ll j = m - k + got[i]; j < m; j ++) {
            answer[i][j] = group % k;
            group ++;
        }
    }
	allocate_tickets(answer);
	return ans;
}
