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
const ll mod = 1e16+ 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl
  
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll n;
    cin >> n;
    vector<pair<ll, ll> > arr;
    arr.resize(n);
    for(ll i = 0; i < n; i ++) {
    	cin >> arr[i].first >> arr[i].second;
    }
    sort(arr.begin(), arr.end());
    ll prf = 0, mn = mod, ans = 0;
    for(ll i = 0; i < n; i ++) {
   		chkmin(mn, -arr[i].first + prf);
   		prf += arr[i].second;
   		chkmax(ans, prf - mn - arr[i].first);

    }
    cout << ans << endl;
    return 0;
}