// Copyright 2021 - 2022 - 321CA - Mihai Daniel Soare
#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 1001

// valoare mai mare decat orice distanta din graf
#define INF (1 << 30)

// cele 4 directii pe care poate merge un robotel in grid
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

// exista maxim 8 obiecte pe harta - 4 roboti si 4 suprafete de curatat
#define MAX_OBJ 9

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    // n = numar de linii, m = numar de coloane
    int n, m;
    // grid-ul dat ca input
    char adj[NMAX][NMAX];
    // matrice de costuri in care se pune distanta minima de la
    // un nod start
    vector<vector<int>> costs;
    // sir de roboti cu indexii lor
    vector<pair<int, int>> robots;
    // sir de suprafete patruite cu indexii lor
    vector<pair<int, int>> dust;
    // matrice de distante de la fiecare obiect de pe harta
    // robot -> robot, robot -> supr. prafuita, supr. -> supr.
    int robo_dist[MAX_OBJ][MAX_OBJ];

    void read_input() {
        ifstream fin("curatare.in");
        fin >> n >> m;

        // se initializeaza matricea de costuri
        costs.resize(n);
        for (int i = 0; i < n; i++) {
            costs[i].resize(m, 0);
        }

        // se citeste gridul si se adauga robotii si suprafetele de curatat
        // in vectori
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                char x;
                fin >> x;
                adj[i][j] = x;
                if (x == 'S') {
                    dust.push_back(make_pair(i, j));
                } else if (x == 'R') {
                    robots.push_back(make_pair(i, j));
                }
            }
        }

        fin.close();
    }

    // verifica daca un nod se afla sau nu in grid
    int is_valid(pair<int, int> node) {
        int x = node.first;
        int y = node.second;

        return (x >= 0 && x < n) && (y >= 0 && y < m)
                && (adj[x][y] != 'X') && (costs[x][y] == 0);
    }

    // lee simplu care calculeaza un nod sursa la toate celelalte
    // prin cele 4 directii posibile
    void lee(pair<int, int> start) {
        // se reinitializeaza matricea de costuri
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                costs[i][j] = 0;
            }
        }

        queue<pair<int, int>> q;
        q.push(start);

        // se itereaza prin nodurile din coada
        // pentru fiecare directie se calculeaza costul muchiei si
        // se adauga nodul in coada;
        while (!q.empty()) {
            auto elth = q.front();
            q.pop();
            int x = elth.first;
            int y = elth.second;

            // pentru directia: UP
            if (is_valid({x - 1, y})) {
                costs[x - 1][y] = costs[x][y] + 1;
                q.push({x - 1, y});
            }

            // pentru directia: DOWN
            if (is_valid({x + 1, y})) {
                costs[x + 1][y] = costs[x][y] + 1;
                q.push({x + 1, y});
            }

            // pentru directia: RIGHT
            if (is_valid({x, y + 1})) {
                costs[x][y + 1] = costs[x][y] + 1;
                q.push({x, y + 1});
            }

            // pentru directia: LEFT
            if (is_valid({x, y - 1})) {
                costs[x][y - 1] = costs[x][y] + 1;
                q.push({x, y - 1});
            }
        }
    }

    // genereaza distributia tuturor obiectelor de pe harta
    // adica distanta minima de la un robot pana la o suprafata
    // un robot pana la un robot si o suprafata pana la o supr.
    void generate_objects_dist() {
        // se initializeaza matricea
        // va avea pe idx-urile i = [1, 4] | j = [1, 4] doar distante intre
        // roboti <-> roboti
        // i = [1, 4] | j = [5, 8] doar distante intre roboti <-> suprafete
        // i = [5, 8] | j = [5, 8] doar distante intre suprafete <-> suprafete
        for (int i = 1; i < MAX_OBJ; i++) {
            for (int j = 1; j < MAX_OBJ; j++) {
                robo_dist[i][j] = 0;
            }
        }

        // distante pentru fiecare robot pana la fiecare robot si
        // pana la fiecare suprafata prafuita
        for (int i = 0; i < robots.size(); i++) {
            // se calculeaza cu aj. alg lui lee toate costurile
            // dintr-un robot
            lee(robots[i]);

            // se itereaza prin lista de suprafete si se adauga
            // costul de la robot pana la supr
            for (int j = 0; j < dust.size(); j++) {
                int x = dust[j].first;
                int y = dust[j].second;
                robo_dist[i + 1][j + 5] = costs[x][y];
            }

            // se itereaza prin lista de suprafete si se adauga
            // costul de la robot pana la alt robot
            for (int j = 0; j < robots.size(); j++) {
                if (robots[i] != robots[j]) {
                    int x = robots[j].first;
                    int y = robots[j].second;
                    robo_dist[i + 1][j + 1] = costs[x][y];
                }
            }
        }

        // se calculeaza distanta de la fiecare supr pana la fiecare supr
        for (int i = 0; i < dust.size(); i++) {
            lee(dust[i]);
            for (int j = 0; j < dust.size(); j++) {
                if (dust[i] != dust[j]) {
                    int x = dust[j].first;
                    int y = dust[j].second;
                    robo_dist[i + 5][j + 5] = costs[x][y];
                }
            }
        }
    }

    // array de distributie de suprafete de curatat
    // tuturor robotilor de pe grid
    vector<vector<int>> distribution;
    int visited[4];
    // distanta minima dintre toate incercarile de bkt
    int minim_distr = INF;

    // se genereaza toate posibilitatile de distributie ale suprafetelor
    // de curatat catre toti robotii disponibili
    void backt() {
        int done = 1;
        // s-a generat toata solutia
        for (int i = 0; i < dust.size(); i++) {
            if (!visited[i]) {
                done = 0;
                break;
            }
        }

        if (done) {
            // se calculeaza maximul dintre cele no_robots distributii
            int max_dist = -1;
            for (int i = 0; i < distribution.size(); i++) {
                if (distribution[i].size() == 0) {
                    continue;
                }

                // se calculeaza costul de la robot la prima suprafata
                int cost = robo_dist[i + 1][distribution[i][0] + 5];
                // si dupa se calculeaza costul de la o suprafata la alta
                for (int j = 0; j < distribution[i].size(); j++) {
                    if (j + 1 < distribution[i].size()) {
                        int x = distribution[i][j] + 5;
                        int y = distribution[i][j + 1] + 5;
                        cost += robo_dist[x][y];
                    }
                }

                // se verifica daca e costul maxim pentru fiecare distributie
                // ale robotilor
                if (cost > max_dist) {
                    max_dist = cost;
                }
            }

            // se verifica dupa generarea solutiei daca nu cumva distributia
            // este minima
            if (minim_distr > max_dist) {
                minim_distr = max_dist;
            }
        }

        // se genereaza fiecare solutie
        for (int i = 0; i < dust.size(); ++i) {
            for (int j = 0; j < robots.size(); ++j) {
                if (visited[i]) {
                    continue;
                }

                // se marcheaza pasul facut
                visited[i] = true;
                distribution[j].push_back(i);

                backt();

                // se retrage pasul facut
                distribution[j].pop_back();
                visited[i] = false;
            }
        }
    }

    void print_output() {
        ofstream fout("curatare.out");

        for (int i = 0; i < 4; i++) {
            visited[i] = 0;
        }

        distribution.resize(robots.size());

        generate_objects_dist();

        backt();

        fout << minim_distr;

        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
