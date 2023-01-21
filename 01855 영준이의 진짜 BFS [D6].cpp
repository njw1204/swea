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
typedef pair<ull, ull> pul;
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

int N;
int parent[100005][18];
int depth[100005];
vector<int> children[100005];

void clear() {
    FOR(i, 0, N) {
        MEMZERO(parent[i]);
        depth[i] = 0;
        children[i].clear();
    }
}

void depthDfs(int node, int cur) {
    stack<pi> callStack;
    callStack.push({node, cur});

    while (!callStack.empty()) {
        int node = callStack.top().$1;
        int cur = callStack.top().$2;
        callStack.pop();

        depth[node] = cur;

        for (int next : children[node]) {
            callStack.push({next, cur + 1});
        }
    }
}

void buildLCA(int node) {
    stack<int> callStack;
    callStack.push(node);

    while (!callStack.empty()) {
        int node = callStack.top();
        callStack.pop();

        for (int i = 1; i <= 17; i++) {
            parent[node][i] = parent[parent[node][i - 1]][i - 1];
        }

        for (int next : children[node]) {
            callStack.push(next);
        }
    }
}

int LCA(int a, int b) {
    if (a == 1 || b == 1) {
        return 1;
    }

    if (depth[a] != depth[b]) {
        if (depth[a] < depth[b]) {
            swap(a, b);
        }

        for (int i = 17; i >= 0; i--) {
            if (depth[parent[a][i]] >= depth[b]) {
                a = parent[a][i];
            }
        }
    }

    if (a == b) {
        return a;
    }

    for (int i = 17; i >= 0; i--) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }

    return parent[a][0];
}

int main(void) {
    UNSYNC; READTXT;
    TESTCASE(T) {
        cin >> N;

        FOR(i, 2, N) {
            DINPUT(int, x);
            parent[i][0] = x;
            children[x].push_back(i);
        }

        depthDfs(1, 0);
        buildLCA(1);

        vector<int> trav;
        queue<int> Q;
        int lastDepth = 0;
        ll ans = 0;
        Q.push(1);

        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            trav.push_back(cur);

            for (int next : children[cur]) {
                Q.push(next);
            }
        }

        for (int i = 1; i < trav.size(); i++) {
            int a = trav[i - 1], b = trav[i];
            int lca = LCA(a, b);
            ans += depth[a] - depth[lca] + depth[b] - depth[lca];
        }

        cout << "#" << T << " " << ans << endl;
        clear();
    }
}
