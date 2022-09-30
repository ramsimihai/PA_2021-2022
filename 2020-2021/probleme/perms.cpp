#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool check(vector<int>& solution) {
    return true;
}

void printSolution(vector<int>& solution) {
    for (auto s : solution) {
        cout << s << " ";
    }
    cout << "\n";
}

void back(int step, int stop, vector<int>& domain, vector<int>& solution, unordered_set<int>& visited) {
    if (step == stop) {

        if (check(solution)) {
            printSolution(solution);
        }
        return;
    }

    for (unsigned int i = 0; i < domain.size(); ++i) {
        if (visited.find(domain[i]) == visited.end()) {
            if ((domain[i] % 2 != solution[step - 1] % 2)) {
                visited.insert(domain[i]);

                solution[step] = domain[i];

                back(step + 1, stop, domain, solution, visited);
                visited.erase(domain[i]);
            }
        }
    }
}

int main(void) {
    int n;
    scanf("%d", &n);
    
    if (n == 0) {
        printf("-1\n");
        return 0;
    }

    vector<int> domain(n), solution(n);
    unordered_set<int> visited;

    for (int i = 0; i < n; ++i) {
        domain[i] = i + 1;
    }

    back(0, n, domain, solution, visited);
    return 0;
}

