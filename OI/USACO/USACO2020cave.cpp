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

const ll MAX_N = 1e3 + 10;
char grid[MAX_N][MAX_N];
vector<pair<pair<ll, ll>, ll> > inter[MAX_N];
ll pow2[MAX_N * MAX_N];
ll par[MAX_N * MAX_N], sz[MAX_N * MAX_N], up[MAX_N * MAX_N], ans[MAX_N * MAX_N];

ll find(ll x) {
	if(x == par[x]) {
		return x;
	} else {
		return par[x] = find(par[x]);
	}
}

void merge(ll x, ll y) {
	x = find(x); y = find(y);
	if(x == y) {return;}
	if(sz[x] < sz[y]) {swap(x, y);}
	par[y] = x;
	sz[x] += sz[y];
	up[x] |= up[y];
	ans[x] = (ans[x] * ans[y]) % mod;
}

bool intersect(const pair<ll, ll> &a, const pair<ll, ll> &b) {
	return !(a.first > b.second || a.second < b.first);
}

signed main() {	
	freopen("cave.in", "r", stdin);
	freopen("cave.out", "w", stdout);
	pow2[0] = 1;
	par[0] = 0; sz[0] = 1; ans[0] = 1;
	for(ll i = 1; i < MAX_N * MAX_N; i ++) {
		pow2[i] = (pow2[i - 1] * 2ll) % mod;
		par[i] = i; sz[i] = 1; ans[i] = 1;
	}
	ll n, m;
	cin >> n >> m;
	ll cnt = 0;
	for(ll i = 0; i < n; i ++) {
		ll curr = 0;
		for(ll j = 0; j < m; j ++) {
			cin >> grid[i][j];
			if(grid[i][j] == '.') {
				curr ++;
			} else {
				if(curr != 0) {
					inter[i].push_back({{j - curr, j - 1}, cnt ++});
				} 
				curr = 0;
			}
		}
		if(curr != 0) {
			inter[i].push_back({{n - curr, n - 1}, cnt ++});
		}
	}
	ll ret = 1;
	for(ll i = n - 1; i >= 0; i --) {
		for(auto it : inter[i]) {
			up[find(it.second)] = true; 
		}
		ll l = 0;
		for(ll j = 0; j < inter[i].size(); j ++) {
			l = max(l - 1, 0ll);
			while(l < (ll)inter[i + 1].size() && inter[i + 1][l].first.first <= inter[i][j].first.second) {
				if(intersect(inter[i + 1][l].first, inter[i][j].first)) {
					merge(inter[i][j].second, inter[i + 1][l].second);
				}
				l ++;
			}
		}
		for(auto it : inter[i]) {
			int curr = find(it.second);
			if(up[curr]) {
				up[curr] = false; 					
				ans[curr] = (ans[curr] + 1) % mod;
			} 
		}
	}	
	for(int i = 0; i < MAX_N * MAX_N; i ++) {
		if(find(i) == i) {
			ret = (ret * ans[i]) % mod;
		}
	}
	cout << ret << endl;
	return 0;
}

