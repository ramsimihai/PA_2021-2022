#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> G[10005];
bool viz[10005];
int cnt;
int max_cnt = -1;

void dfs(int node) {
    viz[node] = true;
    cnt++;
    
    for (int i = 0; i < G[node].size(); ++i) {
        if (!viz[G[node][i]]) {
            dfs(G[node][i]);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        int x;
        scanf("%d", &x);
        G[i].push_back(x);
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            viz[j] = 0;
        }
        cnt = 0;
        dfs(i);
        // printf("\n");
        max_cnt = max(max_cnt, cnt);
    }
    
    printf("%d\n", max_cnt);
    return 0;
}