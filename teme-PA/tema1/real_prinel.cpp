#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int n, k;
    vector<int> dist;
    vector<int> target;
    vector<int> awards;
    vector<vector<int>> dp;

    void read_input() {
        ifstream fin("prinel.in");
        fin >> n >> k;

        target.push_back(-1);
        awards.push_back(-1);

        // se citeste sirul de targets
        int max = -1;
        for (int i = 1; i <= n; i++) {
            int x;
            fin >> x;

            // calculeaza numarul maxim din target
            if (x > max)
                max = x;
            target.push_back(x);
        }

        // se citeste sirul de puncte
        for (int i = 1; i <= n; i++) {
            int x;
            fin >> x;
            awards.push_back(x);
        }

        // se redimensioneaza sirul de distante cat numarul
        // maxim cautat din target
        dist.resize(max + 1, 0);

        fin.close();
    }

    int get_result() {
        // se parcurge sirul de distante si se calculeaza numarul de operatii
        // pe care le face prinel pentru a ajunge din 1 pana la maximul
        // din target prin toti divizorii lui
        for (int i = 2; i < dist.size(); i++) {
            dist[i] = dist[i - 1] + 1;

            // parcurgem toti divizorii lui max(target) si toate elementele lui
            for (int div = 2; div * div <= i; div++) {
                if (i % div == 0) {
                    // se verifica daca se mai face o operatie pentru a ajunge
                    // in elementul respectiv printr-un divizor
                    if (dist[i - div] + 1 < dist[i])
                        dist[i] = dist[i - div] + 1;
                    if (dist[i - i / div] + 1 < dist[i])
                        dist[i] = dist[i - i / div] + 1;
                }
            }
        }

        // se parcurge sirul de distante si se verifica daca nu cumva
        // pot fi luate toate operatiile pe care prinel le face,
        // fara a mai calcula ulterior
        int total_dist = 0;
        int max_points = 0;
        for (int i = 1; i < target.size(); i++) {
            total_dist += dist[target[i]];
            max_points += awards[i];
        }

        if (total_dist <= k)
            return max_points;

        return rucsac();
	}

    int rucsac() {
        // lucram pe doar 2 linii
        dp.resize(2);

        for (int i = 0; i < 2; ++i) {
            dp[i].resize(k + 1);
        }

        // cazul de baza
        for (int cap = 0; cap <= k; ++cap) {
            dp[0][cap] = 0;
        }

        // cazul general
        for (int i = 1; i <= n; ++i) {
            for (int cap = 1; cap <= k; ++cap) {
                // nu se face obiectivul i, deci se ia raspunsul
                // de la pasul i - 1
                dp[i % 2][cap] = dp[(i - 1) % 2][cap];

                // daca mai am destule miscari disponibile, verific daca
                // nu cumva este avantajos sa fac obiectivul i
                if (cap - dist[target[i]] >= 0) {
                    dp[i % 2][cap] = max(
                           dp[i % 2][cap],
                           dp[(i - 1) % 2][cap - dist[target[i]]] + awards[i]);
                }
            }
        }

        return dp[n % 2][k];
    }

    void print_output() {
        ofstream fout("prinel.out");

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
