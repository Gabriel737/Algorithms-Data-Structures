/* 
 * A program to find all solutions to
 * a N by N magic square
 */

#include <iostream>

using std::cout;
using std::endl;

// N is the size of the square
const int N = 3;

// MAX is the dimension of the square
const int MAX = N * N;

// A  constant to indicate that the space is empty
const int NONE = 0;

// The solution to the magic square, 
// which is determined by n(n^2+1)/2
// 3 by 3 = 15
// 4 by 4 = 34
const int SOLUTION = N * (N * N + 1) / 2;

// Finds all possible solutions to an N by N
// magic square with each row, column, and
// diagonal summing up to the SOLUTION
// pre: N > 0, SOLUTION > 0
// post: outputs all possible solutions to 
// the standard output, cout
void solve();

// This is a helper function that processes each
// candidate solution at the specified row and column
// *see original function for documentation
void solve(int square[][N], bool digits[], int row, int col);

// Checks if the square is in a valid row state
// post: returns true if all fully completed rows
// sum up to the SOLUTION or if the square is
// a possible candidate to being a solution
bool rowsValid(int square[][N]);

// Checks if the square is in a valid row state
// post: returns true if all fully completed rows
// sum up to the SOLUTION or if the square is
// a possible candidate to being a solution
bool columnsValid(int square[][N]);

// Checks if the square is in a valid column state
// post: returns true if all fully completed columns
// sum up to the SOLUTION or if the square is
// a possible candidate to being a solution
bool diagonalsValid(int square[][N]);

// Checks if the square is in a valid diagonal state
// post: returns true if all fully completed diagonals
// sum up to the SOLUTION or if the square is
// a possible candidate to being a solution

// Outputs the square in MATLAB format
// to the standard output, cout
void print(int square[][N]);

int main()
{
	cout << "*** Magic Square Solver by Gabriel Henderson ***" << endl;
	cout << "N = " << N << " Solution = " << SOLUTION << endl << endl;
	solve();
	return 0;
}

void solve()
{
	int square[N][N];
	bool digits[MAX + 1];

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			square[i][j] = NONE;
		}
	}

	for(int k = 0; k <= MAX; k++)
	{
		digits[k] = false;
	}

	solve(square, digits, 0, 0);
}

void solve(int square[][N], bool digits[], int row, int col)
{
	if(row >= N || col >= N)
	{
		return;
	}

	for(int candidate = 1; candidate <= MAX; candidate++)
	{
		// this number has already been placed, move on
		if(digits[candidate])
		{
			continue;
		}

		// place this number and check if it is valid
		square[row][col] = candidate;
		digits[candidate] = true;

		if(rowsValid(square) && columnsValid(square) && diagonalsValid(square))
		{
			// the placements are valid and the board is full, were done
			if(row == N - 1 && col == N - 1)
			{
				print(square);
			}

			// so far so good, keep going
			else
			{
				solve(square, digits, row + ((col + 1) / N), (col + 1) % N);
			}
		}

		// the places are invalid or we have already found a solution, 
		// unplace the digit, backtrack, and keep trying other digits
		square[row][col] = NONE;
		digits[candidate] = false;
	}
}

bool rowsValid(int square[][N])
{
	int sum;
	bool incomplete;

	for(int i = 0; i < N; i++)
	{
		sum = 0;
		incomplete = false;
		for(int j = 0; j < N; j++)
		{
			if(square[i][j] == NONE)
			{
				incomplete = true;
			}
			sum += square[i][j];
		}

		// if the row is complete and does not sum up
		// to the solution, this row is not a solution
		if(!incomplete && sum != SOLUTION)
		{
			return false;
		}

		// if the candidate solution's row sums up to
		// something greater than the solution then this 
		// candidate is not a solution
		if(sum > SOLUTION)
		{
			return false;
		}
	}

	return true;
}

bool columnsValid(int square[][N])
{
	int sum;
	bool incomplete;

	for(int i = 0; i < N; i++)
	{
		sum = 0;
		incomplete = false;
		for(int j = 0; j < N; j++)
		{
			if(square[j][i] == NONE)
			{
				incomplete = true;
			}
			sum += square[j][i];
		}

		// if the column is complete and does not sum up
		// to the solution, this row is not a solution
		if(!incomplete && sum != SOLUTION)
		{
			return false;
		}

		// if the candidate solution's column sums up to
		// something greater than the solution then this 
		// candidate is not a solution
		if(sum > SOLUTION)
		{
			return false;
		}
	}

	return true;
}

bool diagonalsValid(int square[][N])
{
	int leftSum = 0, rightSum = 0;
	bool incomplete = false;

	for(int i = 0, j = 0; i < N && j < N; i++, j++)
	{
		 if(square[i][j] == NONE || square[N - i - 1][j] == NONE)
		 {
			 incomplete = true;
		 }
		 leftSum += square[i][j];
		 rightSum += square[N - i - 1][j];
	}

	// if either of the diagonals are not equal to the solution
	// then this candidate is not a solution
	if(!incomplete && (leftSum != SOLUTION || rightSum != SOLUTION))
	{
		return false;
	}

	// if the either of the candidates diagonals are greater
	// than the solution, this candidate is not a solution
	if(leftSum > SOLUTION || rightSum > SOLUTION)
	{
		return false;
	}
	
	return true;
}

void print(int square[][N])
{
	cout << "Sol =" << endl;

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout << "\t" << square[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
