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
    int n, l;
    vector<char> key;
    vector<char> substring;
    vector<vector<int>> dp;

    void read_input() {
        ifstream fin("crypto.in");
        fin >> n >> l;

        key.push_back(' ');
        substring.push_back(' ');

        // se citeste cheia
        for (int i = 1; i <= n; i++) {
            char x;
            fin >> x;

            key.push_back(x);
        }

        // se citeste subsirul din cheie
        for (int i = 1; i <= l; i++) {
            char x;
            fin >> x;

            substring.push_back(x);
        }

        fin.close();
    }

    int get_result() {
        int powth = 0, no_diff_lett = 0;

        dp.resize(l + 1);
        for (int i = 0; i <= l; i++)
            dp[i].resize(n + 1);

        // se creeaza un vector de frecventa pentru a calcula numarul
        // de litere diferite din subsir
        vector<char> freq('z' - 'a' + 1);
        for (int i = 1; i <= l; i++) {
            if (freq[substring[i] - 'a'] != 1) {
                freq[substring[i] - 'a'] = 1;
                no_diff_lett++;
            }
        }

        // cazul de baza este reprezentat din prima linie pentru care putem
        // calcula numarul maxim de litere diferite care pot aparea
        // in calcularea numarului de subsecvente in functie de cate semne
        // de ? apar in cheie
        powth = 1;
        for (int i = 0; i <= n; i++) {
            if (key[i] == '?')
                powth = ((long long) powth) * no_diff_lett % MOD;

            dp[0][i] = powth;
        }

        // i este indexul curent din substring, iar j este indexul
        // curent din cheie
        for (int i = 1; i <= l; i++) {
            for (int j = 1; j <= n; j++) {
                // daca ultimele litere din subsiruri coincid atunci
                // se pot adauga la subsecventa curenta sau se poate ignora
                // si trece mai departe
                if (key[j] == substring[i]) {
                    dp[i][j] = ((long long) dp[i][j - 1] +
                                dp[i - 1][j - 1]) % MOD;
                } else if (key[j] == '?') {
                    // daca a fost gasit un semn ?, atunci toate subsecventele
                    // existente pana atunci vor fi luate de numarul de litere
                    // diferite ori si se considera si noile subsecvente care
                    // se pot forma cu semnul ?
                    dp[i][j] = ((long long) no_diff_lett * dp[i][j - 1]
                                % MOD + dp[i - 1][j - 1]) % MOD;
                } else {
                    // daca ultimele litere din subsiruri nu coincid, atunci
                    // se ignora
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }

        return dp[l][n];
	}

    void print_output() {
        ofstream fout("crypto.out");

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
