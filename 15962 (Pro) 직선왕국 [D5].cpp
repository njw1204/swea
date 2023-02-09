#include <bits/stdc++.h>
using namespace std;

#define TYPE_FETCH_FIN 1
#define TYPE_ORDER_FIN 2
#define TYPE_ORDER 3
#define TYPE_FETCH 4

struct Task {
    int type;
    int startTime;
    int endTime;
    int index;
    int amount;

    Task(int type, int startTime, int endTime, int index, int amount)
        : type(type), startTime(startTime), endTime(endTime), index(index), amount(amount) {}

    bool operator<(const Task& other) const {
        if (startTime != other.startTime) {
            return startTime > other.startTime;
        }
        else {
            return type > other.type;
        }
    }
};

int n, m;
int ans;
int remainMember;
priority_queue<Task> pq;
int expectedAmount[205];
int cityCurAmount[205];
bool cityCurFetching[205];

void init(int N, int M) {
    n = N;
    m = M;
    ans = 0;
    remainMember = M;
    pq = {};
    memset(expectedAmount, 0, sizeof(expectedAmount));
    memset(cityCurAmount, 0, sizeof(cityCurAmount));
    memset(cityCurFetching, 0, sizeof(cityCurFetching));
}

void destroy() {
}

int check(int tStamp) {
    while (!pq.empty()) {
        Task base = pq.top();

        if (base.startTime > tStamp) {
            break;
        }

        while (!pq.empty() && pq.top().startTime == base.startTime) {
            Task task = pq.top();
            pq.pop();

            if (task.type == TYPE_FETCH_FIN) {
                ans += task.amount;
                remainMember++;
                cityCurFetching[task.index] = false;
            }

            if (task.type == TYPE_ORDER_FIN) {
                cityCurAmount[task.index] += task.amount;
                expectedAmount[task.index] -= task.amount;
            }

            if (task.type == TYPE_ORDER) {
                pq.push(Task(TYPE_ORDER_FIN, task.endTime, task.endTime, task.index, task.amount));
                expectedAmount[task.index] += task.amount;
            }

            if (task.type == TYPE_FETCH) {
                pq.push(Task(TYPE_FETCH_FIN, task.endTime + task.index, task.endTime + task.index, task.index, cityCurAmount[task.index]));
                cityCurAmount[task.index] = 0;
            }
        }

        while (remainMember) {
            int bestExpectedAmount = -1;
            int bestExpectedAmountIndex = -1;

            for (int i = 1; i < n; i++) {
                if (cityCurFetching[i]) {
                    continue;
                }

                if (expectedAmount[i] + cityCurAmount[i] > bestExpectedAmount) {
                    bestExpectedAmount = expectedAmount[i] + cityCurAmount[i];
                    bestExpectedAmountIndex = i;
                }
                else if (expectedAmount[i] + cityCurAmount[i] == bestExpectedAmount && i < bestExpectedAmountIndex) {
                    bestExpectedAmountIndex = i;
                }
            }

            if (bestExpectedAmount > 0) {
                pq.push(Task(TYPE_FETCH, base.startTime + bestExpectedAmountIndex, base.startTime + bestExpectedAmountIndex, bestExpectedAmountIndex, -1));
                cityCurFetching[bestExpectedAmountIndex] = true;
                remainMember--;
            }
            else {
                break;
            }
        }
    }

    return ans;
}

int order(int tStamp, int mCityA, int mCityB, int mTax) {
    int endTime = tStamp + abs(mCityA - mCityB);
    pq.push(Task(TYPE_ORDER, max(tStamp, endTime - mCityB), endTime, mCityB, mTax));

    return check(tStamp);
}
