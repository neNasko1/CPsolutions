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

///We need to get n - k distances between guests - we use a priority_queue for the greedy.

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll last = -1;
    ll n, k;
    cin >> n >> k;
    if(n == 1) {
        cout << 1 << endl;
        return 0;
    }
    ll total = n;
    priority_queue<ll> pq;
    for(ll i = 0; i < n; i ++) {
        ll t;
        //cout << "Input";
        cin >> t;
        if(i != 0) {
            pq.push(last - t + 1);
        }
        last = t;
    }
    //cout << "!!" << last << " " << total << " " << total + last + 1 << endl;
    while(n - k > 0 && !pq.empty()) {
        //cout << "Wtf" << pq.top() << endl;
        total -= pq.top();
        pq.pop();
        k ++;
    }
    cout << total << endl;
    return 0;
}


