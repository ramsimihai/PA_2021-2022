// A Memoization based program to find maximum collection
// using two traversals of a grid
#include<bits/stdc++.h>
using namespace std;
#define R 51
#define C 51

int arr[R][C];
int mem[R][C][C];

// checks whether a given input is valid or not
bool isValid(int x, int y1, int y2, int n, int m)
{
	return (x >= 0 && x < n && y1 >=0 &&
			y1 < m && y2 >=0 && y2 < m);
}

// Driver function to collect max value
int getMaxUtil(int x, int y1, int y2, int n, int m)
{
	/*---------- BASE CASES -----------*/
	// if P1 or P2 is at an invalid cell
	if (!isValid(x, y1, y2, n, m)) return INT_MIN;

	// if both traversals reach their destinations
	if (x == n-1 && y1 == m - 1 && y2 == m - 1)
	return (y1 == y2)? arr[x][y1]: arr[x][y1] + arr[x][y2];

	// If both traversals are at last row but not at their destination
	if (x == n-1) return INT_MIN;

	// If subproblem is already solved
	if (mem[x][y1][y2] != -1) return mem[x][y1][y2];

	// Initialize answer for this subproblem
	int ans = INT_MIN;

	// this variable is used to store gain of current cell(s)
	int temp = (y1 == y2)? arr[x][y1]: arr[x][y1] + arr[x][y2];

	/* Recur for all possible cases, then store and return the
	one with max value */
	ans = max(ans, temp + getMaxUtil(x+1, y1, y2-1, n, m));
	ans = max(ans, temp + getMaxUtil(x+1, y1, y2+1, n, m));
	ans = max(ans, temp + getMaxUtil(x+1, y1, y2, n, m));

	ans = max(ans, temp + getMaxUtil(x+1, y1-1, y2, n, m));
	ans = max(ans, temp + getMaxUtil(x+1, y1-1, y2-1, n, m));
	ans = max(ans, temp + getMaxUtil(x+1, y1-1, y2+1, n, m));

	ans = max(ans, temp + getMaxUtil(x+1, y1+1, y2, n, m));
	ans = max(ans, temp + getMaxUtil(x+1, y1+1, y2-1, n, m));
	ans = max(ans, temp + getMaxUtil(x+1, y1+1, y2+1, n, m));

	return (mem[x][y1][y2] = ans);
}

// This is mainly a wrapper over recursive function getMaxUtil().
// This function creates a table for memoization and calls
// getMaxUtil()
int geMaxCollection(int n, int m)
{
	// Create a memoization table and initialize all entries as -1
	memset(mem, -1, sizeof(mem));

	// Calculation maximum value using memoization based function
	// getMaxUtil()
	return getMaxUtil(0, 0, 0, n, m);
}

// Driver program to test above functions
int main()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }

	cout << geMaxCollection(n, m);
	return 0;
}
