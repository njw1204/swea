#include <bits/stdc++.h>
using namespace std;

struct Node {
    int score = 0;
    int parent = 0;
    int height = 0;
};

int n;
Node tree[100005];

void init(int N) {
    n = N;
    memset(tree, 0, sizeof(Node) * (n + 1));
}

void updateScore(int mWinnerID, int mLoserID, int mScore) {
    int pA = mWinnerID, pB = mLoserID;

    while (tree[pA].parent) {
        pA = tree[pA].parent;
    }

    while (tree[pB].parent) {
        pB = tree[pB].parent;
    }

    tree[pA].score += mScore;
    tree[pB].score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB) {
    int pA = mPlayerA, pB = mPlayerB;

    while (tree[pA].parent) {
        pA = tree[pA].parent;
    }

    while (tree[pB].parent) {
        pB = tree[pB].parent;
    }

    if (tree[pA].height < tree[pB].height) {
        tree[pA].parent = pB;
        tree[pA].score -= tree[pB].score;
    }
    else if (tree[pA].height > tree[pB].height) {
        tree[pB].parent = pA;
        tree[pB].score -= tree[pA].score;
    }
    else {
        tree[pB].parent = pA;
        tree[pB].score -= tree[pA].score;
        tree[pA].height++;
    }
}

int getScore(int mID) {
    int ans = tree[mID].score;
    int pA = mID;

    while (tree[pA].parent) {
        pA = tree[pA].parent;
        ans += tree[pA].score;
    }

    return ans;
}
