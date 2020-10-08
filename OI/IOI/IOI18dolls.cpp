#include "doll.h"

#include <vector>

void create_circuit(int M, std::vector<int> A);

void answer(std::vector<int> C, std::vector<int> X, std::vector<int> Y);

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

const int WRONG_ID = -16969420, ROOT_ID = WRONG_ID + 1;
vector<int> arr;
vector<int> x, y;

pair<int, int> buildTree(int l, int r) {
    if(l == r) {
        return {arr[l], arr[l] != WRONG_ID};
    }
    int m = (l + r) / 2ll;
    auto lftSon = buildTree(l, m);
    auto rghtSon = buildTree(m + 1, r);

    if(lftSon.second + rghtSon.second == 0) {
        return {WRONG_ID, 0};
    } else {
        x.push_back(lftSon.first);
        y.push_back(rghtSon.first);
        return {-x.size(), lftSon.second + rghtSon.second};
    }
}

int bitInverse(int ind, int pow2) {
    int ret = 0;
    for(int i = 0; i < pow2; i ++) {
        if(ind & (1 << i)) {
            ret |= (1 << (pow2 - 1 - i));
        }
    }
    return ret;
}

void create_circuit(int M, std::vector<int> A) {
    arr = A;
    arr.push_back(0);
    int pow2 = 0, big = 1, small;
    while((1 << pow2) < arr.size()) {pow2 ++;}
    while(big <= arr.size()) {big *= 2;} big /= 2;
    small = arr.size() - big;

    while(arr.size() < (1 << pow2)) {
        arr.push_back(WRONG_ID);
    }
    vector<pair<int, int> > pairs;
    for(int i = 0; i < big; i ++) {
        int inv = bitInverse(i, pow2);
        pairs.push_back({inv, -1});
    }
    for(int i = arr.size() - small; i < arr.size(); i ++) {
        int inv = bitInverse(i, pow2);
        pairs.push_back({inv, -1});
    }
    sort(pairs.begin(), pairs.end());
    for(int i = 0; i < pairs.size(); i ++) {
        pairs[i].second = arr[i];
    }
    for(auto &it : arr) {it = WRONG_ID;}
    for(int i = 0; i < pairs.size(); i ++) {
        arr[bitInverse(pairs[i].first, pow2)] = pairs[i].second;
    }
    pow2 = 1 << pow2;
    int root = buildTree(0, pow2 - 1).first;
    vector<int> ptr;
    for(int i = 0; i <= M; i ++) {
        ptr.push_back(root);
    }
    for(int i = 0; i < x.size(); i ++) {
        if(x[i] == WRONG_ID) {
            x[i] = root;
        }
        if(y[i] == WRONG_ID) {
            y[i] = root;
        }
    }
    answer(ptr, x, y);
}
