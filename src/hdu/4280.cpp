#include <bits/stdc++.h>
#ifndef LOCAL
#pragma GCC optimize(3)
#endif
using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int maxn=1e5 + 100;
struct node {
    int f, to, nxt, from;
};
node ve[maxn << 2];
int head[maxn];
int cnt, stop, start;
int n, m;
void add(int u, int v, int w) {
    ve[cnt] = (node) {w, v, head[u], u};
    head[u] = cnt++;
    ve[cnt] = (node) {0, u, head[v], v};
    head[v] = cnt++;
}
int dep[maxn], gap[maxn];
void bfs() {
    memset(dep, -1, sizeof(dep));
    memset(gap, 0, sizeof(gap));
    gap[0] = 1; queue<int> q;
    dep[stop] = 0;
    q.push(stop);
    while (!q.empty()) {
        int now = q.front(); q.pop();
        for (int i = head[now]; ~i; i = ve[i].nxt) {
            int to = ve[i].to;
            if (dep[to] != -1) continue;
            q.push(to); dep[to] = dep[now] + 1;
            gap[dep[to]]++;
        }
    }
}

int cur[maxn], s[maxn];
int sap() {
    bfs();
    memcpy(cur, head, sizeof(head));
    int u = start, ans = 0, top = 0;
    while (dep[start] < n) {
        if (u == stop) {
            int flow = inf, inser;
            for (int i = 0; i < top; i++) {
                if (flow > ve[s[i]].f) {
                    flow = ve[s[i]].f, inser = i;
                }
            }
            for (int i = 0; i < top; i++) {
                ve[s[i]].f -= flow;
                ve[s[i] ^ 1].f += flow;
            }
            ans += flow; top = inser, u = ve[s[top]].from;
            continue;
        }
        bool flag = false;
        int v;
        for (int i = cur[u]; ~i; i = ve[i].nxt) {
            v = ve[i].to;
            if (ve[i].f && dep[v] + 1 == dep[u]) {
                flag = true; cur[u] = i; break;
            }
        }
        if (flag) {
            s[top++] = cur[u]; u = v; continue;
        }
        int Min = n;
        for (int i = head[u]; ~i; i = ve[i].nxt) {
            if (ve[i].f && dep[ve[i].to] < Min) {
                Min = dep[ve[i].to]; cur[u] = i;
            }
        }
        gap[dep[u]]--;
        if (!gap[dep[u]]) return ans;
        dep[u] = Min + 1;
        gap[dep[u]]++;
        if (u != start) u = ve[s[--top]].from;
    }
    return ans;
}
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; scanf("%d", &T);
    for (int TT = 1; TT <= T; TT++) {
        cnt= 0; memset(head, -1, sizeof(head));
        scanf("%d%d", &n, &m);
        int a, b, c;
        int lx = inf, rx = -inf;
        for (int i = 1; i <= n; i++) {
            scanf("%d%d", &a, &b);
            if (a >= rx) rx = a, stop = i;
            if (a <= lx) lx = a, start = i;
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
            add(b, a, c);
        }
        printf("%d\n", sap());
    }
    return 0;
}