#include <bits/stdc++.h>
#ifndef LOCAL
#pragma GCC optimize(3)
#endif
#define IOS ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
const int N=6e5;
struct Pal {
    int nxt[N][26], fail[N], cnt[N], num[N], len[N], S[N], last, n, p;
    int newNode(int l) {
        memset(nxt[p], 0, sizeof(nxt[p]));
        cnt[p]=num[p]=0; len[p]=l;
        return p++;
    }
    void init() {
        p=0; newNode(0); newNode(-1);
        last=0; n=0; fail[0]=1; S[0]=-1;
    }
    int getFail(int x) {
        for (; S[n-len[x]-1]!=S[n]; x=fail[x]);
        return x;
    }
    void add(int c) {
        c-='a';
        S[++n]=c;
        int cur=getFail(last);
        if (!nxt[cur][c]) {
            int now=newNode(len[cur]+2);
            fail[now]=nxt[getFail(fail[cur])][c];
            nxt[cur][c]=now;
            num[now]=num[fail[now]]+1;
        }
        last=nxt[cur][c];
        cnt[last]++;
    }
    void count() {
        for (int i=p-1; ~i; i--) cnt[fail[i]]+=cnt[i];
    }
}pal;
bool check(int x) {
    int Ls=pal.len[x];
    int Lf=pal.len[pal.fail[x]];
    int deta=Ls-Lf;
    if (Ls/2%deta==0) return true;
    return false;
}
char s[N];
int ans[N];
int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for (; ~scanf("%s", s); ) {
        int len=strlen(s);
        memset(ans, 0, 4*len+16);
        pal.init();
        for (int i=0; i<len; i++)
            pal.add(s[i]);
        pal.count();
        for (int i=2; i<pal.p; i++) {
            if (check(i)) {
                ans[pal.len[i]]+=pal.cnt[i];
            }
        }
        for (int i=1; i<=len; i++) {
            printf("%d%c", ans[i], " \n"[i==len]);
        }
    }
    return 0;
}