#include <bits/stdc++.h>
using namespace std;

struct Result {
    int id;
    int num;
};

int n;
int field[2005][15][15];
int maxComp[2005];
int theaterOf[50005];
vector<pair<int, int>> reservOf[50005];

void refreshMaxComp(int theater) {
    maxComp[theater] = 0;
    bool visited[15][15] = {0};

    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 10; j++) {
            if (visited[i][j] || field[theater][i][j]) {
                continue;
            }

            queue<pair<int, int>> q;
            int curSize = 0;

            q.push({i, j});
            visited[i][j] = true;
            curSize++;

            while (!q.empty()) {
                pair<int, int> node = q.front();
                q.pop();

                pair<int, int> dxs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

                for (const pair<int, int>& dx : dxs) {
                    pair<int, int> next = {node.first + dx.first, node.second + dx.second};

                    if (visited[next.first][next.second] || field[theater][next.first][next.second]) {
                        continue;
                    }

                    q.push(next);
                    visited[next.first][next.second] = true;
                    curSize++;
                }
            }

            maxComp[theater] = max(maxComp[theater], curSize);
        }
    }
}

void init(int N) {
    n = N;
    memset(field, -1, sizeof(field));
    memset(maxComp, 0, sizeof(maxComp));

    for (int i = 1; i <= n; i++) {
        maxComp[i] = 100;

        for (int j = 1; j <= 10; j++) {
            for (int k = 1; k <= 10; k++) {
                field[i][j][k] = 0;
            }
        }
    }
}

Result reserveSeats(int mID, int K) {
    int theater = 0;

    for (int i = 1; i <= n; i++) {
        if (maxComp[i] >= K) {
            theater = i;
            break;
        }
    }

    if (!theater) {
        Result res;
        res.id = 0;
        res.num = 0;
        return res;
    }

    theaterOf[mID] = theater;
    reservOf[mID].clear();

    bool fin = false;
    bool visited[15][15] = {0};

    for (int i = 1; !fin && i <= 10; i++) {
        for (int j = 1; !fin && j <= 10; j++) {
            if (visited[i][j] || field[theater][i][j]) {
                continue;
            }

            vector<pair<int, int>> cur;
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

            pq.push({i, j});
            visited[i][j] = true;

            while (!pq.empty()) {
                pair<int, int> node = pq.top();
                pq.pop();
                cur.push_back(node);

                if (cur.size() == K) {
                    reservOf[mID] = cur;
                    fin = true;
                    break;
                }

                pair<int, int> dxs[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

                for (const pair<int, int>& dx : dxs) {
                    pair<int, int> next = {node.first + dx.first, node.second + dx.second};

                    if (visited[next.first][next.second] || field[theater][next.first][next.second]) {
                        continue;
                    }

                    pq.push(next);
                    visited[next.first][next.second] = true;
                }
            }
        }
    }

    for (const pair<int, int>& node : reservOf[mID]) {
        field[theater][node.first][node.second] = 1;
    }

    refreshMaxComp(theater);

    pair<int, int> mini = *min_element(reservOf[mID].begin(), reservOf[mID].end());
    Result res;
    res.id = theater;
    res.num = (mini.first - 1) * 10 + mini.second;
    return res;
}

Result cancelReservation(int mID) {
    Result res;
    res.id = theaterOf[mID];
    res.num = 0;

    for (const pair<int, int>& node : reservOf[mID]) {
        field[theaterOf[mID]][node.first][node.second] = 0;
        res.num += (node.first - 1) * 10 + node.second;
    }

    refreshMaxComp(theaterOf[mID]);
    return res;
}
