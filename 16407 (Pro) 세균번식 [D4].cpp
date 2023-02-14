#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100

int n, a, b;
int dish[105][105];
int field[105][105];

struct Candidate {
    int i;
    int j;

    bool operator<(const Candidate& other) const {
        return make_pair(dish[i][j], make_pair(-i, -j))
            < make_pair(dish[other.i][other.j], make_pair(-other.i, -other.j));
    }
};

void incCountTarget(int target) {
    if (target == 1) {
        a++;
    }
    else {
        b++;
    }
}

void decCountTarget(int target) {
    if (target == 1) {
        a--;
    }
    else {
        b--;
    }
}

int getCountTarget(int target) {
    if (target == 1) {
        return a;
    }
    else {
        return b;
    }
}

void init(int N, int mDish[MAX_N][MAX_N]) {
    n = N;
    a = 0;
    b = 0;
    memset(dish, 0, sizeof(dish));
    memset(field, 0, sizeof(field));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dish[i][j] = mDish[i - 1][j - 1];
        }
    }
}

int dropMedicine(int mTarget, int mRow, int mCol, int mEnergy) {
    if (field[mRow][mCol] && field[mRow][mCol] != mTarget) {
        return getCountTarget(mTarget);
    }

    if (!field[mRow][mCol]) {
        field[mRow][mCol] = mTarget;
        mEnergy = max(0, mEnergy - dish[mRow][mCol]);
        incCountTarget(mTarget);
    }

    pair<int, int> dxs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool visited[105][105] = {0};
    bool pqVisited[105][105] = {0};

    queue<pair<int, int>> q;
    priority_queue<Candidate> pq;

    q.push({mRow, mCol});
    visited[mRow][mCol] = true;

    while (mEnergy) {
        while (!q.empty()) {
            pair<int, int> node = q.front();
            q.pop();

            for (pair<int, int> dx : dxs) {
                if (!dish[node.first + dx.first][node.second + dx.second]) {
                    continue;
                }

                if (!visited[node.first + dx.first][node.second + dx.second]) {
                    if (field[node.first + dx.first][node.second + dx.second] == mTarget) {
                        q.push({node.first + dx.first, node.second + dx.second});
                        visited[node.first + dx.first][node.second + dx.second] = true;
                    }
                }

                if (!pqVisited[node.first + dx.first][node.second + dx.second]) {
                    if (!field[node.first + dx.first][node.second + dx.second]) {
                        Candidate candidate;
                        candidate.i = node.first + dx.first;
                        candidate.j = node.second + dx.second;

                        pq.push(candidate);
                        pqVisited[node.first + dx.first][node.second + dx.second] = true;
                    }
                }
            }
        }

        if (pq.empty()) {
            break;
        }

        Candidate pick = pq.top();
        pq.pop();

        field[pick.i][pick.j] = mTarget;
        mEnergy = max(0, mEnergy - dish[pick.i][pick.j]);
        incCountTarget(mTarget);

        q.push({pick.i, pick.j});
        visited[pick.i][pick.j] = true;
    }

    return getCountTarget(mTarget);
}

int cleanBacteria(int mRow, int mCol) {
    if (!field[mRow][mCol]) {
        return -1;
    }

    pair<int, int> dxs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int target = field[mRow][mCol];
    queue<pair<int, int>> q;

    q.push({mRow, mCol});
    field[mRow][mCol] = 0;
    decCountTarget(target);

    while (!q.empty()) {
        pair<int, int> node = q.front();
        q.pop();

        for (pair<int, int> dx : dxs) {
            if (!dish[node.first + dx.first][node.second + dx.second]) {
                continue;
            }

            if (field[node.first + dx.first][node.second + dx.second] == target) {
                q.push({node.first + dx.first, node.second + dx.second});
                field[node.first + dx.first][node.second + dx.second] = 0;
                decCountTarget(target);
            }
        }
    }

    return getCountTarget(target);
}
