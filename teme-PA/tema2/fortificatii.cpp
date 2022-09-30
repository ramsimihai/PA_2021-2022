// Copyright 2021 - 2022 - 321CA - Mihai Daniel Soare
#include <bits/stdc++.h>
using namespace std;

// numarul maxim de noduri
#define NMAX 100001

// valoare mai mare decat orice distanta din graf
#define INF 0x7FFFFFFFFFFFFFFF

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    // n = numar de noduri, m = numar de muchii, k = nr fortificatii
    // b = numar de localitati de barbari
    int n, m, k, b;
    // vector de frecventa pentru fiecare nod din graf, daca nu cumva este
    // o localitate de barbar
    bool is_barb[NMAX];
    // matricea grafului care contine si costul muchiei respective
    vector<pair<int, int>> adj[NMAX];
    // priority queue folosit pentru alg. lui dijkstra
    priority_queue<pair<long long, int>> queue;
    // un vector de distante de la localitatile de barbari
    // pana la capitala
    vector<long long> distances;

    void read_input() {
        ifstream fin("fortificatii.in");
        fin >> n >> m >> k >> b;

        // se citesc localitatile de barbari
        for (int i = 0; i < b; i++) {
            int b_idx;
            fin >> b_idx;
            is_barb[b_idx] = true;
        }

        // se citesc muchiile din graf
        for (int i = 1; i <= m; i++) {
            int x, y, t;
            fin >> x >> y >> t;
            adj[x].push_back({y, t});
            adj[y].push_back({x, t});
        }

        fin.close();
    }

    long long get_result() {
        int i, x, y;
        long long cost;

        // initializari
        vector<long long> d(n + 1, INF);
        vector<int> visited(n + 1, 0);

        // se introduce in priority queue nodul sursa
        queue.push(make_pair(0, 1));
        d[1] = 0;

        // se parcurge coada de prioritati
        while (!queue.empty()) {
            while (!queue.empty() && visited[queue.top().second]) {
                queue.pop();
            }

            // se extrage primul nod din coada
            x = queue.top().second;
            visited[x] = 1;

            // se parcurg vecinii nodului din coada
            for (i = 0; i < adj[x].size(); i++) {
                y = adj[x][i].first;
                cost = adj[x][i].second;

                // se relaxeaza muchiile daca nu sunt noduri reprezentate
                // de barbari
                if (d[y] > d[x] + cost && is_barb[x] == 0) {
                    d[y] = d[x] + cost;
                    queue.push(make_pair(-d[y], y));
                }
            }
        }

        // se parcurge vectorul de distante si se initializeaza cu -1
        // nodurile de barbari sau care nu au fost vizitate
        for (i = 1; i <= n; i++) {
            auto is_barbarian = is_barb[i];
            if (d[i] == INF || is_barbarian == 1) {
                d[i] = -1;
            }

            if (is_barbarian == 1) {
                visited[i] = 0;
            }
        }

        // se parcurge fiecare nod si se verifica daca este barbar,
        // daca da, se trece prin fiecare vecin al barbarului si daca nu este
        // nod de barbar
        for (int node = 1; node <= n; node++) {
            if (is_barb[node] == 1) {
                for (int i = 0; i < adj[node].size(); i++) {
                    // se adauga intr-un array distanta de la sursa pana la
                    // vecin si costul muchiei dintre barbar si vecin
                    auto neigh = adj[node][i].first;
                        if (visited[neigh] != 0) {
                        long long best_dist = d[neigh] + adj[node][i].second;
                        distances.push_back(best_dist);
                    }
                }
            }
        }

        // sortam vectorul de distante dintre barbari si sursa
        sort(distances.begin(), distances.end());

        // marim pe rand numarul de fortificatii pe care le punem in functie
        // de cate drumuri am luat in calcul
        int count = 1;
        for (int i = 0; i < distances.size() - 1; i++) {
            // numarul de fortificatii care trebuie adaugate pentru a fi
            // la acelasi nivel
            long long factor = distances[i + 1] - distances[i];
            // daca se pot pune fortificatii
            if (count * factor < k) {
                distances[i] += factor;
                k -= count * factor;
                count++;
            } else {
                // daca nu se pot pune fortificatii
                return distances[i] + k / count;
            }
        }

        // s-a parcurs tot vectorul de distante
        if (k != 0) {
            return distances[distances.size() - 1] + k / count;
        } else {
            return distances[distances.size() - 1];
        }
    }

    void print_output() {
        ofstream fout("fortificatii.out");

        fout << get_result();

        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
