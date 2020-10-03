#include <vector>

#include "messy.h"

#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
template<class T> inline void fix(T &x) {if(labs(x) >= mod) {x %= mod;} if(x < 0) {x += mod;}}

int N;

void addElements(int l, int r) {
    if(l == r) {return;}
    string frst = "", sec = "", thrd = "";
    for(int i = 0; i < l; i ++) {
        frst += "1";
    }
    for(int i = l; i <= r; i ++) {
        sec += "0";
    }
    for(int i = r + 1; i < N; i ++) {
        thrd += "1";
    }
    int m = (l + r) / 2ll;
    for(int i = l; i <= m; i ++) {
        sec[i - l] = '1';
        add_element(frst + sec + thrd);
        sec[i - l] = '0';
    }

    addElements(l, m);
    addElements(m + 1, r);
}
vector<int> ret;

void getElements(int l, int r, string got, vector<int> lft) {
    if(l == r) {
        got[lft.back()] = '1';
        ret[lft.back()] = l;
        return;
    }
    vector<int> a, b;
    int m = (l + r) / 2ll;
    for(auto it : lft) {
        got[it] = '1';
        if(check_element(got)) {
            a.push_back(it);
        } else {
            b.push_back(it);
        }
        got[it] = '0';
    }
    for(auto it : b) {
        got[it] = '1';
    }
    getElements(l, m, got, a);
    for(auto it : b) {
        got[it] = '0';
    }
    for(auto it : a) {
        got[it] = '1';
    }
    getElements(m + 1, r, got, b);

}

std::vector<int> restore_permutation(int n, int w, int r) {
    N = n;
    ret.resize(n);

    addElements(0, n - 1);
    string got; for(int i = 0; i < n; i ++) {got += '0';}
    vector<int> lft; for(int i = 0; i < n; i ++) {lft.push_back(i);}

    compile_set();

    ret.resize(n);
    getElements(0, n - 1, got, lft);
    return ret;
}
