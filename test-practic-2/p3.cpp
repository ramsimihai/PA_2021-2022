#include <bits/stdc++.h>
using namespace std;

#define NMAX 200001
int albe[NMAX];
int n, m;

void read_input(int *minim, int *maxim)
{
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= n; i++) {
        cin >> albe[i];
        if (i == 1) {
            *minim = albe[i];
            *maxim = albe[i];
        } else {
            *minim = min(*minim, albe[i]);
            *maxim = max(*maxim, albe[i]);
        }
    }

}
int main(void)
{
    int maxim, minim;

    read_input(&minim, &maxim);

    int diff = 0;
    for (int i = 1; i <= n; i++) {
        // calcularea diferentei minime
        if (i != n) {
            diff = diff + abs(albe[i + 1] - albe[i]);
        }
    }

    if (minim != 1) {
        diff = diff + albe[1] - 1;
    }

    if (m > maxim) {
        diff = diff  + 1 - albe[n] + m;
    }

    printf("%d\n", diff);
    return 0;
}