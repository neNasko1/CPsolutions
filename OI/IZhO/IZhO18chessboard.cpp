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
const ll mod = 1e11 + 7;
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const ll MAX_N = 1e5 + 110;
ll xl[MAX_N], yl[MAX_N], xr[MAX_N], yr[MAX_N];
ll n, k;
ll sz;

ll howm(ll w, ll l, ll r) {
    if(l / sz == r / sz) {
        if(l / sz % 2ll == w) {
            return r - l + 1ll;
        } else {
            return 0;
        }
    }
    ll ret = 0;
    {
        ll nxt = (l + sz) / sz * sz;
        if(l / sz % 2ll == w) {
            ret += nxt - l;
        }
        l = nxt;
    }
    {
        ll nxt = r / sz * sz - 1ll;
        if(r / sz % 2ll == w) {
            ret += r - nxt;
        }
        r = nxt;
    }
    ret += (r / sz - l / sz) / 2ll * sz;
    if(l / sz % 2ll == r / sz % 2ll && l / sz % 2ll == w) {
        ret += sz;
    }
    return ret;
}

ll eval(ll x) {
    sz = x;
    ll badw = 0, goodb = 0;
    ll cnt = (n * n) / (x * x);
    goodb = cnt / 2ll * sz * sz;
    for(ll i = 0; i < k; i ++) {
        ll r0 = howm(0, xl[i], xr[i]);
        ll r1 = howm(1, xl[i], xr[i]);
        ll c0 = howm(0, yl[i], yr[i]);
        ll c1 = howm(1, yl[i], yr[i]);
        badw += r0 * c0 + r1 * c1;
        goodb -= r0 * c1 + r1 * c0;
    }
    return min(badw + goodb, n * n - badw - goodb);
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


    cin >> n >> k;
    ll ans = mod;
    for(ll i = 0; i < k; i ++) {
        cin >> xl[i] >> yl[i] >> xr[i] >> yr[i];
        xl[i] --;
        yl[i] --;
        xr[i] --;
        yr[i] --;
    }
    for(ll x = 1; x < n; x ++) {
        if(n % x != 0) {continue;}
        chkmin(ans, eval(x));
    }
    cout << ans << endl;
    return 0;
}

