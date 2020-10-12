//#include "aliens.h"
#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
typedef long double ld;
template<class T, class T2> inline ostream &operator <<(ostream &out, const pair<T, T2> &x) { out << x.first << " " << x.second; return out;}
template<class T, class T2> inline istream &operator >>(istream &in, pair<T, T2> &x) { in >> x.first >> x.second; return in;}
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e12 + 7, MAX_CORD = 1e6 + 10;
const ld eps = 1e-2;
#define out(x) "{" << (#x) << ": " << x << "} "

struct Line {
    ld a, b;
    ll delta;
    ld y(ld x) {return x * a + b;}
    Line(ld _a, ld _b, ll _delta) {a = _a; b = _b; delta = _delta;}
    Line() {a = 0; b = mod; delta = 0;}
};
struct Node {
    Line val;
    Node *l, *r;
    Node() {l = nullptr; r = nullptr;}
    ld y(ld x) {return val.y(x);}
    void expand() {
        if(!l) {l = new Node(); r = new Node();}
    }
};
struct LiChao {
    Node root;
    void add(Line nw, Node *curr, ll l = 0, ll r = MAX_CORD) {
        while(true) {
            ll m = (l + r) / 2;
            bool a = nw.y(l) < curr->y(l);
            bool b = nw.y(m) < curr->y(m);
            if(b) {swap(curr->val, nw);}
            if(r - l == 1) {
                return;
            }
            curr->expand();
            if(a != b) {
                curr = curr->l;
                r = m;
            } else {
                curr = curr->r;
                l = m;
            }
        }
    }
    Line get(ll x, Node *curr) {
        ll l = 0, r = MAX_CORD;
        Line ret = Line();
        while(curr != nullptr) {
            ll m = (l + r) / 2;
            if(curr->y(x) < ret.y(x)) {
                ret = curr->val;
            }
            if(r - l == 1) {
                return ret;
            }
            if(x < m) {
                curr = curr->l;
                r = m;
            } else {
                curr = curr->r;
                l = m;
            }
        }
        return ret;
    }
    void clear() {
        root = Node();
    }
};

const ll MAX_N = 1e5 + 10;
ll n, m, k;
vector<pair<ll, ll> > points;
ld dp[MAX_N];
ll delta[MAX_N];
LiChao tree;

ll toSqr(ll x) {
    return x * x;
}

ll calculate(ld del) {
    tree.clear();
    dp[0] = delta[0] = 0;
    tree.add(Line(-2ll * points[1].second, points[1].second * points[1].second + del, 0), &(tree.root));
    for(ll i = 1; i < points.size(); i ++) {
        auto best = tree.get(points[i].first, &(tree.root));
        dp[i] = best.y(points[i].first) + points[i].first * points[i].first;
        delta[i] = best.delta + 1;
        if(i != points.size() - 1) {
            tree.add(Line(-2ll * points[i + 1].second, dp[i] - toSqr(max(points[i].first - points[i + 1].second, 0ll)) + toSqr(points[i + 1].second) + del, delta[i]), &(tree.root));
        }
    }
    return delta[points.size() - 1];
}


long long take_photos(int N, int M, int K, std::vector<int> r, std::vector<int> c) {
    n = N; m = M; k = K;
    for(ll i = 0; i < n; i ++) {
        if(r[i] < c[i]) {
            points.push_back({c[i], -r[i]});
        } else {
            points.push_back({r[i], -c[i]});
        }
    }
    sort(points.begin(), points.end());
    vector<pair<ll, ll> > cpy;
    ll mn = mod;
    for(ll i = n - 1; i >= 0; i --) {
        if(-points[i].second < mn) {
            mn = -points[i].second;
            cpy.push_back({points[i].first + 1, -points[i].second});
        }
    }
    k = min(k, (ll)cpy.size());
    cpy.push_back({0, 0});
    points = cpy;
    reverse(points.begin(), points.end());
    ld lft = -mod, rght = mod;

    for(int iter = 0; iter < 50; iter ++) {
        ld m = (lft + rght) / 2.;
        if(calculate(m) > k) {
            lft = m;
        } else {
            rght = m;
        }
    }
    calculate(rght);
    return round(dp[cpy.size() - 1] - (ld) max(k, delta[cpy.size() - 1]) * rght);
}
