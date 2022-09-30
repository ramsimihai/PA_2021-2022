#include <bits/stdc++.h>
using namespace std;

// folosita ca o litera dominanta pentru comparator
char letter;

class Task {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    int n;
    vector<string> words;
    unordered_map<char, int> characters;

    void read_input() {
        ifstream fin("statistics.in");
        fin >> n;

        for (int i = 0; i < n; i++) {
            string new_word;
            fin >> new_word;

            // se stocheaza toate literile diferite si numarul ei de aparitii
            int l = new_word.length();
            for (int i = 0; i < l; i++) {
                if (characters.count(new_word[i]) <= 0)
                    characters[new_word[i]] = 1;
                else
                    characters[new_word[i]]++;
            }

            words.push_back(new_word);
        }

        fin.close();
    }

    static bool comp(const string &word1, const string &word2) {
        int count_w1 = 0, count_w2 = 0;

        // folosite pentru reducerea apelarii de mai multe ori
        int word1_length = word1.length();
        int word2_length = word2.length();

        // se gaseste numarul de litere egale cu litera dominanta
        // cautata din primul cuvant
        for (int i = 0; i < word1_length; i++) {
            if (word1[i] == letter)
                count_w1++;
        }

        // se gaseste numarul de litere egale cu litera dominanta
        // cautata din al doilea cuvant
        for (int i = 0; i < word2_length; i++) {
            if (word2[i] == letter)
                count_w2++;
        }

        // se calculeaza diferenta dintre numarul de aparatii
        // a literei dominate si numarul de aparitii al literelor diferite
        // de aceasta
        int w1 = 2 * count_w1 - word1_length;
        int w2 = 2 * count_w2 - word2_length;

        return w1 > w2;
    }

    int get_result(char character) {
        // se sorteaza fiecare cuvant dupa diferenta dintre nr de aparatii
        // al literei dominante cautate si numarul de aparatii al literelor
        // diferite de aceasta
        sort(words.begin(), words.end(), comp);

        // count_ok_letter este numarul de aparitii al literei dominante
        // count_diff_letter este nr de aparatii al celorlalte litere
        // din cuvantul nou creat prin combinarea cuvintelor
        int max = 0, count_ok_letter = 0, count_diff_letter = 0;
        int no_words = 0;

        // se parcurge tot vectorul de cuvinte si se cauta numarul
        // maxim de numere care pot fi combinate incat sa existe
        // o litera dominanta
        for (int i = 0; i < n; i++) {
            int curr_count = 0;
            int curr_word_length = words[i].length();

            // se gaseste numarul de aparatii al literei dominante din
            // cuvantul actual
            for (int j = 0; j < curr_word_length; j++) {
                if (words[i].at(j) == letter)
                    curr_count++;
            }

            // se verifica daca cuvantul actual poate fi adaugat in cuvantul
            // nou creat sau nu
            if (count_ok_letter + curr_count > (max + curr_word_length) / 2) {
                count_ok_letter += curr_count;
                max += curr_word_length;
                no_words++;
            } else {
                break;
            }
        }

        return no_words;
	}

    void print_output() {
        ofstream fout("statistics.out");

        int max = -1;

        // se parcurg toate literele diferite si sunt initializate
        // ca litera dominanta, iar apoi se ruleaza algoritmul pe toate
        // posibilele litere dominante, rezultand nr maxim de cuvinte
        // care pot fi combinate in functie de o litera dominanta
        for (auto it = characters.begin(); it != characters.end(); ++it) {
            letter = it->first;
            int result = get_result(it->first);
            if (result > max) {
                max = result;
                if (max == n)
                    break;
            }
        }

        fout << max;

        fout.close();
    }
};


int main() {
    Task *task = new Task();
    task->solve();

    delete task;
    return 0;
}
