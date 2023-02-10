#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000

int total;
vector<int> disk[3];
vector<pair<int, int>> all;

void init(int N[3], int mDisk[3][MAX_N]) {
    total = N[0] + N[1] + N[2];
    all.clear();

    for (int i = 0; i < 3; i++) {
        disk[i].clear();

        for (int j = N[i] - 1; j >= 0; j--) {
            disk[i].push_back(mDisk[i][j]);
            all.push_back({mDisk[i][j], i});
        }
    }

    sort(all.begin(), all.end(), greater<>());
}

void destroy() {
}

int stop = 0;

void dfs(int n, int to) {
    for (int i = n; i < all.size(); i++) {
        if (stop == 0) {
            return;
        }

        if (all[i].second == to) {
            continue;
        }

        int cur = all[i].second;
        int mid = 3 - cur - to;

        dfs(i + 1, mid);

        if (stop == 0) {
            return;
        }

        all[i].second = to;
        disk[to].push_back(disk[cur].back());
        disk[cur].pop_back();
        stop--;

        dfs(i + 1, to);
        break;
    }
}

void go(int k, int mTop[3]) {
    stop = k;
    dfs(0, 2);

    mTop[0] = disk[0].empty() ? 0 : disk[0].back();
    mTop[1] = disk[1].empty() ? 0 : disk[1].back();
    mTop[2] = disk[2].empty() ? 0 : disk[2].back();
}
