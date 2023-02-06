#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> roads[605][2];
unordered_map<int, int> comp;

int compCity(int city) {
    auto it = comp.find(city);

    if (it != comp.end()) {
        return it->second;
    }

    return (comp[city] = comp.size() + 1);
}

int init(int N, int sCity[], int eCity[], int mCost[]) {
    comp.clear();

    for (int i = 0; i <= 600; i++) {
        roads[i][0].clear();
        roads[i][1].clear();
    }

    for (int i = 0; i < N; i++) {
        roads[compCity(sCity[i])][0].push_back({compCity(eCity[i]), mCost[i]});
        roads[compCity(eCity[i])][1].push_back({compCity(sCity[i]), mCost[i]});

    }

    return comp.size();
}

void add(int sCity, int eCity, int mCost) {
    roads[compCity(sCity)][0].push_back({compCity(eCity), mCost});
    roads[compCity(eCity)][1].push_back({compCity(sCity), mCost});
}

int cost(int mHub) {
    int ans = 0;

    int dist[605][2];
    memset(dist, -1, sizeof(dist));

    for (int type = 0; type <= 1; type++) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, compCity(mHub)});
        dist[compCity(mHub)][type] = 0;

        while (!pq.empty()) {
            pair<int, int> node = pq.top();
            pq.pop();

            if (node.first > dist[node.second][type]) {
                continue;
            }

            for (const auto& road : roads[node.second][type]) {
                if (dist[road.first][type] == -1 || node.first + road.second < dist[road.first][type]) {
                    pq.push({node.first + road.second, road.first});
                    dist[road.first][type] = node.first + road.second;
                }
            }
        }
    }

    for (int i = 1; i <= comp.size(); i++) {
        ans += dist[i][0] + dist[i][1];
    }

    return ans;
}
