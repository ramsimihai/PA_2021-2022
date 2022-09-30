#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> all_characters;

bool resolve_task1()
{
    all_characters.clear();
    string word;
    cin >> word;

    for (int i = 0; i < word.size(); i++) {
        if (all_characters.find(word[i]) == all_characters.end()) {
            all_characters[word[i]] = 1;
        } else {
            all_characters[word[i]]++;
        }
    }

    int ok = 0;
    for (auto i = all_characters.begin(); i != all_characters.end(); i++) {
        if (i->second % 2 == 1) {
            if (ok == 1) {
                return false;
            } else {
                ok = 1;
            }
        }
    }

    return true;
}

bool resolve_task2()
{
    all_characters.clear();

    string word1, word2;
    cin >> word1 >> word2;
    vector<char> freq1;
    vector<char> freq2;
    freq1.clear();
    freq2.clear();
    
    freq1.assign('z' - 'a' + 1, 0);
    freq2.assign('z' - 'a' + 1, 0);
    for (int i = 0; i < word1.size(); i++) {
        freq1['z' - word1[i]]++;
    }

    for (int i = 0; i < word2.size(); i++) {
        freq2['z' - word2[i]]++;
    }

    sort(freq1.begin(), freq1.end());
    sort(freq2.begin(), freq2.end());

    for (int i = 0; i < freq1.size(); i++) {
        if (freq1[i] != freq2[i]) {
            return false;
        }
    }

    return true;
}

void read_input()
{
    int no_tasks;
    cin >> no_tasks;

    for (int i = 0; i < no_tasks; i++) {
        int x;
        cin >> x;
        if (x == 1) {
            cout << resolve_task1();
        } else {
            cout << resolve_task2();
        }
    }
}

int main(void)
{
    read_input();
    return 0;
}