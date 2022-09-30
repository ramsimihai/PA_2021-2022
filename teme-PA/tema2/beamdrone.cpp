// Copyright 2021 - 2022 - 321CA - Mihai Daniel Soare
#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 1001

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    //  n = nr de linii, m = linii de coloane din grid
    int n, m;
    // gridul 2d
    char adj[NMAX][NMAX];
    // o matrice de costuri aka distante de la nodul de start (drona)
    // pana la punctul de stop
    vector<vector<int>> costs;
    int x1, y1, x2, y2;

    void read_input() {
        ifstream fin("beamdrone.in");

        fin >> n >> m;
        fin >> x1 >> y1 >> x2 >> y2;

        // initializarile matricei de costuri
        costs.resize(n);
        for (int i = 0; i < n; i++) {
            costs[i].resize(m, 0);
        }

        // se citeste gridul
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char x;
                fin >> x;
                adj[i][j] = x;
            }
        }

        fin.close();
    }

    // verifica daca un punct din grid se mai afla in grid
    // nu este un perete, daca are costul mai bun decat noul cost sau este 0
    int is_valid(pair<int, int> node, int new_cost) {
        int x = node.first;
        int y = node.second;

        return (x >= 0 && x < n) && (y >= 0 && y < m) &&
                (adj[x][y] != 'W') &&
                (new_cost <= costs[x][y] || costs[x][y] == 0);
    }

    // un algoritm lee pentru umplerea matricei de distante dintr un punct pana
    // la un punct de finish, doar ca putin modificat. se vor lua doar
    // directiile perpendiculare ale nodurilor din coada si se va incerca
    // pana cand se va da de un perete
    int lee() {
        // se adauga nodul de inceput in coada, insa pe 2 directii diferite
        // atat la 0 grd cat si la 90* pentru ca nu a venit dintr-o directie
        // anume si poate pleca in orice directie
        queue<pair<pair<int, int>, int>> q;
        q.push({{x1, y1}, UP});
        q.push({{x1, y1}, RIGHT});

        // se parcurge lista
        while (!q.empty()) {
            // extragem nodul din coada
            auto elth = q.front();
            q.pop();

            pair<int, int> dest = elth.first;
            int direction = elth.second;

            int x = dest.first;
            int y = dest.second;
            int cost = costs[x][y];

            // se calculeaza directiile perpendiculare pe care poate merge
            // drona din punctul venit
            int dir1 = (direction + 1) % 4;
            int dir2 = (direction + 3) % 4;

            // se merge pe prima directie perpendiculara pana cand se da
            // de un perete sau de o pozitie invalida din grid
            while (true) {
                // se calculeaza urmatorul index pentru a merge mai departe
                // dinspre directia din care a venit nodul respectiv
                if (dir1 == UP) {
                    x--;
                } else if (dir1 == DOWN) {
                    x++;
                } else if (dir1 == RIGHT) {
                    y++;
                } else {
                    y--;
                }

                // se verifica daca un nod este valid, daca da se adauga in
                // coada, altfel se termina parcurgerea pe directia respectiva
                if (is_valid({x, y}, cost + 1)) {
                    costs[x][y] = cost + 1;
                    q.push({{x, y}, dir1});
                } else {
                    break;
                }
            }

            x = dest.first;
            y = dest.second;

            // se merge pe a doua directie din grid
            while (true) {
                if (dir2 == UP) {
                    x--;
                } else if (dir2 == DOWN) {
                    x++;
                } else if (dir2 == RIGHT) {
                    y++;
                } else {
                    y--;
                }

                if (is_valid({x, y}, cost + 1)) {
                    costs[x][y] = cost + 1;
                    q.push({{x, y}, dir2});
                } else {
                    break;
                }
            }
        }

        return costs[x2][y2] - 1;
    }

    void print_output() {
        ofstream fout("beamdrone.out");

        fout << lee();

        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
