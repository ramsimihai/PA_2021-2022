#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int n, no_req;
    vector<int> dist;
    vector<int> requests;
    vector<vector<int>> dp;
    vector<int> sol;

    void read_input() {
        ifstream fin("regele.in");
        fin >> n;

        dist.push_back(-1);

        // se citesc distantele intre orase
        for (int i = 1; i <= n; i++) {
            int x;
            fin >> x;

            dist.push_back(x);
        }

        fin >> no_req;

        requests.push_back(-1);

        // se citesc numarul de negustori per interogare
        for (int i = 1; i <= no_req; i++) {
            int x;
            fin >> x;

            requests.push_back(x);
        }

        fin.close();
    }

    void get_result() {
        dp.resize(n + 1);

        for (int i = 0; i <= n; i++)
            dp[i].resize(n + 1);

        // dp[i][j] inseamna de cati negustori e nevoie pentru a activa
        // oricate j orase din primele i
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i < j) {
                    // nu poti activa mai multe orase decat exista
                    dp[i][j] = 0;

                } else if (i == 1) {
                    // pentru a activa primul oras trebuie sa activezi
                    // capatul din dreapta
                    dp[i][j] = max(dp[i - 1][j],
                                dp[i - 1][j - 1] + dist[i + 1] - dist[i]);

                } else if (i == n) {
                    // pentru a activa ultimul oras trebuie sa activezi
                    // capatul din stanga
                    if (i == j) {
                        // pentru a activa toate orasele pana la i se face
                        // diferenta dintre coord. extremitatilor
                        dp[i][j] = dist[i]  - dist[1];
                    } else {
                        dp[i][j] = max(dp[i - 1][j],
                                dp[i - 2][j - 1] + dist[i] - dist[i - 1]);
                    }
                } else if (i == j) {
                    // pentru a activa toate orasele pana la i se face
                    // diferenta dintre coord. extremitatilor
                    dp[i][j] = dist[i + 1]  - dist[1];

                } else {
                    // poti activa un oras prin activarea unui singur capat
                    int max1 = max(dp[i - 1][j],
                                dp[i - 1][j - 1] + dist[i + 1] - dist[i]);

                    // poti activa un oras prin activarea ambelor capete
                    // dar trebuie sarit ultimul oras
                    dp[i][j] = max(max1,
                                dp[i - 2][j - 1] + dist[i + 1] - dist[i - 1]);
                }
            }
        }

        // se apeleaza un binary search care cauta numarul maxim de negustori
        // mai mic decat un numar maxim de negustori dat pentru a activa
        // cate x (cat mai multe) orase
        for (int req = 1; req <= no_req; req++)
            sol.push_back(bsearch(requests[req]));
	}

    int bsearch(int val) {
        int left = 1, right = n;
        int pos = 0, mid;

        while (left <= right) {
            mid = (left + right) / 2;
            if (dp[n][mid] <= val) {
                pos = mid;
                left  = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return pos;
    }

    void print_output() {
        ofstream fout("regele.out");

        sol.push_back(0);
        get_result();

        for (int i = 1; i <= no_req; i++)
            fout << sol[i] << "\n";

        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
