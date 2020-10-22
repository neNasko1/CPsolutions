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
 
const ll MAX_N = (1 << 20) + 10;
const ll MAX_RIGHT = 2000000; ll MAX_LEFT = 7;
int pow3[50];
int dp[MAX_RIGHT];
int price[MAX_N];
string queries[MAX_N];
int ans[MAX_N];
int n, q;
char first2[MAX_RIGHT];
int sum[MAX_RIGHT];
int rightPart[MAX_N];
 
void prec() {
	for(ll i = 0; i < q; i ++) {
		ll currMask = 0;
		for(ll j = n - 1; j >= MAX_LEFT; j --) {
			currMask *= 3;
			currMask += (ll)(queries[i][j] - '0');
		}
		rightPart[i] = currMask;
	}
 
	ll triBits = n - MAX_LEFT;
	for(ll i = 0; i < pow3[triBits]; i ++) {
		bool flag = false;
		for(ll j = triBits - 1; j >= 0; j --) {
			if((i / pow3[j]) % 3 == 2) {
				first2[i] = j;
				flag = true;
				break;
			}
		}
		if(!flag) {
			ll currMask = 0;
			for(ll j = triBits - 1; j >= 0; j --) {
				currMask += ((i / pow3[j]) % 3) * (1 << (j + MAX_LEFT));
			}
			sum[i] = currMask;
			first2[i] = -1;
		}
	}
}
 
void getAns(ll mask) {
	vector<ll> indices;
	for(ll i = 0; i < q; i ++) {
		for(ll j = 0; j < MAX_LEFT; j ++) {
			if(mask & (1 << j)) {
				if(queries[i][j] == '0') {
					break;
				}
			} else {
				if(queries[i][j] == '1') {
					break;
				}				
			}
			if(j == MAX_LEFT - 1) {
				indices.push_back(i);
			}
		}
	}
	
	ll triBits = n - MAX_LEFT;
	for(ll i = 0; i < pow3[triBits]; i ++) {
		if(first2[i] != -1) {
			ll j = first2[i];		
			dp[i] = dp[i - pow3[j]] + dp[i - 2 * pow3[j]]; 
		} else {
			ll currMask = mask + sum[i];
			dp[i] = price[currMask];			
		}
	}
	
	for(auto it : indices) {
		ans[it] += dp[rightPart[it]];
	}
}
 
signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	pow3[0] = 1;
	for(ll i = 1; i < 50; i ++) {
		pow3[i] = pow3[i - 1] * 3ll;
	}
	cin >> n >> q;
	chkmin(MAX_LEFT, n);
	string in;
	cin >> in;
	for(ll i = 0; i < (1 << n); i ++) {
		price[i] = in[i] - '0';
	}
	for(ll i = 0; i < q; i ++) {
		cin >> queries[i];
		reverse(queries[i].begin(), queries[i].end());
		for(auto &it : queries[i]) {
			if(it == '?') {
				it = '2';
			}
		}
	}
		
	prec();
	for(ll mask = 0; mask < (1 << MAX_LEFT); mask ++) {
		getAns(mask);
	}
	for(ll i = 0; i < q; i ++) {
		cout << ans[i] << endl;
	}
	return 0;
}