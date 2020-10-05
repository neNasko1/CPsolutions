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

const int MAX_N = 5e5 + 10, LOG = 20;
int arr[MAX_N], n;
pair<int, int> bords[MAX_N];

struct SparseTable {
    int ans[LOG][MAX_N];
    void construct(int n, int (&arr)[MAX_N]) {
        for(int i = 0; i < n; i ++) {ans[0][i] = arr[i];}
        for(int j = 1; j < LOG; j ++) {
            for(int i = 0; i + (1 << j) <= n; i ++) {
                ans[j][i] = min(ans[j - 1][i], ans[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    int query(int l, int r) {
        int q = 0;
        while((1 << q) <= r - l + 1) {q ++;} q --;
        return min(ans[q][l], ans[q][r - (1 << q) + 1]);
    }
};

SparseTable st;

bool okMin(int l, int r) {
    return r - l + 1 >= st.query(l, r);
}

int good[MAX_N];
int when[MAX_N], delta[MAX_N], dp[MAX_N], pref[MAX_N];

ll sum(int l, int r) {
    if(l == 0) {
        return pref[r];
    } else if(r < l) {
        return 0;
    }
    return (pref[r] - pref[l - 1] + mod) % mod;
}

void upd(int l, int r, int val) {
    if(r < l) {return;}
    delta[l] += val; delta[l] %= mod;
    delta[r + 1] += -val + mod; delta[r + 1] %= mod;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(ll i = 1; i <= n; i ++) {
        cin >> arr[i];
    }
    st.construct(n + 1, arr);
    stack<pair<ll, ll> > st;
    st.push({mod, 0});
    for(ll i = 1; i <= n; i ++) {
        while(st.top().first < arr[i]) {
            st.pop();
        }
        bords[i].first = st.top().second + 1;
        st.push({arr[i], i});
    }
    while(!st.empty()) {st.pop();}
    st.push({mod, n + 1});
    for(ll i = n; i > 0; i --) {
        while(st.top().first <= arr[i]) {
            st.pop();
        }
        bords[i].second = st.top().second - 1;
        st.push({arr[i], i});
    }
    for(ll i = 1; i <= n; i ++) {
        if(!okMin(1, i)) {good[i] = 0; continue;}
        ll l = 1, r = i + 1;
        while(l < r - 1) {
            ll m = (l + r) / 2ll;
            if(okMin(m, i)) {
                l = m;
            } else {
                r = m;
            }
        }
        good[i] = l;
    }

    ll curr = 0;
    good[n + 1] = n + 2;
    for(ll i = 1; i <= n + 1; i ++) {
        while(curr != good[i]) {
            curr ++;
            when[curr] = i;
        }
    }

    dp[0] = 1;
    pref[0] = 1;
    int nowSum = 0;
    for(int i = 1; i <= n; i ++) {
        if(i - bords[i].first < bords[i].second - i) {
            int toAdd = max(bords[i].first, i - arr[i]);
            while(toAdd <= i) {
                int l = max(i, when[toAdd]), r = min(bords[i].second, toAdd + arr[i] - 1);
                upd(l, r, dp[toAdd - 1]);
                toAdd ++;
            }
        } else {
            int toGet = min(bords[i].second, i + arr[i]);
            while(toGet >= i) {
                int l = max(bords[i].first - 1, toGet - arr[i]), r = min(good[toGet] - 1, i - 1);
                ll curr = sum(l, r) % mod;
                upd(toGet, toGet, curr);
                toGet --;
            }
        }
        nowSum = (nowSum + delta[i]) % mod;
        dp[i] = nowSum % mod;
        pref[i] = (dp[i] + pref[i - 1]) % mod;
    }
    cout << dp[n] << endl;


    return 0;
}
