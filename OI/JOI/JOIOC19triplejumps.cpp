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

const int MAX_N = 5e5 + 10;
int arr[MAX_N], n;
vector<pair<int, int> > cand, toAdd[MAX_N], queries[MAX_N];
int ans[MAX_N];

struct Node {
	int val, valFull, lazy;
	Node() {val = valFull = lazy = -mod;}
	Node operator +(const Node &other) const {
		Node ret;
		ret.val = max(val, other.val);
		ret.valFull = max(valFull, other.valFull);
		return ret;
	}
};

struct SegTree {
	Node tree[4 * MAX_N];
	void push(int curr, int l, int r) {
		chkmax(tree[curr].valFull, tree[curr].val + tree[curr].lazy);
		if(l != r) {
			chkmax(tree[curr * 2].lazy, tree[curr].lazy);
			chkmax(tree[curr * 2 + 1].lazy, tree[curr].lazy);
		}
		tree[curr].lazy = -mod;
	}
	void addToRoot(int x) {
		chkmax(tree[1].lazy, x);
	}
	int ans(int curr, int l, int r, int ql, int qr) {
		push(curr, l, r);
		if(ql <= l && r <= qr) {
			return tree[curr].valFull;
		} else if(ql > r || qr < l) {
			return 0;
		}
		int m = (l + r) / 2ll;
		return max(ans(curr * 2, l, m, ql, qr), ans(curr * 2 + 1, m + 1, r, ql, qr));
	}
	void upd(int curr, int l, int r, int ind, int val) {
		push(curr, l, r);
		if(l == r && l == ind) {
			chkmax(tree[curr].val, val);
			return;
		} else if(r < ind || l > ind) {
			return;
		}
		int m = (l + r) / 2ll;
		upd(curr * 2, l, m, ind, val);
		upd(curr * 2 + 1, m + 1, r, ind, val);
		tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
	}
};

SegTree seg;

signed main() {
	//ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n;
	for(int i = 0; i < n; i ++) {
		cin >> arr[i];
	}
	stack<int> st;
	for(int i = 0; i < n; i ++) {
		while(!st.empty() && arr[st.top()] < arr[i]) {
			st.pop();
		}
		if(!st.empty()) {
			cand.push_back({st.top(), i});
		}
		st.push(i);
	}
	while(!st.empty()) {st.pop();}
	for(int i = n - 1; i >= 0; i --) {
		while(!st.empty() && arr[st.top()] < arr[i]) {
			st.pop();
		}
		if(!st.empty()) {
			cand.push_back({i, st.top()});
		}
		st.push(i);
	}
	for(int i = 0; i < n - 1; i ++) {
		cand.push_back({i, i + 1});
	}
	for(auto it : cand) {
		if(it.second * 2 - it.first < n) {
			toAdd[it.second * 2 - it.first].push_back({arr[it.first] + arr[it.second], it.first});		
		}
	}
	
	int q;
	cin >> q;
	for(int i = 0; i < q; i ++) {
		int l, r;
		cin >> l >> r;
		queries[r - 1].push_back({l - 1, i});
	}

	for(int i = 0; i < n; i ++) {
		for(auto it : toAdd[i]) {
			seg.upd(1, 0, n - 1, it.second, it.first);
		}
		seg.addToRoot(arr[i]);
		for(auto it : queries[i]) {
			ans[it.second] = seg.ans(1, 0, n - 1, it.first, i);
		}
	}
	
	for(int i = 0; i < q; i ++) {
		cout << ans[i] << endl;
	}
	return 0;
}

