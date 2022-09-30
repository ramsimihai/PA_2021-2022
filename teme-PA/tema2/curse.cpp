// Copyright 2021 - 2022 - 321CA - Mihai Daniel Soare
#include <bits/stdc++.h>
using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    // p = nr de piste, m = nr de masini, a = nr de antrenamente
    int p, m, a;
    // un array de set-uri neordonate pentru a pastra graful de antr.
    vector<unordered_set<int>> trainings;
    // vector de grade interne folosit in alg. lui khan
    vector<int> grad;

    void read_input() {
        ifstream fin("curse.in");

        fin >> p >> m >> a;

        // initializari
        grad.resize(m + 1, 0);
        vector<int> last_training(p + 1, 0);
        vector<int> new_training(p + 1, 0);
        trainings.resize(m + 1);

        // se citeste primul antrenament
        for (int i = 1; i <= p; i++) {
            int nr;
            fin >> nr;
            last_training[i] = nr;
        }

        for (int j = 0; j < a - 1; j++) {
            int valid_check = 0;
            // se citeste un nou antrenament
            for (int i = 1; i <= p; i++) {
                int nr;
                fin >> nr;
                new_training[i] = nr;

                // verificam daca este valida conditia
                if (last_training[i] != new_training[i] && valid_check == 0) {
                    valid_check = 1;
                    int ok = 1;

                    // se verifica ca nu exista deja conditia in graf
                    if (trainings[last_training[i]].find(new_training[i])
                            != trainings[last_training[i]].end()) {
                        ok = 0;
                    }

                    // se adauga in graf nodurile care au conditii valide
                    // si se modifica gradul pentru nodurile in care intra
                    // muchii
                    if (ok == 1) {
                        grad[new_training[i]]++;
                        trainings[last_training[i]].insert(new_training[i]);
                    }
                }

                last_training[i] = new_training[i];
            }
        }
        fin.close();
    }

    // implementare clasica de topological sort pe un graf format
    // din conditiile extrase
    void get_result() {
        vector<int> topsort;
        queue<int> q;

        // pentru fiecare nod care are grad intern 0
        // adaugam in coada
        for (int i = 1; i <= m; i++) {
            if (!grad[i]) {
                q.push(i);
            }
        }

        // parcurgem coada
        while (!q.empty()) {
            // se extrage elementul
            int x = q.front();
            q.pop();
            // se adauga in solutie elth. extras
            topsort.push_back(x);

            // se parcurge sirul de muchii pentru nodul x
            unordered_set<int>::iterator itr;
            for (itr = trainings[x].begin(); itr != trainings[x].end(); itr++) {
                int y = *itr;
                grad[y]--;

                if (!grad[y]) {
                    q.push(y);
                }
            }
        }

        ofstream fout("curse.out");

        // se afiseaza drumul scos in urma sortarii topologice
        for (int i = 0; i < topsort.size(); i++) {
            fout << topsort[i] << " ";
        }

        fout.close();
    }

    void print_output() {
        get_result();
    }
};

int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
