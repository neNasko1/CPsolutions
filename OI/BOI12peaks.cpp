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
const ll mod = 1e9 + 7;
template<class T> inline void fix(T &x) {if(x >= mod | x <= -mod) {x %= mod;} if(x < 0) {x += mod;}}
#define out(x) cout << __LINE__ << ": " << (#x) << " = " << (x) << endl

///Parallel binary search, where the eval(x(flat area label)) function finds out if there is label > x in the component of x, using the edges which connect 2 vertices with value > m(mid value in binary search);
///Cancer implementation

const int MAX_N = 1 << 20;
vector<int> tab[MAX_N];
vector<int> col[MAX_N];
int tme = 0;
int tmeCol[MAX_N];
int par[MAX_N], mx[MAX_N], sz[MAX_N], n, m;

vector<pair<int, int> > edges[MAX_N];

bool peak[MAX_N];

int dx[] = {0, 0, 1, -1, -1, 1, -1, 1};
int dy[] = {1, -1, 0, 0, -1, -1, 1, 1};

bool ok(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < m;
}

bool bfs(int x, int y) {
    tme ++;
    tmeCol[tme] = tab[x][y];
    col[x][y] = tme;
    queue<pair<int, int> > q;
    q.push({x, y});
    bool flag = true;
    while(!q.empty()) {
        auto curr = q.front(); q.pop();
        for(int i = 0; i < 8; i ++) if(ok(curr.first + dx[i], curr.second + dy[i])) {
            if(tab[curr.first + dx[i]][curr.second + dy[i]] == tab[curr.first][curr.second] && col[curr.first + dx[i]][curr.second + dy[i]] == -1) {
                q.push({curr.first + dx[i], curr.second + dy[i]});
                col[curr.first + dx[i]][curr.second + dy[i]] = tme;
            } else if(tab[curr.first + dx[i]][curr.second + dy[i]] > tab[curr.first][curr.second]) {
                flag = false;
            }
        }
    }
    return flag;
}

void makeEdges() {
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            for(int k = 0; k < 8; k ++) if(ok(i + dx[k], j + dy[k])) {
                if(tab[i + dx[k]][j + dy[k]] < tab[i][j]) {
                    edges[tab[i + dx[k]][j + dy[k]]].push_back({col[i][j], col[i + dx[k]][j + dy[k]]});
                }
            }
        }
    }
}

int find(int x) {
    if(par[x] == x) {return x;}
    return par[x] = find(par[x]);
}

void merge(int x, int y) {
    x = find(x); y = find(y);
    if(x == y) {return;}
    if(sz[x] < sz[y]) {swap(x, y);}
    par[y] = x;
    sz[x] += sz[y];
    chkmax(mx[x], mx[y]);
}

void init() {
    for(int i = 0; i < MAX_N; i ++) {
        par[i] = i;
        mx[i] = tmeCol[i];
        sz[i] = 1;
    }
}

void add(int ind) {
    for(auto &it : edges[ind]) {
        merge(it.first, it.second);
    }
}

bool eval(int ind) {
    return tmeCol[ind] < mx[find(ind)];
}

vector<pair<int, int> > ret;
vector<int> toAns[MAX_N], nxt[MAX_N];

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    int MX = 0;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            int a;
            cin >> a;
            tab[i].push_back(a);
            col[i].push_back(-1);
            chkmax(MX, a);
        }
    }
    ll big = MAX_N, sr = MAX_N / 2;

    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            if(col[i][j] == -1) {
                if(bfs(i, j)) {
                    toAns[sr].push_back(tme);
                }
            }
        }
    }

    for(int i = 0; i < MAX_N; i ++) {
        sort(edges[i].begin(), edges[i].end());
        edges[i].resize(unique(edges[i].begin(), edges[i].end()) - edges[i].begin());
    }

    makeEdges();
    while(big > 1) {
        bool flag = false;
        init();
        for(ll i = MAX_N - 1; i >= 0; i --) {
            add(i);
            ll lb = i - (big / 2), rb = i + (big / 2);
            for(auto it : toAns[i]) {
                if(eval(it)) {
                    nxt[(i + rb) / 2].push_back(it);
                } else {
                    nxt[(i + lb) / 2].push_back(it);
                }
            }
        }
        for(ll i = 0; i < MAX_N; i ++) {
            toAns[i] = nxt[i];
            nxt[i].resize(0);
        }
        big /= 2;
    }

    for(int i = 0; i < MAX_N; i ++) {
        for(auto it : toAns[i]) {
            ret.push_back({tmeCol[it], i});
        }
    }
    sort(ret.begin(), ret.end());
    reverse(ret.begin(), ret.end());
    cout << ret.size() << endl;
    for(auto it : ret) {
        cout << it.first << " " << it.second << endl;
    }
    return 0;
}


