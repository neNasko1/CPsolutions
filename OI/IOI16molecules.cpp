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

///We can use two-pointer approach. We can prove that it will find the answer, because if sum(l, r) < d and sum(l, r + 1) > u, then using the condition maxa - mina <= u - d: d <= sum(l + 1, r + 1) <= u

#include "molecules.h"

std::vector<int> find_subset(ll d, ll u, std::vector<int> nt) {
    vector<pair<ll, int> > w;
    for(int i = 0; i < nt.size(); i ++) {
        w.push_back({nt[i], i});
    }
    sort(w.begin(), w.end());
    ll sum = 0, l = 0;
    for(int r = 0; r < w.size(); r ++) {
        sum += (ll)w[r].first;
        while(sum > u) {
            sum -= (ll)w[l].first;
            l ++;
        }
        if(d <= sum && sum <= u) {
            vector<int> ret;
            for(int i = l; i <= r; i ++) {
                ret.push_back(w[i].second);
            }
            return ret;
        }
    }
    return std::vector<int>(0);
}

