#include <bits/stdc++.h>
using namespace std;

#define MAX_LEN 200
#define TERM_NUMBER 1
#define TERM_OP 2

struct Term {
    int type = TERM_NUMBER;
    int a2 = 0;
    int b2 = 0;
    int c2 = 0;
    int ab = 0;
    int ac = 0;
    int bc = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int num = 0;
    char op = '\0';

    bool operator==(const Term& other) const {
        return (type == other.type && a2 == other.a2 && b2 == other.b2 && c2 == other.c2
                && ab == other.ab && ac == other.ac && bc == other.bc
                && a == other.a && b == other.b && c == other.c && num == other.num);
    }
};

namespace std {
    template<>
    struct hash<Term> {
        size_t operator()(const Term& t) const {
            hash<int> hashFunc;
            return hashFunc(t.a2) ^ hashFunc(t.b2) ^ hashFunc(t.c2)
                ^ hashFunc(t.ab) ^ hashFunc(t.ac) ^ hashFunc(t.bc)
                ^ hashFunc(t.a) ^ hashFunc(t.b) ^ hashFunc(t.c) ^ hashFunc(t.num);
        }
    };
}

Term termById[5005];
unordered_map<Term, int> terms;

void init() {
    terms.clear();
}

int addExpression(int mID, char mExpression[MAX_LEN + 1]) {
    char opStack[205];
    int opStackSize = 0;

    Term postExpr[205];
    int postExprSize = 0;

    Term termStack[205];
    int termStackSize = 0;

    for (int i = 0; mExpression[i]; i++) {
        char c = mExpression[i];

        if (c == '+' || c == '-' || c == '*' || c == '(' || c == ')') {
            if (c == '(') {
                opStack[opStackSize++] = c;
            }
            else if (c == ')') {
                while (opStackSize) {
                    char top = opStack[--opStackSize];

                    if (top == '(') {
                        break;
                    }

                    Term term;
                    term.type = TERM_OP;
                    term.op = top;
                    postExpr[postExprSize++] = term;
                }
            }
            else if (c == '*') {
                while (opStackSize) {
                    char top = opStack[opStackSize - 1];

                    if (top != '*') {
                        break;
                    }

                    opStackSize--;

                    Term term;
                    term.type = TERM_OP;
                    term.op = top;
                    postExpr[postExprSize++] = term;
                }

                opStack[opStackSize++] = c;
            }
            else {
                while (opStackSize) {
                    char top = opStack[opStackSize - 1];

                    if (top == '(') {
                        break;
                    }

                    opStackSize--;

                    Term term;
                    term.type = TERM_OP;
                    term.op = top;
                    postExpr[postExprSize++] = term;
                }

                opStack[opStackSize++] = c;
            }
        }
        else {
            Term term;
            term.type = TERM_NUMBER;

            switch (c) {
            case 'A':
                term.a = 1;
                break;
            case 'B':
                term.b = 1;
                break;
            case 'C':
                term.c = 1;
                break;
            default:
                term.num = c - '0';
            }

            postExpr[postExprSize++] = term;
        }
    }

    while (opStackSize) {
        char top = opStack[--opStackSize];

        Term term;
        term.type = TERM_OP;
        term.op = top;
        postExpr[postExprSize++] = term;
    }

    for (int i = 0; i < postExprSize; i++) {
        if (postExpr[i].type == TERM_NUMBER) {
            termStack[termStackSize++] = postExpr[i];
        }
        else {
            Term left = termStack[termStackSize - 2];
            Term right = termStack[termStackSize - 1];
            termStackSize -= 2;

            if (postExpr[i].op == '+') {
                left.a2 += right.a2;
                left.b2 += right.b2;
                left.c2 += right.c2;
                left.ab += right.ab;
                left.ac += right.ac;
                left.bc += right.bc;
                left.a += right.a;
                left.b += right.b;
                left.c += right.c;
                left.num += right.num;
            }
            else if (postExpr[i].op == '-') {
                left.a2 -= right.a2;
                left.b2 -= right.b2;
                left.c2 -= right.c2;
                left.ab -= right.ab;
                left.ac -= right.ac;
                left.bc -= right.bc;
                left.a -= right.a;
                left.b -= right.b;
                left.c -= right.c;
                left.num -= right.num;
            }
            else if (postExpr[i].op == '*') {
                left.a2 = left.a * right.a;
                left.b2 = left.b * right.b;
                left.c2 = left.c * right.c;
                left.ab = (left.a * right.b) + (left.b * right.a);
                left.ac = (left.a * right.c) + (left.c * right.a);
                left.bc = (left.b * right.c) + (left.c * right.b);
                left.a = (left.a * right.num) + (left.num * right.a);
                left.b = (left.b * right.num) + (left.num * right.b);
                left.c = (left.c * right.num) + (left.num * right.c);
                left.num = left.num * right.num;
            }

            termStack[termStackSize++] = left;
        }
    }

    termById[mID] = termStack[termStackSize - 1];
    int cnt = terms[termById[mID]]++;

    if (cnt > 0) {
        return cnt;
    }

    return -1 * ((int)(termById[mID].a2 || termById[mID].ab || termById[mID].ac || termById[mID].a)
        + (int)(termById[mID].b2 || termById[mID].ab || termById[mID].bc || termById[mID].b)
        + (int)(termById[mID].c2 || termById[mID].ac || termById[mID].bc || termById[mID].c));
}

int calcExpression(int mID, int mA, int mB, int mC) {
    const Term& term = termById[mID];
    return mA * mA * term.a2 + mB * mB * term.b2 + mC * mC * term.c2
        + mA * mB * term.ab + mA * mC * term.ac + mB * mC * term.bc
        + mA * term.a + mB * term.b + mC * term.c + term.num;
}
