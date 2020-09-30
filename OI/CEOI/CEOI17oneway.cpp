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

///If a edge is in a cycle it is always 'B', we construct dfs-tree then we can process each needed path X->Y as X->LCA->Y where verteces on path from X->LCA are going up the tree and LCA->Y down the tree

const int MAX_N = 1e5 + 10, LOG = 20;
int par[MAX_N][LOG];
vector<pair<int, int> > g[MAX_N], tree[MAX_N];
int ans[MAX_N];
int low[MAX_N], in[MAX_N], tme = 0, d[MAX_N];
int coming[MAX_N], going[MAX_N];

void dfs(int x, int p, int ind) {
	par[x][0] = p;
	for(int i = 1; i < LOG; i ++) {
		par[x][i] = par[par[x][i - 1]][i - 1];
	}
	in[x] = low[x] = tme ++;
	d[x] = d[p] + 1;
	for(auto it : g[x]) {
		if(abs(it.second) == ind) {continue;} 
		if(in[it.first] == -1) {
			dfs(it.first, x, abs(it.second));
			chkmin(low[x], low[it.first]);
			if(low[it.first] == in[it.first]) {
				ans[abs(it.second)] = 10;
			}
			tree[x].push_back(it);
		} else {
			chkmin(low[x], in[it.first]);
		}
	}
}

int lca(int a, int b) {
	if(d[b] > d[a]) {swap(a, b);}
	for(int i = LOG - 1; i >= 0; i --) {
		if(d[par[a][i]] >= d[b]) {
			a = par[a][i];
		}
	}
	if(a == b) {return a;}
	for(int i = LOG - 1; i >= 0; i --) {
		if(par[a][i] != par[b][i]) {
			a = par[a][i];
			b = par[b][i];
		}
	}
	return par[a][0];
}

void dfs2(int x, int ind) {
	for(auto it : tree[x]) {
		dfs2(it.first, it.second);
		going[x] += going[it.first];
		coming[x] += coming[it.first];
	}	
	if(ans[abs(ind)] != 10) {return;}
	ans[abs(ind)] = 0;
	if((coming[x])) {
	    if(ind < 0) {
		    ans[abs(ind)] = 2;
	    } else {
		    ans[abs(ind)] = 1;
	    }
	} else if(going[x]) {
	    if(ind > 0) {
		    ans[abs(ind)] = 2;
	    } else {
		    ans[abs(ind)] = 1;
	    }
	}
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= m; i ++) {
    	int a, b;
    	cin >> a >> b;
    	g[a].push_back({b, i});
    	g[b].push_back({a, -i});
    }
    for(int i = 1; i <= n; i ++) {
    	in[i] = -1;
    }
    vector<int> roots;
    for(int i = 1; i <= n; i ++) {
        if(in[i] == -1) {
            dfs(i, 0, -mod);
            roots.push_back(i);
        }
    }
    int p;
    cin >> p;
    while(p --) {
    	int a, b;
    	cin >> a >> b;
    	int c = lca(a, b);
    	coming[c] --;
    	going[c] --;
    	coming[a] ++;
    	going[b] ++;
    }
    for(auto it : roots) {
        dfs2(it, -1);
    }
    for(int i = 1; i <= m; i ++) {
    	if(ans[i] == 0) {
    		cout << 'B';
    	} else if(ans[i] == 1) {
    		cout << 'L';
    	} else {
    		cout << 'R';
    	}
    }
    return 0;
}

