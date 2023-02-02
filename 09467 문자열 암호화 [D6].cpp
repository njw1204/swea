#include <bits/stdc++.h>
#define ALL(c) (c).begin(),(c).end()
using namespace std;

int N;
char X[50005];
int hashOfPos[50005];
list<int> posOfHash[20000];
list<int>::iterator itOfPos[50005];

inline int myHash(char str[], int start, int len) {
    int val = 0;

    for (int i = 0; i < len; i++) {
        val *= 26;
        val += str[start + i] - 'a';
    }

    return val;
}

void init(int n, char init_string[]) {
    N = n;

    for (int i = 0; i < n; i++) {
        X[i] = init_string[i];
    }

    X[n] = '\0';

    for (int i = 0; i < 20000; i++) {
        posOfHash[i].clear();
;    }

    for (int i = 0; i < n - 2; i++) {
        int theHash = myHash(X, i, 3);
        hashOfPos[i] = theHash;
        posOfHash[theHash].push_back(i);
        itOfPos[i] = --posOfHash[theHash].end();
    }
}

int change(char string_A[], char string_B[]) {
    int base = 26 * 26;
    int cnt = 0;
    int fromHash = myHash(string_A, 0, 3);
    int lastIdx = -99;

    for (auto it = posOfHash[fromHash].begin(); it != posOfHash[fromHash].end();) {
        int val = *it;

        if (val - lastIdx < 3) {
            it++;
            continue;
        }

        for (int i = val; i < val + 3; i++) {
            X[i] = string_B[i - val];
        }

        int theHash = -1;

        for (int i = val - 2; i <= val + 2; i++) {
            if (i < 0 || i > N - 3) {
                continue;
            }

            if (theHash == -1) {
                theHash = myHash(X, i, 3);
            }
            else {
                theHash = (theHash - base * (X[i - 1] - 'a')) * 26 + X[i + 2] - 'a';
            }

            if (theHash != hashOfPos[i]) {
                if (hashOfPos[i] == fromHash && it == itOfPos[i]) {
                    it = posOfHash[hashOfPos[i]].erase(itOfPos[i]);
                }
                else {
                    posOfHash[hashOfPos[i]].erase(itOfPos[i]);
                }

                hashOfPos[i] = theHash;
                auto mit = lower_bound(ALL(posOfHash[theHash]), i);
                itOfPos[i] = posOfHash[theHash].insert(mit, i);
            }
        }

        cnt++;
        lastIdx = val;
    }

    return cnt;
}

void result(char ret[]) {
    strcpy(ret, X);
}
