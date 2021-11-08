/* 
 * The tester file for the polynomial  
 * class that is implemented using a modified BST
 * in descending order, i.e. left > parent > right
 */

#include <iostream>
#include <limits>
#include "Polynomial.h"

using std::cin;
using std::cout;
using std::endl;

const int MAX_TEST_CASES = 1000;

// Fills the polynomial array P with up to
// MAX_TEST_CASES polynomials
// postcondition: returns the size of the array
int get_test_cases(Polynomial P[]);

// Tests all operations of the polynonimals
// contained within the array P
void test_operations(Polynomial P[], int n);

int main()
{
   int number_of_cases;
   Polynomial cases[MAX_TEST_CASES];
   
   cout << "*** PolynomialTester by Gabriel Henderson ***" << endl;
   cout << "This program will allow you to test up to " << MAX_TEST_CASES << " polynomials."<< endl;
   
   number_of_cases = get_test_cases(cases);
   test_operations(cases, number_of_cases);

	return 0;
}

int get_test_cases(Polynomial P[])
{
   int n;
   cout << "Enter the number of test cases: ";
   cin >> n;
   cout << "For each polynomial, enter the # of terms followed by each terms coefficent and power." << endl;
   
   for(int i = 0; i < n && i < MAX_TEST_CASES; i++)
      cin >> P[i];
   
   return n;
}

void test_operations(Polynomial P[], int n)
{
   for(int i = 0; i < n; i++)
   {
      // select one case and test assignment operator
      Polynomial p = P[i]; 
      // copy constructor - will use later for differentiation too
      Polynomial x(p);
      cout << "*** Test case " << i + 1 << "; P(x) = "<< p << "***" << endl;
      cout << "Assignment operator = " << p << endl;
      cout << "Copy constructor = " << x << endl;
      p.insert(1, 0);
      cout << "Inserting 1 = " << p << endl;
      p.insert(2, 5);
      cout << "Inserting 2x^5 = " << p << endl;
      p.remove(0);
      cout << "Removing the constant term = " << p << endl;
      p.remove(5);
      cout << "Removing term with degree 5 = " << p << endl;
      cout << "Does P(x) = 0? " << p.is_zero() << endl;
      cout << "P(0) = " << p.evaluate(0) << endl;
      cout << "P(1) = " << p.evaluate(1) << endl;
      cout << "Constant coefficient = " << p.coefficient_at(0) << endl;
      cout << "Coefficient at x^2 = " << p.coefficient_at(2) << endl;
      cout << "Degree of P(x) = " << p.degree() << endl;
      // select the next two polynomials to test addition
      cout << "P(x) " << P[(i + 1) % n] << " = "<< p + P[(i + 1) % n] << endl;
      cout << "P(x) " << P[(i + 2) % n] << " = "<< (p + P[(i + 2) % n]) << endl;
      p.differentiate_x();
      cout << "dP/dx = " << p << endl << endl;
   }
}