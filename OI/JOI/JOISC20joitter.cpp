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

const int MAX_N = 1e5 + 10;

ll par[MAX_N], sz[MAX_N];
set<pair<int, int>> perr[MAX_N];

set<pair<int, int> > between;
set<int> toClique[MAX_N];

ll ans, in[MAX_N];

int find(int x) {
	if(x == par[x]) {
		return x;
	} else {
		return par[x] = find(par[x]);
	}
}

void remove(int x, int y) {
	ll compx = find(x), compy = find(y);
	if(compx == compy) {return;}
	if(between.find({compx, compy}) == between.end()) {
		between.erase({compx, compy});			
	}

 	perr[compx].erase({x, y});
	perr[compy].erase({x, y});

	ans -= sz[compy];
	in[compy] --;
	toClique[x].erase(compy);
} 

void add(int x, int y) {
	ll compx = find(x), compy = find(y);
	if(compx == compy) {return;}
	if(toClique[x].find(compy) != toClique[x].end()) {return;}
	
	between.insert({compx, compy});
 	perr[compx].insert({x, y});
	perr[compy].insert({x, y});
	
	ans += sz[compy];
	in[compy] ++;
	toClique[x].insert(compy);
}

stack<pair<int, int> > st;

void merge(int x, int y) {
	if(x == y) {return;}
	ans -= (sz[x] * sz[x] - sz[x]);
	ans -= (sz[y] * sz[y] - sz[y]);
	if(perr[x].size() + sz[x] < perr[y].size() + sz[y]) {swap(x, y);}
	vector<pair<int, int> > toMove;
	for(auto it : perr[y]) {toMove.push_back(it);}
	perr[y].clear();
	for(auto it : toMove) {
		remove(it.first, it.second);
		st.push(it);
	}
	ans += in[x] * sz[y];
	par[y] = x;
	sz[x] += sz[y]; 
	ans += (sz[x] * sz[x] - sz[x]);
}

void fixStack() {
	while(!st.empty()) {
		auto curr = st.top(); st.pop();
		pair<int, int> comp = {find(curr.first), find(curr.second)};
		if(comp.first == comp.second) {continue;}
		if(between.find({comp.second, comp.first}) != between.end()) {
			merge(comp.first, comp.second);
		} else {
			add(curr.first, curr.second);
		}
	}	
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	for(int i = 0; i < MAX_N; i ++) {par[i] = i; sz[i] = 1;}
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i ++) {
		int a, b;
		cin >> a >> b;
		st.push({a, b});
		fixStack();
		cout << ans << endl;
	}
	return 0;
}

