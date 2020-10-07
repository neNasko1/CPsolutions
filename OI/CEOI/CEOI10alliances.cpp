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

struct Edge {
    int to, flow, cap;
    Edge(int a, int b, int c) {
        to = a;
        flow = b;
        cap = c;
    }
    Edge() {}
};

const int MAX_CONST = 5000;
const int MAX_N = 3 * MAX_CONST + 10;
vector<int> g[MAX_N];
vector<Edge> edges;
int s = MAX_N - 2, t = MAX_N - 1;
int ind[MAX_N];

void add(int a, int b, int cap) {
    //cout << a << " " << b << " " << cap << endl;
    g[a].push_back(edges.size());
    edges.push_back({b, 0, cap});
    g[b].push_back(edges.size());
    edges.push_back({a, 0, 0});
}

int level[MAX_N];
bool bfs() {
    fill_n(level, MAX_N, mod);
    fill_n(ind, MAX_N, 0);
    queue<int> q;
    q.push(s);
    level[s] = 0;
    while(!q.empty()) {
        int curr = q.front(); q.pop();
        for(auto it : g[curr]) {
            if(edges[it].cap > edges[it].flow && level[edges[it].to] > level[curr]) {
                level[edges[it].to] = level[curr] + 1;
                q.push(edges[it].to);
            }
        }
    }
    return level[t] != mod;
}

int dfs(int x, int pushed) {
    if(x == t || pushed == 0) {return pushed;}
    while(ind[x] < g[x].size()) {
        int curr = g[x][ind[x]]; ind[x] ++;
        if(level[edges[curr].to] != level[x] + 1) {continue;}
        int now = dfs(edges[curr].to, min(pushed, edges[curr].cap - edges[curr].flow));
        if(now == 0) {continue;}
        edges[curr].flow += now;
        edges[curr ^ 1].flow -= now;
        return now;
    }
    return 0;
}

int flow() {
    int ret = 0;
    while(bfs()) {
        int f;
        while(f = dfs(s, mod)) {
            ret += f;
        }
    }
    return ret;
}

int tab[80][80];

int n, m;
int encode1(int x, int y) {
    return x * m + y;
}

int encode2(int x, int y) {
    if(x % 2 == 0 && y % 2 == 0) {
        return 1;
    } else if(x % 2 == 0) {
        return 2;
    } else if(y % 2 == 0) {
        return 4;
    } else {
        return 3;
    }
}

void generate(int x, int y) {
    int code1 = encode1(x, y);
    int code2 = encode2(x, y);
    if(tab[x][y] == 0) {return;}
    if(code2 & 1) {
        add(s, code1, tab[x][y]);
    } else {
        add(code1, t, tab[x][y]);
    }
    ll bCap = (tab[x][y] == 2) ? 1 : 2;
    if(code2 & 1) {
        if(x > 0) {
            add(code1 + encode2(x - 1, y) / 2 * MAX_CONST, encode1(x - 1, y) + (code2 + 1) / 2 * MAX_CONST, 1);
        }
        if(y > 0) {
            add(code1 + encode2(x, y - 1) / 2 * MAX_CONST, encode1(x, y - 1) + (code2 + 1) / 2 * MAX_CONST, 1);
        }
        if(x < n - 1) {
            add(code1 + encode2(x + 1, y) / 2 * MAX_CONST, encode1(x + 1, y) + (code2 + 1) / 2 * MAX_CONST, 1);
        }
        if(y < m - 1) {
            add(code1 + encode2(x, y + 1) / 2 * MAX_CONST, encode1(x, y + 1) + (code2 + 1) / 2 * MAX_CONST, 1);
        }
        add(code1, code1 + MAX_CONST, bCap);
        add(code1, code1 + 2 * MAX_CONST, bCap);
    } else {
        add(code1 + MAX_CONST, code1, bCap);
        add(code1 + 2 * MAX_CONST, code1, bCap);
    }
}

vector<int> conn[MAX_N];
bool pos[80][80][4];
string ans[240];

void print(int on, int i) {
    if(on == 1) {
        ans[i] += 'X';
    } else if(on == 0) {
        ans[i] += '.';
    } else {
        ans[i] += 'O';
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n >> m;
    int cnt = 0, cnt1 = 0;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            cin >> tab[i][j];
            if((i + j) % 2 == 0) {cnt += tab[i][j];} else {cnt1 += tab[i][j];}
        }
    }
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            generate(i, j);
        }
    }
    if(cnt1 != cnt || flow() != cnt) {
        cout << "Impossible!" << endl;
        return 0;
    }
    ll cnt3 = 0;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            int ind = encode1(i, j);
            for(auto it : g[ind + MAX_CONST]) {
                if(edges[it].flow == 1 && edges[it].cap > 0) {
                    int x = (edges[it].to % MAX_CONST) / m, y = (edges[it].to % MAX_CONST) % m;
                    if(x == i + 1) {
                        pos[i][j][2] = true;
                        pos[x][y][0] = true;
                    } else if(x == i - 1) {
                        pos[i][j][0] = true;
                        pos[x][y][2] = true;
                    } else if(y == j + 1) {
                        pos[i][j][1] = true;
                        pos[x][y][3] = true;
                    } else if(y == j - 1) {
                        pos[i][j][3] = true;
                        pos[x][y][1] = true;
                    }
                    cnt3 ++;
                }
            }
            for(auto it : g[ind + 2 * MAX_CONST]) {
                if(edges[it].flow == 1 && edges[it].cap > 0) {
                    int x = (edges[it].to % MAX_CONST) / m, y = (edges[it].to % MAX_CONST) % m;
                    if(x == i + 1) {
                        pos[i][j][2] = true;
                        pos[x][y][0] = true;
                    } else if(x == i - 1) {
                        pos[i][j][0] = true;
                        pos[x][y][2] = true;
                    } else if(y == j + 1) {
                        pos[i][j][1] = true;
                        pos[x][y][3] = true;
                    } else if(y == j - 1) {
                        pos[i][j][3] = true;
                        pos[x][y][1] = true;
                    }
                    cnt3 ++;
                }
            }
        }
    }
    int cnt2 = 0;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            ll nowRet = pos[i][j][0] + pos[i][j][1] + pos[i][j][2] + pos[i][j][3];
            cnt2 += nowRet;
            print(0, i * 3);
            print(pos[i][j][0], i * 3);
            print(0, i * 3);
            print(pos[i][j][3], i * 3 + 1);
            if(tab[i][j] == 0) {
                print(0, i * 3 + 1);
            } else {
                print(2, i * 3 + 1);
            }
            print(pos[i][j][1], i * 3 + 1);
            print(0, i * 3 + 2);
            print(pos[i][j][2], i * 3 + 2);
            print(0, i * 3 + 2);
        }
    }
    for(int i = 0; i < 3 * n; i ++) {
        cout << ans[i] << endl;
    }
    return 0;
}

