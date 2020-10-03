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

///Greedy solution - we use the height with the least number of flags; We can use a  modified segment tree to perform updates;

const ll MAX_N = 1e5 + 20;

struct Node {
    ll sum, mx, mn, lazy;
    Node() {sum = mx = mn = lazy = 0;}
};

Node tree[4 * MAX_N];

void push(ll curr, ll l, ll r) {
    tree[curr].sum += tree[curr].lazy * (r - l + 1);
    tree[curr].mx += tree[curr].lazy;
    tree[curr].mn += tree[curr].lazy;
    if(l != r) {
        tree[curr * 2].lazy += tree[curr].lazy;
        tree[curr * 2 + 1].lazy += tree[curr].lazy;
    }
    tree[curr].lazy = 0;
}

Node operator +(const Node &a, const Node &b) {
    Node ret;
    ret.sum = a.sum + b.sum;
    ret.mx = max(a.mx, b.mx);
    ret.mn = min(a.mn, b.mn);
    return ret;
}

ll nowoff;

void upd(ll curr, ll l, ll r, ll ql, ll qr, ll val) {
    push(curr, l, r);
    if(ql <= l && r <= qr) {
        tree[curr].lazy += val;
        push(curr, l, r);
        return;
    } else if(l > qr || r < ql) {return;}
    ll m = (l + r) / 2ll;
    upd(curr * 2, l, m, ql, qr, val);
    upd(curr * 2 + 1, m + 1, r, ql, qr, val);
    tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
}

ll sum(ll curr, ll l, ll r, ll ql, ll qr) {
    push(curr, l, r);
    if(ql <= l && r <= qr) {
        return tree[curr].sum;
    } else if(l > qr || r < ql) {return 0;}
    ll m = (l + r) / 2ll;
    return sum(curr * 2, l, m, ql, qr) + sum(curr * 2 + 1, m + 1, r, ql, qr);
}

ll firstEqual(ll curr, ll l, ll r, ll val) {
    push(curr, l, r);
    if(l == r) {
        return r;
    }
    ll m = (l + r) / 2ll;
    push(curr * 2, l, m);
    push(curr * 2 + 1, m + 1, r);
    if(tree[curr * 2].mx >= val) {
        return firstEqual(curr * 2, l, m, val);
    } else {
        return firstEqual(curr * 2 + 1, m + 1, r, val);
    }
}

pair<ll, ll> arr[MAX_N];
ll n;
ll offset = 1e5 + 10;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(ll i = 0; i < n; i ++) {
        cin >> arr[i].first >> arr[i].second;
    }
    sort(arr, arr + n);
    ll ret = 0;
    upd(1, 0, MAX_N - 1, 0, MAX_N - 1, -mod);
    upd(1, 0, MAX_N - 1, offset, MAX_N - 1, 2 * mod);
    int last = offset;
    for(ll i = 0; i < n; i ++) {
        nowoff = offset - arr[i].first;
        while(last > nowoff) {
            last --;
            upd(1, 0, MAX_N - 1, last, last, mod);
        }
        ll now = sum(1, 0, MAX_N - 1, nowoff + arr[i].second - 1, nowoff + arr[i].second - 1);

        ll l = firstEqual(1, 0, MAX_N - 1, now), r = firstEqual(1, 0, MAX_N - 1, now + 1) - 1;
        ll toChange = nowoff + arr[i].second - l;

        upd(1, 0, MAX_N - 1, nowoff, l - 1, 1);
        upd(1, 0, MAX_N - 1, r - toChange + 1, r, 1);
        //continue;
        if(i == n - 1) {
            for(int j = nowoff; j < offset; j ++) {
                ll nnow = sum(1, 0, MAX_N - 1, j, j);
                ret += (nnow * nnow - nnow) / 2ll;
            }
        }

    }
    cout << ret << endl;
    return 0;
}
