#include <cstdio>
#define NMAX 16

int n;
int visited[NMAX];
int solution[NMAX];

void bkt(int step) {
    if (step == n + 1) {
        for (int i = 1; i <= n; ++i) {
            printf("%d ", solution[i]);
        }

        printf("\n");
        return;
    }

    for (int i = 1; i <= n; ++i) {
        if (visited[i]) {
            continue;
        }

        if (step == 1 || (i % 2 != solution[step - 1] % 2)) {
            visited[i] = true;
            solution[step] = i;
            bkt(step + 1);
            visited[i] = false;
        }
    }
}

bool check(int x1, int x2) {
    if (x1 % 2 != x2 % 2) {
        return true;
    }

    return false;
}

int main() {
    scanf("%d", &n);
    if (n == 0) {
        printf("-1\n");
        return 0;
    }

    bkt(1);

    return 0;
}