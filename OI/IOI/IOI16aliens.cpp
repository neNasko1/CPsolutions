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
const ld mod = 1e12 + 7;
const ll MAX_CORD = 1e6 + 10;
const ld eps = 1e-2;
#define out(x) "{" << (#x) << ": " << x << "} "

struct Line {
    ld a, b, delta;
    long double p;
    Line() {}
    Line(ld _a, ld _b, ld _delta) {a = _a; b = _b; delta = _delta;}
    ld y(ld x) {return a * x + b;}
    long double getWhere(const Line &other) {
        if(a == other.a) {
            return -mod;
        } else {
            return (long double)(b - other.b) / (long double)(other.a - a);
        }
    }
};

struct LineContainer {
    deque<Line> lines;
    void addLine(Line curr) {
        while(!lines.empty() && lines.back().getWhere(curr) <= lines.back().p) {
            lines.pop_back();
        }
        if(lines.empty()) {
            curr.p = -mod;
        } else {
            curr.p = lines.back().getWhere(curr);
        }
        lines.push_back(curr);
    }
    pair<ld, int> get(ll x) {
        while(lines.size() > 1 && lines[1].p <= x) {
            lines.pop_front();
        }
        return {lines.front().y(x), lines.front().delta};
    }
    void clear() {
        while(!lines.empty()) {lines.pop_back();}
    }
};

const ll MAX_N = 1e5 + 10;
ll n, m, k;
vector<pair<ll, ll> > points;
ld dp[MAX_N];
ll delta[MAX_N];
LineContainer lc;

ll toSqr(ll x) {
    return x * x;
}

ll calculate(ld del) {
    lc.clear();
    dp[0] = delta[0] = 0;
    lc.addLine(Line(-2ll * points[1].second, points[1].second * points[1].second + del, 0));
    for(ll i = 1; i < points.size(); i ++) {
        auto best = lc.get(points[i].first);
        dp[i] = best.first + points[i].first * points[i].first;
        delta[i] = best.second + 1;
        if(i != points.size() - 1) {
            lc.addLine(Line(-2ll * points[i + 1].second, dp[i] - toSqr(max(points[i].first - points[i + 1].second, 0ll)) + toSqr(points[i + 1].second) + del, delta[i]));
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

    for(int iter = 0; iter < 60; iter ++) {
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
