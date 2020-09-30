#include "wall.h"

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
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const ll MAX_N = 2e6 + 10;

struct Node {
    ll mn, mx, lazy;
    Node(ll a) {
        mn = mx = a;
        lazy = -1;
    }
    Node() {
        mn = mod;
        mx = -1;
        lazy = -1;
    }
};

Node operator +(const Node &a, const Node &b) {
    Node ret;
    ret.mn = min(a.mn, b.mn);
    ret.mx = max(a.mx, b.mx);
    return ret;
}

Node tree[4 * MAX_N];

void push(ll curr, ll l, ll r) {
    if(tree[curr].lazy == -1) {return;}
    tree[curr].mn = tree[curr].mx = tree[curr].lazy;
    if(l != r) {
        tree[curr * 2].lazy = tree[curr].lazy;
        tree[curr * 2 + 1].lazy = tree[curr].lazy;
    }
    tree[curr].lazy = -1;
}

void updAdding(ll curr, ll l, ll r, ll ql, ll qr, ll k) {
    push(curr, l, r);
    if(ql <= l && r <= qr && tree[curr].mx <= k) {
        tree[curr].lazy = k;
        push(curr, l, r);
        return;
    } else if(l > qr || r < ql || tree[curr].mn >= k) {return;}
    ll m = (l + r) / 2ll;
    updAdding(curr * 2, l, m, ql, qr, k);
    updAdding(curr * 2 + 1, m + 1, r, ql, qr, k);
    tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
}

void updRemoving(ll curr, ll l, ll r, ll ql, ll qr, ll k) {
    push(curr, l, r);
    if(ql <= l && r <= qr && tree[curr].mn >= k) {
        tree[curr].lazy = k;
        push(curr, l, r);
        return;
    } else if(l > qr || r < ql || tree[curr].mx <= k) {return;}
    ll m = (l + r) / 2ll;
    updRemoving(curr * 2, l, m, ql, qr, k);
    updRemoving(curr * 2 + 1, m + 1, r, ql, qr, k);
    tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
}

int ret[MAX_N], tme = 0;

void pushAll(ll curr, ll l, ll r) {
    push(curr, l, r);
    if(l == r) {
        ret[tme ++] = tree[curr].mn;
        return;
    }
    ll m = (l + r) / 2ll;
    pushAll(curr * 2, l, m);
    pushAll(curr * 2 + 1, m + 1, r);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
    tree[1].lazy = 0;
    for(ll i = 0; i < k; i ++) {
        if(op[i] == 1) {
            updAdding(1, 0, n - 1, left[i], right[i], height[i]);
        } else {
            updRemoving(1, 0, n - 1, left[i], right[i], height[i]);
        }
    }
    pushAll(1, 0, n - 1);
    for(int i = 0; i < n; i ++) {
        finalHeight[i] = ret[i];
    }
    return;
}


