#include <bits/stdc++.h>
using namespace std;
#define $1 first
#define $2 second

vector<pair<int, int>> articles;
int articlesIdx[100005];
bool following[1005][1005];
int timestamps[100005];
int articleUid[100005];

void init(int N) {
    memset(timestamps, 0, sizeof(timestamps));
    memset(following, 0, sizeof(following));

    for (int i = 0; i <= N; i++) {
        articles.clear();
        following[i][i] = true;
    }
}

void follow(int uID1, int uID2, int timestamp) {
    following[uID1][uID2] = true;
}

void makePost(int uID, int pID, int timestamp) {
    articleUid[pID] = uID;
    articlesIdx[pID] = articles.size();
    articles.push_back({0, -timestamp});
    timestamps[timestamp] = pID;
}

void like(int pID, int timestamp) {
    articles[articlesIdx[pID]].$1--;
}

void getFeed(int uID, int timestamp, int pIDList[]) {
    priority_queue<pair<int, int>> candidates;

    for (int i = articles.size() - 1; i >= 0; i--) {
        pair<int, int> node = articles[i];
        int pID = timestamps[-node.$2];
        int other = articleUid[pID];

        if (!following[uID][other]) {
            continue;
        }

        int writeTimestamp = -node.$2;

        if (timestamp - writeTimestamp > 1000) {
            node.$1 = 1;

            if (candidates.size() == 10) {
                break;
            }
        }

        candidates.push(node);

        if (candidates.size() > 10) {
            candidates.pop();
        }
    }

    for (int i = min(9, (int)candidates.size() - 1); i >= 0; i--) {
        pIDList[i] = timestamps[-candidates.top().$2];
        candidates.pop();
    }
}
