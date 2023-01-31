/*
 * A problem solving template
 * Written in 2022 by Na Jongwoo <njw1204@naver.com>
 *
 * Please visit: https://github.com/njw1204/problem-solving-template
 */

#if defined(__GNUC__)&&!defined(__llvm__)
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")
#endif
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<pi, pi> ppi;
typedef pair<pl, pl> ppl;
#define __CC(a,b) a##b
#define $1 first
#define $2 second
#define endl '\n'
#define DINPUT(t,...) t __VA_ARGS__;INPUT(__VA_ARGS__)
#define REP(i,n) for(int i=0,__REP##i=0;__REP##i<(n);i=++__REP##i)
#define FOR(i,s,e) for(auto i=(s),__FOR##i=(s);__FOR##i<=(e);i=++__FOR##i)
#define TESTCASE(t) DINPUT(int,__TESTCASE##t);FOR(t,1,__TESTCASE##t)
#define MEMZERO(a) memset((a),0,sizeof(a))
#define MEMNEG(a) memset((a),-1,sizeof(a))
#define FILL(c,x) for(auto &__FILL:(c))__FILL=(x)
#define ALL(c) (c).begin(),(c).end()
#define UNSYNC ios_base::sync_with_stdio(false);cin.tie(nullptr)
#ifdef LOCAL_ALGO
#define READTXT for(__CC(ifst,ream) __READTXT(STDIN);__READTXT&&__READTXT.get()!=-1&&__CC(freo,pen)(STDIN,"r",stdin);)__READTXT.close()
#define DEBUG(...) cerr << "[" << #__VA_ARGS__ << "]:", __DEBUG_OUT(__VA_ARGS__)
#else
#define READTXT
#define DEBUG(...)
#endif
#define STDIN "_input.txt"
string to_string(const string& s) { return '"' + s + '"'; } string to_string(bool b) { return b ? "true" : "false"; } string to_string(char c) { string s; s += c; return s; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")"; }
template <typename A> string to_string(A v) { bool f = true; string r = "{"; for (const auto& x : v) { if (!f) r += ", "; f = false; r += to_string(x); } r += "}"; return r; }
void __DEBUG_OUT() { cerr << endl; } template <typename H, typename... T> void __DEBUG_OUT(H h, T... t) { cerr << " " << to_string(h); __DEBUG_OUT(t...); }
template<typename T> const T& MIN(const T& arg) { return arg; } template<typename T, typename... Ts> const T& MIN(const T& arg, const Ts&... args) { return min(arg, MIN(args...)); }
template<typename T> const T& MAX(const T& arg) { return arg; } template<typename T, typename... Ts> const T& MAX(const T& arg, const Ts&... args) { return max(arg, MAX(args...)); }
template<typename T> void INPUT(T& arg) { cin >> arg; } template<typename T, typename... Ts> void INPUT(T& arg, Ts&... args) { cin >> arg; INPUT(args...); }
template<typename T> void PRINT(const T& arg) { cout << arg << '\n'; } template<typename T, typename... Ts> void PRINT(const T& arg, const Ts&... args) { cout << arg << ' '; PRINT(args...); }
ull GCD(ull a, ull b) { while (b != 0) { ull t = a % b; a = b; b = t; } return a; }
ull LCM(ull a, ull b) { return a * b > 0 ? a * b / GCD(a, b) : 0; }
ull POW(ull a, ull b, ull m = ULLONG_MAX) { ull r = 1; while (b) { if (b & 1) r = r * a % m; b >>= 1; a = a * a % m; } return r; }

char target[2005][2005];
ull targetHash[2005];
char field[2005][2005];
ull fieldHash[2005][2005];

ull hhash(const char* str, int len) {
    ull hash = 0;

    for (int i = 0; i < len; i++) {
        hash *= 3;
        hash += str[i];
    }

    return hash;
}

ull lhash(const ull* arr, int len) {
    ull hash = 0;

    for (int i = 0; i < len; i++) {
        hash *= 5;
        hash += arr[i];
    }

    return hash;
}

int main() {
    UNSYNC; READTXT;
    setbuf(stdout, NULL);
    TESTCASE(T) {
        int ans = 0;
        DINPUT(int, H, W, N, M);

        FOR(i, 0, H - 1) {
            FOR(j, 0, W - 1) {
                cin >> target[i][j];

                if (target[i][j] == 'o') {
                    target[i][j] = 1;
                }
                else {
                    target[i][j] = 2;
                }
            }
        }

        FOR(i, 0, N - 1) {
            FOR(j, 0, M - 1) {
                cin >> field[i][j];

                if (field[i][j] == 'o') {
                    field[i][j] = 1;
                }
                else {
                    field[i][j] = 2;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            int left = 0, right = W - 1;
            targetHash[i] = hhash(&target[i][left], W);
            fieldHash[i][left] = hhash(&field[i][left], W);

            ull base = POW(3, W - 1);

            while (right < M - 1) {
                right++;
                ull now = (fieldHash[i][left] - base * field[i][left]) * 3 + field[i][right];
                left++;
                fieldHash[i][left] = now;
            }
        }

        ull targetOneHash = lhash(targetHash, H);

        for (int c = 0; c < M - W + 1; c++) {
            int left = 0, right = H - 1;
            ull now = 0;

            for (int i = left; i <= right; i++) {
                now *= 5;
                now += fieldHash[i][c];
            }

            if (targetOneHash == now) {
                ans++;
            }

            ull base = POW(5, H - 1);

            while (right < N - 1) {
                right++;
                now = (now - base * fieldHash[left][c]) * 5 + fieldHash[right][c];
                left++;

                if (targetOneHash == now) {
                    ans++;
                }
            }
        }

        cout << "#" << T << " " << ans << endl;
    }
}
