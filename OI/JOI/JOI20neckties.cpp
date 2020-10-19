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
const ll mod = 1e12 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "
 
const ll MAX_N = 2e5 + 10;
pair<ll, ll> a[MAX_N];
ll b[MAX_N];
ll pref[MAX_N], suf[MAX_N];
ll n;
ll ans[MAX_N];
 
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(ll i = 0; i < n + 1; i ++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    for(ll i = 0; i < n; i ++) {
        cin >> b[i];
    }
    sort(a, a + n + 1);
    sort(b, b + n);
    for(ll i = 0; i < n; i ++) {
        pref[i] = max(a[i].first - b[i], 0ll);
        if(i != 0) {
            chkmax(pref[i], pref[i - 1]);
        }
    }
    for(ll i = 0; i < n; i ++) {
        suf[n - i] = max(a[n - i].first - b[n - 1 - i], 0ll);
        chkmax(suf[n - i], suf[n - i + 1]);
    }
    for(ll i = 0; i < n + 1; i ++) {
        if(i != 0) {
            ans[a[i].second] = pref[i - 1];
        }
        chkmax(ans[a[i].second], suf[i + 1]);
    }
    for(ll i = 0; i < n + 1; i ++) {
        cout << ans[i] << " ";
    }
    return 0;
}