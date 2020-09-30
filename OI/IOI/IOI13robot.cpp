#include "robots.h"

#include <bits/stdc++.h>
using namespace std;

///Binary search on the answer - eval function is a greedy.

const int MAX_N = 1e6 + 10;
int n, m, t;
int small[MAX_N], weak[MAX_N];
pair<int, int> toy[MAX_N];

bool eval(int x) {
    int cnt = -1;
    priority_queue<int> pq;
    for(int i = 0; i < n; i ++) {
        while(cnt + 1 < t && toy[cnt + 1].first < weak[i]) {
            pq.push(toy[cnt + 1].second);
            cnt ++;
        }
        int cpy = x;
        while(!pq.empty() && cpy > 0) {
            cpy --;
            pq.pop();
        }
    }
    while(cnt + 1 < t) {
        pq.push(toy[cnt + 1].second);
        cnt ++;
    }
    for(int i = m - 1; i >= 0; i --) {
        if(pq.empty()) {return true;}
        int cpy = x;
        while(!pq.empty() && cpy > 0) {
            if(pq.top() >= small[i]) {return false;}
            cpy --;
            pq.pop();
        }
    }
    return pq.empty();
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
    n = A;
    m = B;
    t = T;
    for(int i = 0; i < n; i ++) {
        weak[i] = X[i];
    }
    for(int i = 0; i < m; i ++) {
        small[i] = Y[i];
    }
    sort(small, small + m);
    sort(weak, weak + n);
    for(int i = 0; i < t; i ++) {
        toy[i] = {W[i], S[i]};
    }
    sort(toy, toy + t);
    int l = 0, r = t;
    while(l < r - 1) {
        int mid = (l + r) / 2ll;
        if(eval(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    if(eval(r)) {
        return r;
    } else {
        return -1;
    }
}
