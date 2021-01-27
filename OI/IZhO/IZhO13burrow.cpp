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
const ll mod = 1e9 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "

const ll MAX_N = 1e3 + 10;
ll tab[MAX_N][MAX_N];
ll k;
ll n, m;
ll howm[MAX_N][MAX_N];
ll l[MAX_N], r[MAX_N];

ll eval(ll x) {
    for(ll j = 0; j < m; j ++) {
        howm[0][j] = tab[0][j] >= x;
    }
    for(ll i = 1; i < n; i ++) {
        for(ll j = 0; j < m; j ++) {
            if(tab[i][j] >= x) {
                howm[i][j] = howm[i - 1][j] + 1;
            } else {
                howm[i][j] = 0;
            }
        }
    }
    ll mx = 0;
    for(ll i = 0; i < n; i ++) {
        stack<ll> st;
        for(ll j = 0; j < m; j ++) {
            while(!st.empty() && howm[i][st.top()] >= howm[i][j]) {
                st.pop();
            }
            if(st.empty()) {
                l[j] = 0;
            } else {
                l[j] = st.top() + 1;
            }
            st.push(j);
        }
        while(!st.empty()) {st.pop();}
        for(ll j = m - 1; j >= 0; j --) {
            while(!st.empty() && howm[i][st.top()] >= howm[i][j]) {
                st.pop();
            }
            if(st.empty()) {
                r[j] = m - 1;
            } else {
                r[j] = st.top() - 1;
            }
            st.push(j);
        }
        while(!st.empty()) {st.pop();}
        for(ll j = 0; j < m; j ++) {
            chkmax(mx, howm[i][j] * (r[j] - l[j] + 1));
        }
    }
    return mx;
}

signed main() {
    //ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m >> k;
    for(ll i = 0; i < n; i ++) {
        for(ll j = 0; j < m; j ++) {
            cin >> tab[i][j];
        }
    }
    ll l = 0, r = mod;
    while(l < r - 1) {
        ll m = (l + r) / 2ll;
        if(eval(m) >= k) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << " " << eval(l) << endl;
    return 0;
}

