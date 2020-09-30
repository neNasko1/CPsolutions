#include "combo.h"

///With 2 queries we find the first element, then with n - 2 queries we find [1, n - 1], the last element is special, because we cant ask 4*n+4 element query, so we need to do something different.

#include <bits/stdc++.h>
using namespace std;

string let = "ABXY";
string pos[2100];

string guess_sequence(int n) {
    char first;
    string ans = "";
    string ask1;
    ask1.push_back(let[0]);
    ask1.push_back(let[1]);
    if(press(ask1) != 0) {
        string ask2; ask2.push_back(let[0]);
        if(press(ask2) != 0) {
            first = let[0];
        } else {
            first = let[1];
        }
    } else {
        string ask2; ask2.push_back(let[2]);
        if(press(ask2) != 0) {
            first = let[2];
        } else {
            first = let[3];
        }
    }
    string nwLet = "";
    for(auto it : let) {
        if(it != first) {
            nwLet.push_back(it);
        }
    }
    let = nwLet;
    ans = first;
    for(int i = 1; i < n - 1; i ++) {
        string ask2 = "";
        ask2 += ans;
        ask2.push_back(let[0]);
        ask2.push_back(let[0]);
        ask2 += ans;
        ask2.push_back(let[0]);
        ask2.push_back(let[1]);
        ask2 += ans;
        ask2.push_back(let[0]);
        ask2.push_back(let[2]);
        ask2 += ans;
        ask2.push_back(let[1]);
        int curr = press(ask2);
        if(curr == i) {
            ans += let[2];
        } else if(curr == i + 1) {
            ans += let[1];
        } else {
            ans += let[0];
        }
    }
    if(n == 1) {
        return ans;
    }
    string ask3 = "";
    ask3 += ans;
    ask3.push_back(let[0]);
    ask3 += ans;
    ask3.push_back(let[1]);
    if(press(ask3) == n) {
        ask3 = ans;
        ask3.push_back(let[0]);
        if(press(ask3) == n) {
            ans.push_back(let[0]);
        } else {
            ans.push_back(let[1]);
        }
    } else {
        ans.push_back(let[2]);
    }
    return ans;
}
