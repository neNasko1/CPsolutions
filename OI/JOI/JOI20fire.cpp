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

const ll MAX_N = 2e5 + 10, LOG = 20;

struct SegTree {
	ll tree[4 * MAX_N];
	void upd(ll curr, ll l, ll r, ll ind, ll val) {
		if(l == r && l == ind) {
			tree[curr] = val;
			return;
		} else if(r < ind || ind < l) {return;}
		ll m = (l + r) / 2ll;
		upd(curr * 2, l, m, ind, val);
		upd(curr * 2 + 1, m + 1, r, ind, val);
		tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
	}
	ll ans(ll curr, ll l, ll r, ll ql, ll qr) {
		if(ql <= l && r <= qr) {
			return tree[curr];
		} else if(l > qr || r < ql) {
			return 0;
		}
		ll m = (l + r) / 2ll;
		return ans(curr * 2, l, m, ql, qr) + ans(curr * 2 + 1, m + 1, r, ql, qr);
	}
};
	  
struct SparseTable {
    ll ans[LOG][MAX_N], arr[MAX_N];
    void construct(ll n, ll (&_arr)[MAX_N]) {
        for(ll i = 0; i < n; i ++) {arr[i] = _arr[i]; ans[0][i] = i;}
        for(ll j = 1; j < LOG; j ++) {
            for(ll i = 0; i + (1 << j) <= n; i ++) {
            	if(arr[ans[j - 1][i]] > arr[ans[j - 1][i + (1 << (j - 1))]]) {
					ans[j][i] = ans[j - 1][i];            		
            	} else {
            		ans[j][i] = ans[j - 1][i + (1 << (j - 1))];
            	}
            }
        }
    }
    ll query(ll l, ll r) {
        ll q = 0;
        while((1 << q) <= r - l + 1) {q ++;} q --;
        if(arr[ans[q][l]] > arr[ans[q][r - (1 << q) + 1]]) {
        	return ans[q][l];
        } else {
        	return ans[q][r - (1 << q) + 1];	
        }
    }
};

SegTree delta, m;
SparseTable sTable;
ll arr[MAX_N];
ll lft[MAX_N], rght[MAX_N];
ll n, q;
vector<pair<ll, ll> > events[MAX_N];
vector<pair<pair<ll, ll>, ll> > queries[MAX_N];
ll ans[MAX_N];

ll getAns(ll t, ll r) {
	if(r == -1) {return 0;}
	ll indCurr = sTable.query(max(0ll, r - t + 1), r);
	ll begCurr = max(indCurr, lft[indCurr] + t);
	ll cumm = (r - begCurr + 1) * arr[indCurr];
	if(indCurr == -1) {return cumm;}
	return delta.ans(1, 0, n - 1, 0, indCurr - 1) * t + m.ans(1, 0, n - 1, 0, indCurr - 1) + cumm;
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> q;
	for(ll i = 0; i < n; i ++) {
		cin >> arr[i];
	}	
	sTable.construct(n, arr);
	stack<pair<ll, ll> > st;
	st.push({mod, -mod});
	for(ll i = 0; i < n; i ++) {
		while(!st.empty() && st.top().first <= arr[i]) {
			st.pop();
		}
		lft[i] = st.top().second;
		st.push({arr[i], i});
	}
	while(!st.empty()) {st.pop();}	
	st.push({mod, n});
	for(ll i = n - 1; i >= 0; i --) {
		while(!st.empty() && st.top().first < arr[i]) {
			st.pop();
		}
		rght[i] = st.top().second;
		st.push({arr[i], i});
	}
	for(ll i = 0; i < n; i ++) {
		ll tmeRght = rght[i] - i;
		if(tmeRght < MAX_N) {
			events[tmeRght].push_back({i, 0}); 
		}
		
		ll tmeLft = i - lft[i];
		if(tmeLft < MAX_N) {
			events[tmeLft].push_back({i, 1});
		}
		
		ll tmeFull = rght[i] - lft[i];
		if(tmeFull < MAX_N) {
			events[tmeFull].push_back({i, 2});
		}
	}
	
	for(ll i = 0; i < q; i ++) {
		ll l, r, t;
		cin >> t >> l >> r;
		queries[t].push_back({{l - 1, r - 1}, i});
	}
	for(ll i = 0; i < n; i ++) {
		delta.upd(1, 0, n - 1, i, arr[i]);
	}
	for(ll tme = 1; tme <= n; tme ++) {
		for(auto it : events[tme]) {
			if(it.second == 0 || it.second == 1) {
				ll nowDelta = delta.ans(1, 0, n - 1, it.first, it.first);
				ll nowm = m.ans(1, 0, n - 1, it.first, it.first);
				if(nowDelta == 0) {
					m.upd(1, 0, n - 1, it.first, nowDelta * (tme + 1) + nowm + arr[it.first] * tme);
				} else {
					m.upd(1, 0, n - 1, it.first, nowDelta * tme + nowm);					
				}
				delta.upd(1, 0, n - 1, it.first, nowDelta - arr[it.first]);
			} else {
				m.upd(1, 0, n - 1, it.first, 0);
				delta.upd(1, 0, n - 1, it.first, 0);
			}
		}
		for(auto it : queries[tme]) {
			ans[it.second] = getAns(tme + 1, it.first.second) - getAns(tme + 1, it.first.first - 1);
		}
	}
	
	for(ll i = 0; i < q; i ++) {
		cout << ans[i] << endl;
	}
	return 0;
	
}

