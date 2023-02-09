#include <set>
using namespace std;

#define MOD 2000003

int n;
int indexCounter;

int indexOfGeneral[MOD];
int posOfIndex[8625];
int indexOfPos[625];
int soldierOfPos[625];
int disjointSetParent[8625];
int disjointSetSize[625];
set<int> disjointSetEnemy[625];

inline int convert1dTo2dRow(int i) {
    return i / n;
}

inline int convert1dTo2dCol(int i) {
    return i % n;
}

inline int convert2dTo1d(int i, int j) {
    return i * n + j;
}

unsigned int hhash(char str[], int len = 0) {
    unsigned long long hashed = 0;

    for (int i = 0; (len > 0) ? i < len : str[i]; i++) {
        hashed *= 31;
        hashed += str[i] - 'a';
    }

    return hashed % MOD;
}

int disjointSetFind(int a) {
    if (disjointSetParent[a] == -1) {
        return -1;
    } else if (disjointSetParent[a] == a) {
        return a;
    }
    else {
        return (disjointSetParent[a] = disjointSetFind(disjointSetParent[a]));
    }
}

void disjointSetUnion(int a, int b) {
    int pa = disjointSetFind(a), pb = disjointSetFind(b);

    if (pa != pb) {
        if (disjointSetSize[pa] < disjointSetSize[pb]) {
            disjointSetParent[pa] = pb;
            disjointSetSize[pb] += disjointSetSize[pa];
            disjointSetEnemy[pb].insert(disjointSetEnemy[pa].begin(), disjointSetEnemy[pa].end());

            for (int other : disjointSetEnemy[pa]) {
                disjointSetEnemy[other].insert(pb);
            }
        }
        else {
            disjointSetParent[pb] = pa;
            disjointSetSize[pa] += disjointSetSize[pb];
            disjointSetEnemy[pa].insert(disjointSetEnemy[pb].begin(), disjointSetEnemy[pb].end());

            for (int other : disjointSetEnemy[pb]) {
                disjointSetEnemy[other].insert(pa);
            }
        }
    }
}

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11]) {
    n = N;
    indexCounter = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            unsigned int hashed = hhash(mMonarch[i][j]);
            int pos = convert2dTo1d(i, j);
            int index = indexCounter++;

            indexOfGeneral[hashed] = index;
            posOfIndex[index] = pos;
            indexOfPos[pos] = index;
            soldierOfPos[pos] = mSoldier[i][j];
            disjointSetParent[index] = index;
            disjointSetSize[index] = 1;
            disjointSetEnemy[index].clear();
        }
    }
}

void destroy() {
}

int ally(char mMonarchA[11], char mMonarchB[11]) {
    unsigned int hashedA = hhash(mMonarchA), hashedB = hhash(mMonarchB);
    int disjointSetA = disjointSetFind(indexOfGeneral[hashedA]), disjointSetB = disjointSetFind(indexOfGeneral[hashedB]);

    if (disjointSetA == disjointSetB) {
        return -1;
    }

    if (disjointSetEnemy[disjointSetA].find(disjointSetB) != disjointSetEnemy[disjointSetA].end()) {
        return -2;
    }

    disjointSetUnion(disjointSetA, disjointSetB);
    return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11]) {
    unsigned int hashedA = hhash(mMonarchA), hashedB = hhash(mMonarchB);
    int indexA = indexOfGeneral[hashedA], indexB = indexOfGeneral[hashedB];
    int disjointSetA = disjointSetFind(indexA), disjointSetB = disjointSetFind(indexB);

    if (disjointSetA == disjointSetB) {
        return -1;
    }

    int posB = posOfIndex[indexB];
    int rowB = convert1dTo2dRow(posB), colB = convert1dTo2dCol(posB);
    int dxs[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    bool attacked = false;
    int attackCount = 0;
    int defendCount = soldierOfPos[posB];

    for (int i = 0; i < 8; i++) {
        int row = rowB + dxs[i][0], col = colB + dxs[i][1];

        if (row < 0 || row > n - 1 || col < 0 || col > n - 1) {
            continue;
        }

        int pos = convert2dTo1d(row, col);
        int disjointSet = disjointSetFind(indexOfPos[pos]);

        if (disjointSet == disjointSetA) {
            attacked = true;
            break;
        }
    }

    if (!attacked) {
        return -2;
    }

    disjointSetEnemy[disjointSetA].insert(disjointSetB);
    disjointSetEnemy[disjointSetB].insert(disjointSetA);

    for (int i = 0; i < 8; i++) {
        int row = rowB + dxs[i][0], col = colB + dxs[i][1];

        if (row < 0 || row > n - 1 || col < 0 || col > n - 1) {
            continue;
        }

        int pos = convert2dTo1d(row, col);
        int disjointSet = disjointSetFind(indexOfPos[pos]);

        if (disjointSet == disjointSetA) {
            attackCount += soldierOfPos[pos] / 2;
            soldierOfPos[pos] -= soldierOfPos[pos] / 2;
        }
        else if (disjointSet == disjointSetB) {
            defendCount += soldierOfPos[pos] / 2;
            soldierOfPos[pos] -= soldierOfPos[pos] / 2;
        }
    }

    if (defendCount >= attackCount) {
        soldierOfPos[posB] = defendCount - attackCount;
        return 0;
    }

    soldierOfPos[posB] = attackCount - defendCount;

    unsigned int hashedNew = hhash(mGeneral);
    indexOfGeneral[hashedNew] = indexCounter++;
    posOfIndex[indexOfGeneral[hashedNew]] = posB;
    indexOfPos[posB] = indexOfGeneral[hashedNew];
    disjointSetParent[indexOfGeneral[hashedNew]] = disjointSetA;
    disjointSetSize[disjointSetA]++;
    return 1;
}

int recruit(char mMonarch[11], int mNum, int mOption) {
    unsigned int hashed = hhash(mMonarch);
    int index = indexOfGeneral[hashed];
    int pos = posOfIndex[index];

    if (mOption == 0) {
        soldierOfPos[pos] += mNum;
        return soldierOfPos[pos];
    }

    int disjointSet = disjointSetFind(index);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos = convert2dTo1d(i, j);

            if (disjointSetFind(indexOfPos[pos]) == disjointSet) {
                soldierOfPos[pos] += mNum;
                ans += soldierOfPos[pos];
            }
        }
    }

    return ans;
}
