#include <bits/stdc++.h>
using namespace std;

struct Phrase {
    unsigned int words[10];
    unsigned int hash;
    int size = 0;
};

int gN, gK;
list<Phrase> dq[1005];

unsigned int hhash(char text[], int len) {
    unsigned int hashed = 0;

    for (int i = 0; i < len; i++) {
        hashed *= 31;
        hashed += text[i] - 'a';
    }

    return hashed;
}

unsigned int vhash(unsigned int words[], int len) {
    unsigned int hashed = 0;

    for (int i = 0; i < len; i++) {
        hashed *= 131;
        hashed += words[i];
    }

    return hashed;
}

void init(int N, int K) {
    gN = N;
    gK = K;

    for (int i = 0; i <= N; i++) {
        dq[i].clear();
    }
}

void sendMail(char subject[], int uID, int cnt, int rIDs[]) {
    Phrase phrase;
    int left = 0;

    for (int right = 0, len = strlen(subject); right < len; right++) {
        if (subject[right] == ' ') {
            phrase.words[phrase.size++] = hhash(subject + left, right - left);
            left = right + 1;
        }
        else if (right == len - 1) {
            phrase.words[phrase.size++] = hhash(subject + left, right - left + 1);
        }
    }

    phrase.hash = vhash(phrase.words, phrase.size);

    for (int i = 0; i < cnt; i++) {
        int rID = rIDs[i];
        dq[rID].push_back(phrase);

        if (dq[rID].size() > gK) {
            dq[rID].erase(dq[rID].begin());
        }
    }
}

int getCount(int uID) {
    return dq[uID].size();
}

int deleteMail(int uID, char subject[]) {
    int cnt = 0;

    Phrase phrase;
    int left = 0;

    for (int right = 0, len = strlen(subject); right < len; right++) {
        if (subject[right] == ' ') {
            phrase.words[phrase.size++] = hhash(subject + left, right - left);
            left = right + 1;
        }
        else if (right == len - 1) {
            phrase.words[phrase.size++] = hhash(subject + left, right - left + 1);
        }
    }

    phrase.hash = vhash(phrase.words, phrase.size);

    for (auto it = dq[uID].begin(); it != dq[uID].end();) {
        const Phrase& x = *it;

        if (x.size == phrase.size && x.hash == phrase.hash) {
            it = dq[uID].erase(it);
            cnt++;
            continue;
        }

        it++;
    }

    return cnt;
}

int searchMail(int uID, char text[]) {
    int cnt = 0;
    unsigned int textHash = hhash(text, strlen(text));

    for (auto it = dq[uID].begin(); it != dq[uID].end(); it++) {
        const Phrase& x = *it;

        for (int i = 0; i < x.size; i++) {
            if (x.words[i] == textHash) {
                cnt++;
                break;
            }
        }
    }

    return cnt;
}
