#include "game.h"

#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 15010;
int N;
int cnt[MAX_N][MAX_N];
int par[MAX_N], sz[MAX_N];

int find(int x) {
    if(x == par[x]) {
        return x;
    } else {
        return par[x] = find(par[x]);
    }
}

void merge(int u, int v) {
    if(sz[u] < sz[v]) {swap(u, v);}
    par[v] = u;
    sz[u] += sz[v];
    for(int i = 0; i < N; i ++) {
        cnt[u][i] += cnt[v][i];
        cnt[i][u] += cnt[i][v];
    }
}

void initialize(int n) {
    N = n;
    for(int i = 0; i < n; i ++) {
        par[i] = i;
        sz[i] = 1;
        for(int j = 0; j < n; j ++) {
            cnt[i][j] ++;
        }
    }
}

int hasEdge(int u, int v) {
    u = find(u); v = find(v);
    if(u == v) {return 0;}
    if(cnt[u][v] == 1) {
        cnt[u][v] --;
        cnt[v][u] --;
        merge(u, v);
        return 1;
    } else {
        cnt[u][v] --;
        cnt[v][u] --;
        return 0;
    }
}

