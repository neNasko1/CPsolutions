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
const ll mod = 1e15 + 7;
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

const ll MAX_N = 1e5 + 110, MAX_LOG = 20;

struct Lca {
    vector<pair<int, ll> > g[MAX_N];
    ll par[MAX_N][MAX_LOG], mx[MAX_N][MAX_LOG], d[MAX_N];

    void add(int a, int b, ll c) {
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    void pre(int x, int p, ll w) {//Initialize lca with pre(root, 0, 0);
        par[x][0] = p;
        mx[x][0] = w;
        d[x] = d[p] + 1;
        for(int i = 1; i < MAX_LOG; i ++) {
            par[x][i] = par[par[x][i - 1]][i - 1];
            mx[x][i] = min(mx[par[x][i - 1]][i - 1], mx[x][i - 1]);
        }
        for(auto it : g[x]) {
            if(it.first == p) {continue;}
            pre(it.first, x, it.second);
        }
    }

    ll ans(int a, int b) {
        if(d[a] < d[b]) {swap(a, b);}
        ll ret = mod;
        for(int i = MAX_LOG - 1; i >= 0; i --) {
            if(d[a] >= d[b] + (1 << i)) {
                chkmin(ret, mx[a][i]);
                a = par[a][i];
            }
        }
        if(a == b) {return ret;}
        for(int i = MAX_LOG - 1; i >= 0; i --) {
            if(par[a][i] != par[b][i]) {
                chkmin(ret, min(mx[a][i], mx[b][i]));
                a = par[a][i];
                b = par[b][i];
            }
        }
        return min({ret, mx[a][0], mx[b][0]});
    }
};

ll dist[MAX_N];
vector<pair<ll, pair<ll, ll> > > edges;
vector<pair<ll, ll> > g[MAX_N];

void dij(vector<ll> &st) {
    fill_n(dist, MAX_N, mod);
    priority_queue<pair<ll, ll> > pq;
    for(auto it : st) {
        dist[it] = 0;
        pq.push({0, it});
    }
    while(!pq.empty()) {
        auto curr = pq.top(); pq.pop();
        if(-curr.first != dist[curr.second]) {continue;}
        curr.first *= -1;
        for(auto it : g[curr.second]) {
            if(curr.first + it.second < dist[it.first]) {
                dist[it.first] = curr.first + it.second;
                pq.push({-curr.first + -it.second, it.first});
            }
        }
    }
}

ll par[MAX_N], sz[MAX_N];

void init(ll n) {
    for(ll i = 1; i <= n; i ++) {
        par[i] = i;
        sz[i] = 1;
    }
}

ll find(ll x) {
    if(x == par[x]) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

bool merge(ll x, ll y) {
    x = find(x); y = find(y);
    if(x == y) {return false;}
    if(sz[x] < sz[y]) {swap(x, y);}
    assert(sz[x] >= sz[y]);
    par[y] = x;
    sz[x] += sz[y];
    return true;
}

ll ans[MAX_N];
Lca lca;

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    ll n, m;
    cin >> n >> m;
    for(ll i = 0; i < m; i ++) {
        ll a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
        edges.push_back({-1, {a, b}});
    }
    ll k;
    cin >> k;
    vector<ll> st;
    for(ll i = 0; i < k; i ++) {
        ll a;
        cin >> a;
        st.push_back(a);
    }
    dij(st);
    for(auto &it : edges) {
        it.first = min(dist[it.second.first], dist[it.second.second]);
    }
    sort(edges.begin(), edges.end());
    reverse(edges.begin(), edges.end());
    init(n);
    for(auto it : edges) {
        if(merge(it.second.first, it.second.second)) {
            lca.add(it.second.first, it.second.second, it.first);
        }
    }
    lca.pre(1, 0, mod);
    int q;
    cin >> q;
    for(int i = 0; i < q; i ++) {
        int a, b;
        cin >> a >> b;
        cout << lca.ans(a, b) << endl;;
    }
    return 0;
}
