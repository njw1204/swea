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

template<typename T>
struct MaxHeap {
    int n = 0;
    T arr[100005];

    void push(const T& t) {
        n++;
        arr[n] = t;

        for (int i = n; i > 1; i /= 2) {
            if (arr[i / 2] < arr[i]) {
                T temp = arr[i / 2];
                arr[i / 2] = arr[i];
                arr[i] = temp;
            }
            else {
                break;
            }
        }
    }

    T top() {
        return arr[1];
    }

    void pop() {
        if (size() == 0) {
            return;
        }

        arr[1] = arr[n];
        n--;

        for (int i = 1; ;) {
            bool checkLeft = false, checkRight = false;

            if (i * 2 <= n && arr[i] < arr[i * 2]) {
                checkLeft = true;
            }

            if (i * 2 + 1 <= n && arr[i] < arr[i * 2 + 1]) {
                checkRight = true;
            }

            if (checkLeft && checkRight) {
                if (arr[i * 2] < arr[i * 2 + 1]) {
                    checkLeft = false;
                }
                else {
                    checkRight = false;
                }
            }

            if (!checkLeft && !checkRight) {
                break;
            }
            else if (checkLeft) {
                T temp = arr[i];
                arr[i] = arr[i * 2];
                arr[i * 2] = temp;
                i = i * 2;
            }
            else {
                T temp = arr[i];
                arr[i] = arr[i * 2 + 1];
                arr[i * 2 + 1] = temp;
                i = i * 2 + 1;
            }
        }
    }

    int size() {
        return n;
    }

    void clear() {
        n = 0;
    }
};

int main() {
    UNSYNC; READTXT;
    MaxHeap<int> pq;

    TESTCASE(T) {
        cout << "#" << T << " ";
        DINPUT(int, N);

        REP(_, N) {
            DINPUT(int, op);

            if (op == 1) {
                DINPUT(int, x);
                pq.push(x);
            }
            else {
                if (pq.size() > 0) {
                    cout << pq.top() << " ";
                    pq.pop();
                }
                else {
                    cout << -1 << " ";
                }
            }
        }

        cout << endl;
        pq.clear();
    }
}
