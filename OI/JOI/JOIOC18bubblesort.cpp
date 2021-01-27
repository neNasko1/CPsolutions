#include "bubblesort2.h"
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
 
struct Node {
	int val, lazy, cnt;
	Node() {val = lazy = cnt = 0;}
	Node operator +(const Node &other) const {
		Node ret;
		ret.val = max(val, other.val);
		ret.cnt = cnt + other.cnt;
		if(ret.cnt == 0) {
			ret.val = 0;
		}
		return ret;
	}
};
 
struct SegTree {
	Node tree[4 * MAX_N];
	void push(int curr, int l, int r) {
		tree[curr].val += tree[curr].lazy;
		if(tree[curr].cnt == 0) {
			tree[curr].val = 0;
		}
		if(l != r) {
			tree[curr * 2].lazy += tree[curr].lazy;
			tree[curr * 2 + 1].lazy += tree[curr].lazy;
		}
		tree[curr].lazy = 0;
	}
	void updPos(int curr, int l, int r, int ind, int val) {
		push(curr, l, r);
		if(l == r && l == ind) {
			tree[curr].cnt += val;
			if(tree[curr].cnt == 0) {
				tree[curr].val = 0;
			}
			return;
		} else if(l > ind || r < ind) {
			return;
		}
		int m = (l + r) / 2ll;
		updPos(curr * 2, l, m, ind, val);
		updPos(curr * 2 + 1, m + 1, r, ind, val);
		tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
	}
	void upd(int curr, int l, int r, int ql, int qr, int val) {
		push(curr, l, r);
		if(ql <= l && r <= qr) {
			tree[curr].lazy += val;
			push(curr, l, r);
			return;
		} else if(l > qr || r < ql) {
			return;
		}
		int m = (l + r) / 2ll;
		upd(curr * 2, l, m, ql, qr, val);
		upd(curr * 2 + 1, m + 1, r, ql, qr, val);
		tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
	}	
	int ansPos(int curr, int l, int r, int ql, int qr) {
		push(curr, l, r);
		if(ql <= l && r <= qr) {
			return tree[curr].cnt;
		} else if(l > qr || r < ql) {
			return 0;
		}
		int m = (l + r) / 2ll;
		return ansPos(curr * 2, l, m, ql, qr) + ansPos(curr * 2 + 1, m + 1, r, ql, qr);		
	}
	int ans(int curr, int l, int r, int ql, int qr) {
		push(curr, l, r);
		if(ql <= l && r <= qr) {
			return tree[curr].val;
		} else if(l > qr || r < ql) {
			return 0;
		}
		int m = (l + r) / 2ll;
		return max(ans(curr * 2, l, m, ql, qr), ans(curr * 2 + 1, m + 1, r, ql, qr));
	}
};
 
SegTree ans;
 
vector<int> countScans(vector<int> A, vector<int> X, vector<int> V){
	int Q = X.size(), N = A.size();
	vector<int> answer(Q);
	vector<pair<int, int> > cord;
	for(int i = 0; i < N; i ++) {
		cord.push_back({A[i], i});
	}
	for(int i = 0; i < Q; i ++) {
		cord.push_back({V[i], X[i]});
	}
	sort(cord.begin(), cord.end());
	cord.resize(unique(cord.begin(), cord.end()) - cord.begin());
	for(int i = 0; i < N; i ++) {
		A[i] = lower_bound(cord.begin(), cord.end(), make_pair(A[i], i)) - cord.begin() + 1;
	}
	for(int i = 0; i < Q; i ++) {
		V[i] = lower_bound(cord.begin(), cord.end(), make_pair(V[i], X[i])) - cord.begin() + 1;
	}
	for(int i = 0; i < N; i ++) {
		ans.updPos(1, 0, MAX_N - 1, A[i], 1);
	}
	for(int i = 0; i < N; i ++) {
		int smaller = ans.ansPos(1, 0, MAX_N - 1, 0, A[i] - 1);
		ans.upd(1, 0, MAX_N - 1, A[i], A[i], i - smaller);
	}
 
	for(int i = 0; i < Q; i ++) {
		ans.updPos(1, 0, MAX_N - 1, A[X[i]], -1);
		ans.upd(1, 0, MAX_N - 1, A[X[i]] + 1, MAX_N - 1, 1);
 
		A[X[i]] = V[i];
		ans.updPos(1, 0, MAX_N - 1, A[X[i]], 1);
 
		int smaller = ans.ansPos(1, 0, MAX_N - 1, 0, V[i] - 1);
		ans.upd(1, 0, MAX_N - 1, V[i], V[i], X[i] - smaller);
		ans.upd(1, 0, MAX_N - 1, V[i] + 1, MAX_N - 1, -1);
		
		answer[i] = ans.ans(1, 0, MAX_N - 1, 0, MAX_N - 1);
	}
	return answer;
}