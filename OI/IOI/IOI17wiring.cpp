#include "wiring.h"

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
const ll mod = 1e18 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "

const ll MAX_N = 2e5 + 100;
vector<pair<ll, bool> > arr;
ll pref[MAX_N], balance[MAX_N];
vector<int> r, b;
ll dp[MAX_N];

ll getMin(pair<ll, bool> curr) {
    if(curr.second) {
        auto it = lower_bound(r.begin(), r.end(), curr.first);
        ll ret = mod;
        if(it != r.end()) {chkmin(ret, *it - curr.first);}
        if(it != r.begin()) {it --; chkmin(ret, curr.first - *it);}
        return ret;
    } else {
        auto it = lower_bound(b.begin(), b.end(), curr.first);
        ll ret = mod;
        if(it != b.end()) {chkmin(ret, *it - curr.first);}
        if(it != b.begin()) {it --; chkmin(ret, curr.first - *it);}
        return ret;
    }
}

long long min_total_length(std::vector<int> _r, std::vector<int> _b) {
    r = _r;
    b = _b;
    for(auto it : r) {
        arr.push_back({it, 0});
    }
    for(auto it : b) {
        arr.push_back({it, 1});
    }
    arr.push_back({-mod, 0});
    sort(arr.begin(), arr.end());
    fill_n(balance, MAX_N, -1);
    ll curr = MAX_N / 2;
    balance[curr] = 0;
    for(ll i = 1; i < arr.size(); i ++) {
        if(arr[i].second) {
            pref[i] = pref[i - 1] - arr[i].first;
            curr --;
        } else {
            pref[i] = pref[i - 1] + arr[i].first;
            curr ++;
        }
        dp[i] = dp[i - 1] + getMin(arr[i]);
        if(balance[curr] != -1) {
            chkmin(dp[i], dp[balance[curr]] + abs(pref[i] - pref[balance[curr]]));
        }
        balance[curr] = i;
    }

    return dp[arr.size() - 1];
}
