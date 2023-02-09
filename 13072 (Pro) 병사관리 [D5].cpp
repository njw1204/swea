#define OP_DELTA -5

char teamOfSoldier[100001];
char scoreOfSoldier[100001];
int *ptrOfSoldier[100001];

int soldiersSize[5];
int soldiers[5][300000];

void init() {
    for (int i = 0; i < 5; i++) {
        soldiersSize[i] = 0;
    }
}

void hire(int mID, int mTeam, int mScore) {
    teamOfSoldier[mID] = mTeam - 1;
    scoreOfSoldier[mID] = mScore;
    ptrOfSoldier[mID] = &(soldiers[mTeam - 1][soldiersSize[mTeam - 1]++] = mID);
}

void fire(int mID) {
    *ptrOfSoldier[mID] = 0;
}

void updateSoldier(int mID, int mScore) {
    *ptrOfSoldier[mID] = 0;
    scoreOfSoldier[mID] = mScore;
    ptrOfSoldier[mID] = &(soldiers[teamOfSoldier[mID]][soldiersSize[teamOfSoldier[mID]]++] = mID);
}

void updateTeam(int mTeam, int mChangeScore) {
    soldiers[mTeam - 1][soldiersSize[mTeam - 1]++] = mChangeScore + OP_DELTA;
}

int bestSoldier(int mTeam) {
    int maxNumOfScore[6] = {0};
    int* team = soldiers[mTeam - 1];

    for (int i = 0, size = soldiersSize[mTeam - 1]; i < size; i++) {
        if (!team[i]) {
            continue;
        }

        if (team[i] < 0) {
            int inc = team[i] - OP_DELTA;
            int nextMaxNumOfScore[6] = {0};

            for (int score = 1; score <= 5; score++) {
                int target = score + inc;

                if (target < 1) {
                    target = 1;
                }
                else if (target > 5) {
                    target = 5;
                }

                if (maxNumOfScore[score] > nextMaxNumOfScore[target]) {
                    nextMaxNumOfScore[target] = maxNumOfScore[score];
                }
            }

            for (int score = 1; score <= 5; score++) {
                maxNumOfScore[score] = nextMaxNumOfScore[score];
            }
        }
        else {
            int score = scoreOfSoldier[team[i]];
            int num = team[i];

            if (num > maxNumOfScore[score]) {
                maxNumOfScore[score] = num;
            }
        }
    }

    for (int score = 5; score >= 1; score--) {
        if (maxNumOfScore[score]) {
            return maxNumOfScore[score];
        }
    }
}
