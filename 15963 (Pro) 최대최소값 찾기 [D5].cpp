#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE 200000

int n;
int a[200005];
int seg[800005][3];

void initSeg(int node, int start, int end) {
    if (start == end) {
        seg[node][0] = (a[start] != -1) ? a[start] : INT_MAX;
        seg[node][1] = (a[start] != -1) ? a[start] : INT_MIN;
        seg[node][2] = (a[start] != -1);
        return;
    }

    initSeg(node * 2, start, (start + end) / 2);
    initSeg(node * 2 + 1, (start + end) / 2 + 1, end);
    seg[node][0] = min(seg[node * 2][0], seg[node * 2 + 1][0]);
    seg[node][1] = max(seg[node * 2][1], seg[node * 2 + 1][1]);
    seg[node][2] = seg[node * 2][2] + seg[node * 2 + 1][2];
}

void updateSeg(int idx, int val, int node, int start, int end) {
    if (start > idx || end < idx) {
        return;
    }

    if (start == end) {
        a[idx] = val;
        seg[node][0] = (a[idx] != -1) ? a[idx] : INT_MAX;
        seg[node][1] = (a[idx] != -1) ? a[idx] : INT_MIN;
        seg[node][2] = (a[idx] != -1);
        return;
    }

    updateSeg(idx, val, node * 2, start, (start + end) / 2);
    updateSeg(idx, val, node * 2 + 1, (start + end) / 2 + 1, end);
    seg[node][0] = min(seg[node * 2][0], seg[node * 2 + 1][0]);
    seg[node][1] = max(seg[node * 2][1], seg[node * 2 + 1][1]);
    seg[node][2] = seg[node * 2][2] + seg[node * 2 + 1][2];
}

void querySeg(int queryLeft, int queryRight, int queryResult[], int node, int start, int end) {
    if (end < queryLeft || start > queryRight) {
        queryResult[0] = INT_MAX;
        queryResult[1] = INT_MIN;
        queryResult[2] = 0;
        return;
    }

    if (start >= queryLeft && end <= queryRight) {
        queryResult[0] = seg[node][0];
        queryResult[1] = seg[node][1];
        queryResult[2] = seg[node][2];
        return;
    }

    int queryResults[2][3];
    querySeg(queryLeft, queryRight, queryResults[0], node * 2, start, (start + end) / 2);
    querySeg(queryLeft, queryRight, queryResults[1], node * 2 + 1, (start + end) / 2 + 1, end);
    queryResult[0] = min(queryResults[0][0], queryResults[1][0]);
    queryResult[1] = max(queryResults[0][1], queryResults[1][1]);
    queryResult[2] = queryResults[0][2] + queryResults[1][2];
}

void init(int N, int mValue[]) {
    n = N;
    memset(a, -1, sizeof(a));

    for (int i = 0; i < N; i++) {
        a[i] = mValue[i];
    }

    initSeg(1, 0, MAX_SIZE);
}

void add(int M, int mValue[]) {
    for (int i = 0; i < M; i++) {
        updateSeg(n++, mValue[i], 1, 0, MAX_SIZE);
    }
}

void erase(int mFrom, int mTo) {
    int left = 0, right = n - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        int queryResult[3];
        querySeg(0, mid, queryResult, 1, 0, MAX_SIZE);

        if (queryResult[2] >= mFrom) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    int x = left;

    left = 0, right = n - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        int queryResult[3];
        querySeg(0, mid, queryResult, 1, 0, MAX_SIZE);

        if (queryResult[2] >= mTo) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }

    int y = left;

    for (int i = x; i <= y; i++) {
        if (a[i] == -1) {
            continue;
        }

        updateSeg(i, -1, 1, 0, MAX_SIZE);
    }
}

int find(int K) {
    int left = 0, right = n - 1;

    while (left < right) {
        int mid = (left + right) / 2;
        int queryResult[3];
        querySeg(mid, n - 1, queryResult, 1, 0, MAX_SIZE);

        if (queryResult[2] > K) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    int queryResult[3];
    querySeg(left, n - 1, queryResult, 1, 0, MAX_SIZE);
    return queryResult[1] - queryResult[0];
}
