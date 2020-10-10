#include "vision.h"
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

const int MAX_N = 4e2 + 10;

pair<int, int> diag1[MAX_N], diag2[MAX_N];
int got1[MAX_N], got2[MAX_N];
vector<int> elements1[MAX_N], elements2[MAX_N];
int w, h;

int encode(int x, int y) {
    return x * w + y;
}

int generateDiagonals(int k) {
    for(int i = 0; i < MAX_N; i ++) {
        elements1[i].resize(0);
        elements2[i].resize(0);
    }
    for(int i = 0; i < h; i ++) {
        for(int j = 0; j < w; j ++) {
            elements1[i + j].push_back(encode(i, j));
            elements2[i - j + w - 1].push_back(encode(i, j));
        }
    }
    vector<int> finish, diag1, diag2, pref1, pref2;
    for(int i = 0; i < h + w - 1; i ++) {
        diag1.push_back(add_or(elements1[i]));
        diag2.push_back(add_or(elements2[i]));
        pref1.push_back(add_or(diag1));
        pref2.push_back(add_or(diag2));
        if(i >= k) {
            finish.push_back(add_and({diag1[i], pref1[i - k]}));
            finish.push_back(add_and({diag2[i], pref2[i - k]}));
        }
    }
    return add_or(finish);

}

void construct_network(int H, int W, int K) {
    h = H; w = W;
    if(h + w - 2 == K) {
        add_xor({generateDiagonals(K)});
    } else {
        add_xor({generateDiagonals(K), generateDiagonals(K + 1)});
    }
}
