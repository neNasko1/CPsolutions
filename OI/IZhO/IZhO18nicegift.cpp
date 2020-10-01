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
const ll mod = 1e18 + 7;
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    vector<vector<ll> > ans;
    ll n, k;
    cin >> n >> k;
    priority_queue<pair<ll, ll> > pq;
    ll avr = 0;
    for(ll i = 0; i < n; i ++) {
        ll a;
        cin >> a;
        avr += a;
        if(a != 0) {
            pq.push({a, i});
        }
    }
    if(avr % k != 0) {
        cout << -1 << endl;
        return 0;
    }
    while(pq.size() >= k) {
        vector<pair<ll, ll> > curr;
        ll get = mod;
        for(ll i = 0; i < k; i ++) {
            chkmin(get, pq.top().first);
            curr.push_back(pq.top()); pq.pop();
        }
        if(!pq.empty()) {
            chkmin(get, avr / k - pq.top().first);
        }
        ans.resize(ans.size() + 1);
        ans.back().push_back(get);
        avr -= k * get;
        for(auto &it : curr) {
            ans.back().push_back(it.second + 1);
            it.first -= get;
            if(it.first > 0) {
                pq.push({it});
            }
        }
    }
    if(pq.size() != 0) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans.size() << endl;
    for(auto it : ans) {
        for(auto itt : it) {
            cout << itt << " ";
        }
        cout << endl;
    }
    return 0;
}


