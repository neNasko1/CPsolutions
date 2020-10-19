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
 
const ll MAX_N = 410;
int dpLeft[MAX_N][MAX_N][MAX_N];
int dpRight[MAX_N][MAX_N][MAX_N];
int t[MAX_N], x[MAX_N], n, l;
 
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	for(int i = 0; i < MAX_N; i ++) {
		for(int j = 0; j < MAX_N; j ++) {
			for(int k = 0; k < MAX_N; k ++) {
				dpLeft[i][j][k] = dpRight[i][j][k] = mod;
			}
		}
	}    
	cin >> n >> l;
	for(int i = 0; i < n; i ++) {cin >> x[i]; x[n + i] = x[i] + l;}
	for(int i = 0; i < n; i ++) {cin >> t[i]; t[n + i] = t[i];}
	if(l - x[n - 1] <= t[n - 1]) {
		dpLeft[n - 1][n - 1][1] = dpRight[n - 1][n - 1][1] = l - x[n - 1];
	} else {
		dpLeft[n - 1][n - 1][0] = dpRight[n - 1][n - 1][0] = l - x[n - 1];
	}
	if(x[n] - l <= t[n]) {
		dpLeft[n][n][1] = dpRight[n][n][1] = x[n] - l;
	} else {
		dpLeft[n][n][0] = dpRight[n][n][0] = x[n] - l;		
	}
	for(int len = 1; len <= n; len ++) {
		for(int lft = 0; lft + len - 1 < 2 * n; lft ++) {
			int rght = lft + len - 1;
			///Go from left
			for(int got = 0; got <= n; got ++) {
				if(dpLeft[lft][rght][got] >= mod) {continue;}
				int pos = x[lft];
				if(lft != 0) {
					int need = dpLeft[lft][rght][got] + pos - x[lft - 1];
					bool canGet = need <= t[lft - 1];
					chkmin(dpLeft[lft - 1][rght][got + canGet], need);			
				}
				if(rght != 2 * n - 1) {
					int need = dpLeft[lft][rght][got] + x[rght + 1] - pos;
					bool canGet = need <= t[rght + 1];
					chkmin(dpRight[lft][rght + 1][got + canGet], need);								
				}				
			}			
			
			///Go from right		
			for(int got = 0; got <= n; got ++) {
				if(dpRight[lft][rght][got] >= mod) {continue;}
				int pos = x[rght];
				if(lft != 0) {
					int need = dpRight[lft][rght][got] + pos - x[lft - 1];
					bool canGet = need <= t[lft - 1];
					chkmin(dpLeft[lft - 1][rght][got + canGet], need);			
				}
				if(rght != 2 * n - 1) {
					int need = dpRight[lft][rght][got] + x[rght + 1] - pos;
					bool canGet = need <= t[rght + 1];
					chkmin(dpRight[lft][rght + 1][got + canGet], need);		
				}				
			}			
		}
	}
	int ret = 0;
	for(int i = 0; i <= n; i ++) {
		for(int j = 0; j <= n; j ++) {
			if(min(dpLeft[i][i + n - 1][j], dpRight[i][i + n - 1][j]) < mod) {
				chkmax(ret, j);
			}
		}
	}
	cout << ret << endl;
    return 0;
}