#include <cstdio>
#define NMAX 20 

using namespace std;

int n;
int visited[NMAX];
int sol[NMAX];

void print_sol() {
    for (int i = 1; i <= n; ++i) {
        printf("%d ", sol[i]);
    }
    printf("\n");
}

void backt(int step) {
    // pentru ca e numaru' primit + 1
    if (step == n + 1) {
        print_sol();
        return;
    }

    // iei cate un element de la 1 la n din domeniul
    // de alegeri posibile
    for (int i = 1; i <= n; ++i) {
        // validare daca n-a fost folosit
        if (visited[i]) {
            continue;
        }

        // pt fiecare element din domeniu verificare daca e valid in functie data
        if (step == 1 || (i % 2 != sol[step - 1] % 2)) {
            // adaugare la solutie
            visited[i] = true;
            sol[step] = i;
            backt(step + 1);
            // undo
            visited[i] = false;
        }
    }
}

int main() {
    scanf("%d", &n);
    if (n == 0) {
        printf("-1\n");
        return 0;
    }
    backt(1);

    return 0;
}