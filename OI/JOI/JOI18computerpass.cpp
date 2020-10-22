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
const ll mod = 1e15 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl
  
const ll MAX_N = 1e5 + 10;
ll dist[4][MAX_N];
vector<pair<ll, ll> > g[MAX_N];
ll dp[MAX_N][4];
ll n, m;

void dij(ll ind, ll start) {
	for(ll i = 0; i < MAX_N; i ++) {
		dist[ind][i] = mod;
	}
	dist[ind][start] = 0;
	priority_queue<pair<ll, ll> > pq;
	pq.push({0, start});
	while(!pq.empty()) {
		auto curr = pq.top(); pq.pop();
		curr.first *= -1;
		if(curr.first != dist[ind][curr.second]) {continue;}
		for(auto it : g[curr.second]) {
			if(dist[ind][it.first] > curr.first + it.second) {
				dist[ind][it.first] = curr.first + it.second;
				pq.push({-dist[ind][it.first], it.first});
			}
		}
	}
}

vector<ll> can;  

bool cmp(ll a, ll b) {
	return dist[2][a] < dist[2][b];
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	ll s, t, u, v;
	cin >> s >> t >> u >> v;
	for(ll i = 0; i < m; i ++) {
		ll a, b, c;
		cin >> a >> b >> c;
		g[a].push_back({b, c});
		g[b].push_back({a, c});
	}
	dij(0, u);
	dij(1, v);
	dij(2, s);
	dij(3, t);
	ll minPath = dist[2][t];
	for(ll i = 1; i <= n; i ++) {
		for(ll j = 0; j < 4; j ++) {
			dp[i][j] = mod;
		}
		if(dist[2][i] + dist[3][i] == minPath) {
			can.push_back(i);
		}
	}    
	dp[s][0] = 0;
	sort(can.begin(), can.end(), cmp);
	for(auto it : can) {
		for(auto prv : g[it]) {
			if(dist[2][prv.first] + prv.second + dist[3][it] == minPath) {
				for(ll mask = 0; mask < 4; mask ++) {
					chkmin(dp[it][mask], dp[prv.first][mask]);
				}
			}
		}
		for(ll mask = 0; mask < 4; mask ++) {
			if(!(mask & 1)) {
				chkmin(dp[it][mask + 1], dp[it][mask] + dist[0][it]);
			}
			if(!(mask & 2)) {				
				chkmin(dp[it][mask + 2], dp[it][mask] + dist[1][it]);
			}
		}
	}
	cout << min(dp[t][3], dist[0][v]) << endl;
    return 0;
}