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
const ll mod = 1e7 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

///If we use simple greedy we can form suboptimal solution :
///This happens when we set a school(a, b) to a music one and school(c, d) to a sport one. Then the simple greedy which picks a(a > b) and d(d > c) fails when b - a > d - c
///So we calculate prefix music answer and suffix sport answer.

const ll MAX_N = 3e5 + 10;
bool used[MAX_N];
pair<ll, pair<ll, ll> > toSrt[MAX_N];

struct HeapSum {
    ll sum = 0, limit = -1;
    priority_queue<ll> pq;
    HeapSum() {}
    HeapSum(ll _limit) : limit(_limit) {}
    void push(ll x) {
        pq.push(-x);
        sum += x;
        if(pq.size() > limit) {
            sum += pq.top();
            pq.pop();
        }
    }
    ll ans() {
        if(pq.size() != limit) {
            return -mod * mod;
        } else {
            return sum;
        }
    }
};

ll pref[MAX_N], suf[MAX_N];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll n, m, s;
    cin >> n >> m >> s;
    for(ll i = 0; i < n; i ++) {
        ll a, b;
        cin >> a >> b;
        toSrt[i] = {b - a, {a, b}};
    }
    sort(toSrt, toSrt + n);
    HeapSum music(m), sport(s);
    pref[0] = -mod * mod;
    if(m == 0) {pref[0] = 0;}
    for(ll i = 0; i < n; i ++) {
        music.push(toSrt[i].second.first);
        pref[i + 1] = music.ans();
    }
    ll ret = 0;
    suf[n] = -mod * mod;
    if(s == 0) {suf[n] = 0;}
    for(ll i = n - 1; i >= 0; i --) {
        sport.push(toSrt[i].second.second);
        suf[i] = sport.ans();
    }
    for(ll i = 0; i <= n; i ++) {
        chkmax(ret, pref[i] +  suf[i]);
    }
    cout << ret << endl;
    return 0;
}


