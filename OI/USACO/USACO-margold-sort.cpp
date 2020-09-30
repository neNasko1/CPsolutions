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

const int MAX_N = 1e5 + 10;

///For every index index we need to find out how many elements, that are currently on its right, have to go on its left

struct SegTree {
    int tree[4 * MAX_N], lazy[4 * MAX_N];

    void build(int curr, int l, int r, int (&arr)[MAX_N]) {
        if(l == r) {
            tree[curr] = arr[l]; lazy[curr] = 0;
            return;
        }
        int m = (l + r) / 2;
        build(curr * 2, l, m, arr);
        build(curr * 2 + 1, m + 1, r, arr);
        tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
        lazy[curr] = 0;
    }

    void push(int curr, int l, int r) {
        tree[curr] += lazy[curr] * (r - l + 1);
        if(l != r) {
            lazy[curr * 2] += lazy[curr]; lazy[curr * 2 + 1] += lazy[curr];
        }
        lazy[curr] = 0;
    }

    void upd(int curr, int l, int r, int ql, int qr, int val) {
        push(curr, l, r);
        if(ql <= l && r <= qr) {
            lazy[curr] += val;
            push(curr, l, r);
            return;
        } else if(l > qr || r < ql) {return;}
        int m = (l + r) / 2;
        upd(curr * 2, l, m, ql, qr, val);
        upd(curr * 2 + 1, m + 1, r, ql, qr, val);
        tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
    }

    int query(int curr, int l, int r, int ql, int qr) {
        push(curr, l, r);
        if(ql <= l && r <= qr) {
            return tree[curr];
        } else if(l > qr || r < ql) {return 0;}
        int m = (l + r) / 2;
        return query(curr * 2, l, m, ql, qr) + query(curr * 2 + 1, m + 1, r, ql, qr);
    }
};

int arr[MAX_N];
pair<int, int> val[MAX_N];

SegTree st;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;
    cin >> n;
    vector<int> p;
    for(int i = 0; i < n; i ++) {
        cin >> val[i].first; val[i].second = i;
    }
    sort(val, val + n);
    for(int i = 0; i < n; i ++) {
        arr[i] = st.query(1, 0, n, i, n);
        st.upd(1, 0, n, val[i].second, val[i].second, 1);
    }
    int ans = 0;
    for(int i = n - 1; i >= 0; i --) {
        chkmax(ans, arr[i]);
    }
    cout << ans << endl;
    return 0;
}


