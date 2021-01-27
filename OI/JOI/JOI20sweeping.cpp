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

const int MAX_N = 1e6 + 10;

struct Query {
	int type, val, x, y;
};

vector<Query> queries;
pair<int, int> ans[MAX_N];
int n, m, q, cnt = 0;

int on[MAX_N];
int wherex[MAX_N], wherey[MAX_N];

void solve(int x, int y, vector<Query> &now) {
	int midx = (x + n - y) / 2ll, midy = (y + n - x) / 2ll;
	if(now.empty()) {return;}
	
	vector<Query> up, rght;
	priority_queue<int> pqx, pqy;
	map<int, vector<int> > groupx, groupy;
	map<int, int> valx, headx;
	map<int, int> valy, heady;	
	int helpCnt = 0;
	
	for(auto it : now) {
		if(it.type == 4) {
			if(it.y > midy) {
				on[it.val] = 1;
				up.push_back(it);
				continue;
			} else if(it.x > midx) {
				on[it.val] = 2;
				rght.push_back(it);
				continue;
			}
			
			int whereToPut;
			on[it.val] = 0;
			
			if(headx.find(it.x) == headx.end()) {
				headx[it.x] = ++ helpCnt;
				valx[helpCnt] = it.x;
			}
			whereToPut = headx[it.x];		
			wherex[it.val] = whereToPut;
			if(groupx[whereToPut].empty()) {pqx.push(-it.x);}
			groupx[whereToPut].push_back(it.val);
		
			if(heady.find(it.y) == heady.end()) {
				heady[it.y] = ++ helpCnt;
				valy[helpCnt] = it.y;
			}
			whereToPut = heady[it.y];		
			wherey[it.val] = whereToPut;
			if(groupy[whereToPut].empty()) {pqy.push(-it.y);}
			groupy[whereToPut].push_back(it.val);						
		} else if(it.type == 1) {
			if(on[it.val] == 0) {
 				ans[it.x] = {valx[wherex[it.val]], valy[wherey[it.val]]}; 
			} else if(on[it.val] == 1) {
				up.push_back(it);
			} else if(on[it.val] == 2) {
				rght.push_back(it);
			}
		} else if(it.type == 2) {
			if(n - it.val <= midx) {
				while(!pqx.empty() && -pqx.top() < n - it.val) {
					auto curr = -pqx.top(); pqx.pop();
					
					if(headx.find(n - it.val) == headx.end()) {
						headx[n - it.val] = ++ helpCnt;
						valx[helpCnt] = n - it.val;
						pqx.push(-n + it.val);
					} 					
					int heada = headx[curr], headb = headx[n - it.val];
					
					if(groupx[heada].size() >= groupx[headb].size()) {
						for(auto toMove : groupx[headb]) {
							groupx[heada].push_back(toMove);
							wherex[toMove] = heada;
						}
						valx[heada] = n - it.val;
						headx[n - it.val] = heada;
						headx.erase(curr);
						groupx.erase(headb);
						valx.erase(headb);
					} else {
						for(auto toMove : groupx[heada]) {
							groupx[headb].push_back(toMove);
							wherex[toMove] = headb;
						}						
						headx.erase(curr);
						groupx.erase(heada);
						valx.erase(heada);
					}					
				}
				up.push_back(it);
			} else {
				while(!pqy.empty() && -pqy.top() <= it.val) {
					auto curr = -pqy.top(); pqy.pop();		
					int heada = heady[curr];			
					for(auto toMove : groupy[heada]) {
						if(on[toMove] == 0) {
							rght.push_back({4, toMove, n - it.val, valy[wherey[toMove]]});
							on[toMove] = 2;
						}
					}
					heady.erase(curr);
					groupy.erase(heada);
					valy.erase(heada);
				}
				rght.push_back(it);
			}
		} else if(it.type == 3) {
			if(n - it.val <= midy) {
				while(!pqy.empty() && -pqy.top() < n - it.val) {
					auto curr = -pqy.top(); pqy.pop();
					
					if(heady.find(n - it.val) == heady.end()) {
						heady[n - it.val] = ++ helpCnt;
						valy[helpCnt] = n - it.val;
						pqy.push(-n + it.val);
					} 					
					int heada = heady[curr], headb = heady[n - it.val];
					
					if(groupy[heada].size() >= groupy[headb].size()) {
						for(auto toMove : groupy[headb]) {
							groupy[heada].push_back(toMove);
							wherey[toMove] = heada;
						}
						valy[heada] = n - it.val;
						heady[n - it.val] = heada;
						heady.erase(curr);
						groupy.erase(headb);
						valy.erase(headb);
					} else {
						for(auto toMove : groupy[heada]) {
							groupy[headb].push_back(toMove);
							wherey[toMove] = headb;
						}						
						heady.erase(curr);
						groupy.erase(heada);
						valy.erase(heada);
					}					
				}
				rght.push_back(it);
			} else {
				while(!pqx.empty() && -pqx.top() <= it.val) {
					auto curr = -pqx.top(); pqx.pop();		
					int heada = headx[curr];			
					for(auto toMove : groupx[heada]) {
						if(on[toMove] == 0) {
							up.push_back({4, toMove, valx[wherex[toMove]], n - it.val});
							on[toMove] = 1;
						}
					}
					headx.erase(curr);
					groupx.erase(heada);
					valx.erase(heada);
				}
				up.push_back(it);
			}			
		}
		continue;
	}
	
	for(auto it : now) {if(it.type == 4) {on[it.val] = -1;}}
	
	groupx.clear();
	groupy.clear();
	valx.clear();
	valy.clear();
	headx.clear();
	heady.clear();
	
	if(x + midy + 1 <= n) {
		solve(x, midy + 1, up);
	}
	
	if(y + midx + 1 <= n) {
		solve(midx + 1, y, rght);
	}
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	for(int i = 0; i < MAX_N; i ++) {ans[i] = {-1, -1}; on[i] = -1;}
	cin >> n >> m >> q;
	for(int i = 0; i < m; i ++) {
		int x, y;
		cin >> x >> y;
		queries.push_back({4, ++ cnt, x, y});
	}
	for(int i = 0; i < q; i ++) {
		int t;
		cin >> t;
		if(t == 1) {
			int ind;
			cin >> ind; 
			queries.push_back({t, ind, i, -1});
		} else if(t == 2) {
			int val;
			cin >> val;
			queries.push_back({t, val, -1, -1});
		} else if(t == 3) {
			int val;
			cin >> val;
			queries.push_back({t, val, -1, -1});
		} else {
			int x, y;
			cin >> x >> y;
			queries.push_back({t, ++ cnt, x, y});
		}
	}
	
	solve(0, 0, queries);

	for(int i = 0; i < q; i ++) {
		if(ans[i].first != -1) {
			cout << ans[i] << endl;
		}
	}
	return 0;
}

