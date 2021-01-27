#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#define endl "\n"
typedef long long ll;
template<class T, class T2> inline ostream &operator <<(ostream &out, const pair<T, T2> &x) { out << x.first << " " << x.second; return out;}
template<class T, class T2> inline istream &operator >>(istream &in, pair<T, T2> &x) { in >> x.first >> x.second; return in;}
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;
#define out(x) "{" << (#x) << ": " << x << "} "

const int MAX_N = 1010;
string s[MAX_N];
set<int> st[MAX_N][MAX_N];
int n, m;

int dx[4] = {-1, -1, 0, 1};
int dy[4] = {1, -1, 1, 0};
string ch = "";
string col = "PWG";

bool valid(int x, int y, int dind) {
	for(int scale = -1; scale < 2; scale ++) {
		int nowx = x + dx[dind] * scale;
		int nowy = y + dy[dind] * scale;
		if(nowx < 0 || nowy < 0 || nowx >= n || nowy >= m) {return false;}
		if(s[nowx][nowy] != col[scale + 1]) {break;}
		if(scale == 1) {
			return true;
		}
	}
	for(int scale = -1; scale < 2; scale ++) {
		int nowx = x + dx[dind] * scale;
		int nowy = y + dy[dind] * scale;
		if(nowx < 0 || nowy < 0 || nowx >= n || nowy >= m) {return false;}
		if(s[nowx][nowy] != col[1 - scale]) {break;}
		if(scale == 1) {
			return true;
		}
	}
	return false;
}

vector<pair<pair<int, int>, int> > good;
bool got[MAX_N * MAX_N];
char ans[MAX_N][MAX_N];

int blocking(int ind) {
	int x = good[ind].first.first, y = good[ind].first.second, dind = good[ind].second;
	set<int> stNow;
	for(int scale = -1; scale < 2; scale ++) {
		int nowx = x + dx[dind] * scale;
		int nowy = y + dy[dind] * scale;
		if(st[nowx][nowy].size() > 1) {return -1;}
		if(!st[nowx][nowy].empty()) {
			stNow.insert(*st[nowx][nowy].begin());
		}
	}
	if(stNow.size() > 1) {
		return -1;
	} else if(stNow.empty()) {
		return -2;
	} else {
		return *stNow.begin();
	}
}

void apply(int ind, int add) {
	got[ind] = add;
	int x = good[ind].first.first, y = good[ind].first.second, dind = good[ind].second;
	for(int scale = -1; scale < 2; scale ++) {
		int nowx = x + dx[dind] * scale;
		int nowy = y + dy[dind] * scale;
		if(add) {
			st[nowx][nowy].insert(ind);
		} else {
			st[nowx][nowy].erase(ind);
		}
	}
}

vector<int> ind;

signed main() {
	//ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	srand(clock());
	ch += '/';
	ch += '\\';
	ch += '-';
	ch += '|';
	cin >> n >> m;
	for(int i = 0; i < n; i ++) {
		cin >> s[i];
	}
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			for(int k = 0; k < 4; k ++) {
				if(valid(i, j, k)) {
					good.push_back({{i, j}, k});
					ind.push_back(good.size() - 1);
				}
			}
		}
	}
	const int MAX_ITER = 200000, MAX_SHUFFLE = 10000, SHUFFLE_RESET = 10000, SHUFFLE_COUNT = 7500;
	const int TARGET = 51390, TIME_LIMIT = 60000;
	int ret = 0;
	while(clock() < 180000) {
		int iter = MAX_ITER;
		int score = 0, nxt = 0;
		int shuffled = 0;
		random_shuffle(ind.begin(), ind.end());
		while(clock() < 180000 && iter) {
			iter --;
			if(iter <= SHUFFLE_RESET && iter % SHUFFLE_COUNT == 0) {random_shuffle(ind.begin(), ind.end()); shuffled ++; iter = SHUFFLE_RESET;}
			int rnd = ind[nxt % ind.size()]; nxt = (nxt + 1) % ind.size();
 			int now = blocking(rnd);
			if(now == -1) {continue;}
			if(now != -2) {apply(now, 0);} else {score ++; iter = MAX_ITER; shuffled = max(0, shuffled - 100); iter = (iter + SHUFFLE_COUNT - 1) / SHUFFLE_COUNT * SHUFFLE_COUNT;}
			apply(rnd, 1);
		}
		for(int i = 0; i < ind.size(); i ++) {
            int now = blocking(ind[i]);
            if(now == -2) {
                apply(ind[i], 1);
                score ++;
            }
		}
		if(score <= ret) {
            for(int i = 0; i < good.size(); i ++) {
                if(!got[i]) {continue;}
                apply(i, 0);
            }
            continue;
		}
		ret = score;
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < m; j ++) {
				ans[i][j] = s[i][j];
			}
		}
		for(int i = 0; i < good.size(); i ++) {
			if(!got[i]) {continue;}
			ans[good[i].first.first][good[i].first.second] = ch[good[i].second];
			apply(i, 0);
		}
	}
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < m; j ++) {
			cout << ans[i][j];
		}
		cout << endl;
	}
	return 0;
}

