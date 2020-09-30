#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
template<class T, class T2> bool chkmax(T &a, const T2 &b) {return (a < b) ? a = b, 1 : 0;}

const int mod = 1e9 + 7;
const int MAX_N = 1e6 + 10;

struct Node {
	int ans, lazy;
	Node() : ans(0), lazy(0) {}
};

Node tree[4 * MAX_N];

Node operator +(const Node &a, const Node &b) {
	Node ret;
	ret.ans = max(a.ans, b.ans);
	ret.lazy = 0;
	return ret;
}

void push(int curr, int l, int r) {
	chkmax(tree[curr].ans, tree[curr].lazy);
	if(l != r) {
		chkmax(tree[curr * 2].lazy, tree[curr].lazy);
		chkmax(tree[curr * 2 + 1].lazy, tree[curr].lazy);
	}
	tree[curr].lazy = 0;
}

void update(int curr, int l, int r, int ql, int qr, int val) {
	push(curr, l, r);
	if(ql <= l && r <= qr) {
		chkmax(tree[curr].lazy, val);
		push(curr, l, r);
		return;
	} else if(l > qr || r < ql) {
		return;
	}
	int m = (l + r) / 2ll;
	update(curr * 2, l, m, ql, qr, val);
	update(curr * 2 + 1, m + 1, r, ql, qr, val);
	tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
}

int ans(int curr, int l, int r, int ql, int qr) {
	push(curr, l, r);
	if(ql <= l && r <= qr) {
		return tree[curr].ans;
	} else if(l > qr || r < ql) {
		return 0;
	}
	int m = (l + r) / 2ll;
	return max(ans(curr * 2, l, m, ql, qr), ans(curr * 2 + 1, m + 1, r, ql, qr));
}

int l[MAX_N], k[MAX_N];
vector<int> query[MAX_N];
bool ret[MAX_N];
int arr[MAX_N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int n, q;
	cin >> n;
	cin >> q;
	for(int i = 0; i < n; i ++) {
		cin >> arr[i];
	}
	for(int i = 0; i < q; i ++) {
		int r;
		cin >> l[i] >> r >> k[i];
		query[r - 1].push_back(i);
		l[i] --;
	}
	stack<int> st;
	for(int i = 0; i < n; i ++) {
		while(!st.empty() && arr[st.top()] <= arr[i]) {
			st.pop();
		}
		if(!st.empty()) {
			update(1, 0, n - 1, 0, st.top(), arr[st.top()] + arr[i]);
		}
		st.push(i);
		for(auto it : query[i]) {
			ret[it] = ans(1, 0, n - 1, l[it], i) <= k[it];
		}
	}
	for(int i = 0; i < q; i ++) {
		cout << ret[i] << endl;
	}
}

