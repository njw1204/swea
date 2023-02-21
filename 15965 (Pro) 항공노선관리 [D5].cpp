#include <bits/stdc++.h>
using namespace std;

int n;
vector<pair<int, pair<int, int>>> timeEdges[60];
vector<pair<int, int>> priceEdges[60];

void init(int N) {
    n = N;

    for (int i = 0; i < n; i++) {
        timeEdges[i].clear();
        priceEdges[i].clear();
    }
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice) {
    timeEdges[mStartAirport].push_back({mEndAirport, {mStartTime, mTravelTime}});
    priceEdges[mStartAirport].push_back({mEndAirport, mPrice});
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime) {
    int dist[60];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    memset(dist, -1, sizeof(dist));

    pq.push({0, mStartAirport});
    dist[mStartAirport] = 0;

    while (!pq.empty()) {
        pair<int, int> node = pq.top();
        pq.pop();

        if (dist[node.second] < node.first) {
            continue;
        }

        if (node.second == mEndAirport) {
            return node.first;
        }

        for (const pair<int, pair<int, int>>& edge : timeEdges[node.second]) {
            int curTime = (mStartTime + node.first) % 24;
            int nextDist = node.first + (edge.second.first - curTime + 24) % 24 + edge.second.second;

            if (dist[edge.first] == -1 || nextDist < dist[edge.first]) {
                pq.push({nextDist, edge.first});
                dist[edge.first] = nextDist;
            }
        }
    }

    return -1;
}

int minPrice(int mStartAirport, int mEndAirport) {
    int dist[60];
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    memset(dist, -1, sizeof(dist));

    pq.push({0, mStartAirport});
    dist[mStartAirport] = 0;

    while (!pq.empty()) {
        pair<int, int> node = pq.top();
        pq.pop();

        if (dist[node.second] < node.first) {
            continue;
        }

        if (node.second == mEndAirport) {
            return node.first;
        }

        for (const pair<int, int>& edge : priceEdges[node.second]) {
            int nextDist = node.first + edge.second;

            if (dist[edge.first] == -1 || nextDist < dist[edge.first]) {
                pq.push({nextDist, edge.first});
                dist[edge.first] = nextDist;
            }
        }
    }

    return -1;
}
