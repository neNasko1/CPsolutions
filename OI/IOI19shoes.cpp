#include "shoes.h"
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

///We greedily scan from left to right. WLOG let this shoe be a left one. We get the closest unmatched right shoe and we move it next to the current. We use a segment tree to see how many shoes are still between them.

const ll MAX_N = 5e5 + 10;
ll tree[4 * MAX_N], lazy[4 * MAX_N];

void upd(ll curr, ll l, ll r, ll ind, ll val) {
    if(ind < l || r < ind) {
        return;
    } else if(l == ind && ind == r) {
        tree[curr] += val;
        return;
    }
    ll m = (l + r) / 2ll;
    upd(curr * 2, l, m, ind, val);
    upd(curr * 2 + 1, m + 1, r, ind, val);
    tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
}

ll sum(ll curr, ll l, ll r, ll ql, ll qr) {
    if(ql <= l && r <= qr) {
        return tree[curr];
    } else if(l > qr || r < ql) {
        return 0;
    }
    ll m = (l + r) / 2ll;
    return sum(curr * 2, l, m, ql, qr) + sum(curr * 2 + 1, m + 1, r, ql, qr);
}

map<ll, vector<ll> > mp;
bool got[MAX_N];

ll count_swaps(vector<int> arr) {
    for(ll i = 0; i < arr.size(); i ++) {
        mp[arr[i]].push_back(i);
    }
    for(auto &it : mp) {
        reverse(it.second.begin(), it.second.end());
    }
    ll ret = 0;
    for(ll i = 0; i < arr.size(); i ++) {
        if(got[i]) {continue;}
        if(arr[i] > 0) {ret ++;}
        got[i] = true;
        got[mp[-arr[i]].back()] = true;
        ret += (mp[-arr[i]].back() - i - 1) - sum(1, 0, MAX_N - 1, i, mp[-arr[i]].back());
        upd(1, 0, MAX_N - 1, mp[-arr[i]].back(), 1);
        mp[arr[i]].pop_back();
        mp[-arr[i]].pop_back();
    }
    return ret;
}
/*
signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll n;
    cin >> n;
    vector<ll> arr;
    arr.resize(n);
    for(ll i = 0; i < n; i ++) {
        cin >> arr[i];
    }
    cout << shoes(arr);
    return 0;
}*/
