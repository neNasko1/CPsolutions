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

const int MAX_N = 1e5 + 10, LOG = 20;
vector<int> g[MAX_N];
int par[MAX_N][LOG], d[MAX_N];

void dfs(int x, int p) {
	par[x][0] = p;
	for(int i = 1; i < LOG; i ++) {
		par[x][i] = par[par[x][i - 1]][i - 1];
	}	
	d[x] = d[p] + 1;
	for(auto it : g[x]) {
		if(it == p) {continue;}
		dfs(it, x);
	}
}

int ans[MAX_N], pref[MAX_N];

pair<int, int> lca(int a, int b) {
	for(int i = LOG - 1; i >= 0; i --) {
		if(d[par[a][i]] >= d[b]) {
			a = par[a][i];
		}
	}
	if(a == b) {return {a, -1};}
	for(int i = LOG - 1; i >= 0; i --) {
		if(par[a][i] != par[b][i]) {
			a = par[a][i];
			b = par[b][i];
		}
	}
	return {par[a][0], 1};
}

int ret[MAX_N];

int dfsAns(int x, int p) {
	int currSum = 0;
	for(auto it : g[x]) {
		if(it == p) {continue;}
		currSum += dfsAns(it, x);
	}	
	currSum += pref[x];
	ret[x] = currSum + ans[x];
	return currSum;
}

signed main() {	
	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);
	int n, k;
	cin >> n >> k;
	for(int i = 0; i < n - 1; i ++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b); 
		g[b].push_back(a);
	}
	dfs(1, 0);
	for(int i = 0; i < k; i ++) {
		int a, b;
		cin >> a >> b;
		if(d[a] < d[b]) {swap(a, b);}
		auto curr = lca(a, b);
		ans[curr.first] ++;
		if(curr.second == -1) {
			pref[a] ++;
			pref[curr.first] --;
		} else {
			pref[a] ++;
			pref[b] ++;
			pref[curr.first] -= 2;			
 		}
	}
	dfsAns(1, 0);
	int mx = -1;
	for(int i = 1; i <= n; i ++) {
		chkmax(mx, ret[i]);
	}
	cout << mx << endl;
    return 0;
}

