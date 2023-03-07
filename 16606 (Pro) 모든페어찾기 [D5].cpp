#include <bits/stdc++.h>
using namespace std;

extern bool checkCards(int mIndexA, int mIndexB, int mDiff);

int n;
int baseCard;
int diffs[100005];
vector<int> idxOfDiffs[100005];

void calcDiffs(bool fillIdxOfDiffs) {
    for (int i = 0; i < n * 2; i++) {
        if (i == baseCard) {
            diffs[i] = 0;

            if (fillIdxOfDiffs) {
                idxOfDiffs[0].push_back(i);
            }

            continue;
        }

        int left = 0, right = n;

        while (left < right) {
            int mid = (left + right) / 2;
            bool result = checkCards(baseCard, i, mid);

            if (result) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        diffs[i] = left;

        if (fillIdxOfDiffs) {
            idxOfDiffs[left].push_back(i);
        }
    }
}

void playGame(int N) {
    n = N;
    baseCard = 0;

    for (int i = 0; i < n; i++) {
        idxOfDiffs[i].clear();
    }

    calcDiffs(false);

    int maxDiff = -1;
    int maxDiffIdx = -1;

    for (int i = 0; i < n * 2; i++) {
        if (diffs[i] > maxDiff) {
            maxDiff = diffs[i];
            maxDiffIdx = i;
        }
    }

    baseCard = maxDiffIdx;
    calcDiffs(true);

    for (int i = 0; i < n; i++) {
        checkCards(idxOfDiffs[i][0], idxOfDiffs[i][1], 0);
    }
}
