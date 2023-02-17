#include <bits/stdc++.h>
using namespace std;

#define RANGE_NORMAL 1
#define RANGE_START 2
#define RANGE_END 3

struct Range {
    int from;
    int to;
    int type = RANGE_NORMAL;

    bool operator<(const Range& other) const {
        if (to - from != other.to - other.from) {
            return to - from > other.to - other.from;
        }

        return to < other.to;
    }

    bool operator==(const Range& other) const {
        return (from == other.from) && (to == other.to);
    }
};

int n;
set<Range> s;
unordered_map<int, Range> rangeByFrom;
unordered_map<int, Range> rangeByTo;
unordered_map<int, int> idToPos;
int cnt;

void addRange(int from, int to, int type) {
    if (from > to) {
        return;
    }

    Range nextRange;
    nextRange.from = from;
    nextRange.to = to;
    nextRange.type = type;

    s.insert(nextRange);
    rangeByFrom[from] = nextRange;
    rangeByTo[to] = nextRange;
}

void eraseRange(const Range& range) {
    s.erase(range);
    rangeByFrom.erase(range.from);
    rangeByTo.erase(range.to);
}

void init(int N) {
    n = N;
    s.clear();
    rangeByFrom.clear();
    rangeByTo.clear();
    idToPos.clear();
    cnt = 0;
}

int arrive(int mId) {
    cnt++;

    if (s.empty()) {
        idToPos[mId] = 1;
        addRange(2, n, RANGE_END);
        return 1;
    }

    Range range = *s.begin();
    eraseRange(range);

    if (range.type == RANGE_START) {
        idToPos[mId] = 1;
        addRange(2, range.to, RANGE_NORMAL);
        return 1;
    }
    else if (range.type == RANGE_END) {
        idToPos[mId] = n;
        addRange(range.from, n - 1, RANGE_NORMAL);
        return n;
    }
    else {
        int center = (range.from + range.to) / 2;
        idToPos[mId] = center;
        addRange(range.from, center - 1, RANGE_NORMAL);
        addRange(center + 1, range.to, RANGE_NORMAL);
        return center;
    }
}

int leave(int mId) {
    cnt--;

    int pos = idToPos[mId];
    idToPos[mId] = 0;

    auto itByTo = rangeByTo.find(pos - 1);
    auto itByFrom = rangeByFrom.find(pos + 1);

    if (itByTo != rangeByTo.end() && itByFrom != rangeByFrom.end()) {
        Range rangeLeft = itByTo->second;
        Range rangeRight = itByFrom->second;
        eraseRange(rangeLeft);
        eraseRange(rangeRight);

        if (cnt > 0) {
            int type = RANGE_NORMAL;

            if (rangeLeft.from == 1) {
                type = RANGE_START;
            }
            else if (rangeRight.to == n) {
                type = RANGE_END;
            }

            addRange(rangeLeft.from, rangeRight.to, type);
        }
    } else if (itByTo != rangeByTo.end()) {
        Range rangeLeft = itByTo->second;
        eraseRange(rangeLeft);

        if (cnt > 0) {
            int type = RANGE_NORMAL;

            if (rangeLeft.from == 1) {
                type = RANGE_START;
            }
            else if (pos == n) {
                type = RANGE_END;
            }

            addRange(rangeLeft.from, pos, type);
        }
    }
    else if (itByFrom != rangeByFrom.end()) {
        Range rangeRight = itByFrom->second;
        eraseRange(rangeRight);

        if (cnt > 0) {
            int type = RANGE_NORMAL;

            if (pos == 1) {
                type = RANGE_START;
            }
            else if (rangeRight.to == n) {
                type = RANGE_END;
            }

            addRange(pos, rangeRight.to, type);
        }
    }
    else {
        if (cnt > 0) {
            int type = RANGE_NORMAL;

            if (pos == 1) {
                type = RANGE_START;
            }
            else if (pos == n) {
                type = RANGE_END;
            }

            addRange(pos, pos, type);
        }
    }

    return n - cnt;
}
