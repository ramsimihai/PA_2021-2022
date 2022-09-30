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
    vector<pair<int, int>> points;

    void read_input() {
        ifstream fin("walsh.in");
        fin >> n >> k;

        // se citeste intr-un vector de perechi (x, y) care vor fi cautate
        for (int i = 0; i < k; i++) {
            int x, y;
            fin >> x >> y;

            points.push_back(make_pair(x, y));
        }

        fin.close();
    }

    int solve(int n, int x, int y) {
        // daca matricea ajunge de 2x2 putem sa dam return
        // la valoarea respectiva in functie de coordonatele la care
        // s-a ajuns
        if (n == 2) {
            if (x == 2 && y == 2)
                return 1;

            return 0;
        }

        if ((x >= 1 &&  x <= n / 2) && (y >= 1 && y <= n / 2)) {
            // cadranul stanga-sus
            return solve(n >> 1, x, y);
        } else if ((x >= 1 &&  x <= n / 2) && (y >= n / 2 + 1 && y <= n)) {
            // cadranul dreapta-sus
            return solve(n >> 1, x, y - (n >> 1));
        } else if ((x >= n / 2 + 1 &&  x <= n) && (y >= 1 && y <= n / 2)) {
            // cadranul stanga-jos
            return solve(n >> 1, x - (n >> 1), y);
        } else if ((x >= n / 2 + 1 &&  x <= n) && (y >= n / 2 + 1 && y <= n)) {
            // cadranul dreapta-jos in care se intoarce
            // valoarea negata
            return !solve(n >> 1, x - (n >> 1), y - (n >> 1));
        }

        // nu se ajunge niciodata aici
        return 1;
    }

    int get_result(int n, int x, int y) {
        return solve(n, x, y);
	}

    void print_output() {
        ofstream fout("walsh.out");

        for (int i = 0; i < k; i++)
            fout << get_result(n, points[i].first, points[i].second) << "\n";

        fout.close();
    }
};


int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
