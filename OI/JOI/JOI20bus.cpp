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
const ll mod = 1e12 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "
 
const ll MAX_N = 2e2 + 10, MAX_W = 1e5 + 10;
vector<pair<pair<int, int>, pair<ll, ll> > > edges;
bitset<MAX_W> off;
vector<pair<pair<int, ll>, int> > g[MAX_N];
ll dist[2][MAX_N];
int n, m;
 
void dij(ll ind, ll start) {
	for(ll i = 0; i < MAX_N; i ++) {
		dist[ind][i] = mod;
	}
	priority_queue<pair<ll, ll> > pq;
	pq.push({0, start});
	dist[ind][start] = 0;
	while(!pq.empty()) {
		auto curr = pq.top(); pq.pop();
		curr.first *= -1;
      	if(curr.first != dist[ind][curr.second]) {continue;}
		for(auto it : g[curr.second]) {
			if(off[it.second]) {continue;}
			ll nxt = it.first.first;
			if(dist[ind][nxt] > curr.first + it.first.second) {
				dist[ind][nxt] = curr.first + it.first.second;
				pq.push({-dist[ind][nxt], nxt});
			}	
		}
	}
	return;
	cout << "Started from " << start << endl;
	for(ll i = 1; i <= n; i ++) {
		cout << dist[ind][i] << " ";
	}
	cout << endl;
} 
 
ll distFull[MAX_N][MAX_N];
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	for(ll i = 0; i < MAX_N; i ++) {
		for(ll j = 0; j < MAX_N; j ++) {
			distFull[i][j] = mod;
		}
	}
	for(ll i = 0; i < MAX_N; i ++) {
		distFull[i][i] = 0;
	} 
	
	cin >> n >> m;
	edges.resize(m);
	for(ll i = 0; i < m; i ++) {
		cin >> edges[i];
	}
	random_shuffle(edges.begin(), edges.end());
 
	for(int i = 0; i < m; i ++) {
		off[2 * i] = false;
		off[2 * i + 1] = true;
		g[edges[i].first.first].push_back({{edges[i].first.second, edges[i].second.first}, 2 * i}); 
		g[edges[i].first.second].push_back({{edges[i].first.first, edges[i].second.first}, 2 * i + 1}); 
		chkmin(distFull[edges[i].first.first][edges[i].first.second], edges[i].second.first);
	}
	for(ll k = 1; k <= n; k ++) {
		for(ll i = 1; i <= n; i ++) {
			for(ll j = 1; j <= n; j ++) {
				chkmin(distFull[i][j], distFull[i][k] + distFull[k][j]);
			}
		}
	}
	ll ret = distFull[1][n] + distFull[n][1];
	vector<pair<ll, int> > indices;
	for(int i = 0; i < m; i ++) {
		ll u = edges[i].first.first, v = edges[i].first.second, cost = edges[i].second.first, price = edges[i].second.second;
		ll firstHalf = min(distFull[1][v] + cost + distFull[u][n], (ll)distFull[1][n]);
		ll secondHalf = min(distFull[n][v] + cost + distFull[u][1], (ll)distFull[n][1]);
		indices.push_back({firstHalf + secondHalf + price, i});
	}
	sort(indices.begin(), indices.end());
	for(ll i = 0; i < m; i ++) {
		int ind = indices[i].second;
		if(indices[i].first >= ret) {continue;}
		off[2 * ind] = true;
		off[2 * ind + 1] = false;
		dij(0, 1);
		dij(1, n);
		chkmin(ret, edges[ind].second.second + dist[0][n] + dist[1][1]);
		off[2 * ind] = false;
		off[2 * ind + 1] = true;
	}
	if(ret < mod) {
		cout << ret << endl;
	} else {
		cout << -1 << endl;
	}
	return 0;
}