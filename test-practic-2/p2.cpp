#include <stdio.h>
#include <cmath>
#include <iostream>

using namespace std;

#define N 55
#define M 55
#define INF -200000

int matrix[N][M];
int dp[N][N][M];
int n, m;

void read_input()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

int get_result(int x1, int x2, int y1) {
        int y2 = y1 + x1 - x2;

        if (x1 > n || x2 > n || y1 > m || y2 > m) {
            return INF;
        }

        if (dp[x1][x2][y1]) {
            return dp[x1][x2][y1];
        }

        if (x1 == n && x2 == n && y1 == m && y2 == m) {
            if (matrix[x1][y1] < 0) {
                return 0;
            } else {
                return matrix[x1][y1];
            }
        }

        int rez = max(get_result(x1 + 1, x2 + 1, y1), get_result(x1 + 1, x2, y1));
        rez = max(rez, get_result(x1, x2, y1 + 1));
        rez = max(rez, get_result(x1, x2 + 1, y1 + 1));
        
        if (x2 != x1) {
            dp[x1][x2][y1] = matrix[x1][y1] + matrix[x2][y2] + rez;
        } else {
            dp[x1][x2][y1] = matrix[x1][y1] + rez;
        }

        return dp[x1][x2][y1];
}

int main() {
    read_input();

    printf("%d", get_result(1, 1, 1));

    return 0;
}
