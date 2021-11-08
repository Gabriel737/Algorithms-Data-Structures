/* 
 * The header file for the polynomial  
 * class that is implemented using a modified BST
 * in descending order, i.e. left > parent > right
 */

#include <iostream>
#include <string>
#include <cmath>

// This term structure is placed in the polynomial
// header file as it is a stripped down class that is
// only used for the purposes of managing the polynomial
struct Term
{
	int coeff;
	int x;
	Term *left;
	Term *right;
};

class Polynomial
{
public:
   // Creates a polynomial with zero terms,
   // i.e. the zero polynomial
	Polynomial();

   // Creates a deep copy of the polynomial p
   Polynomial(const Polynomial &p);

   // Destroys the polynomial and reclaims
   // all the memory taken by the terms
   ~Polynomial();

   // Overloaded assignment operator to 
   // create a deep copy of the other polynomial
   Polynomial &operator=(const Polynomial &other);

   // inserts a term with specified coefficient
   // and degree into the polynomial
   void insert(int coeff, int degree);

   // removes the term with the specified
   // degree if it exists
   void remove(int degree);

   // postcondition: returns true if this
   // polynomial is the ZERO polynomial
	bool is_zero() const;
   
   // postcondition: returns the polynomial evaluated at x
	int evaluate(int x) const;
   
   // postcondition: returns the coefficient at the specified
   // degree or zero if the term is not in the polynomial
	int coefficient_at(int degree) const;
   
   // postcondition: returns the degree of the polynomial
   // i.e., the degree of the highest term in the polynomial
	int degree() const;
   
   // postcondition: differentiates the polynomial with
   // respect to x using the standard power rule
	void differentiate_x();
   
   // overloaded operator to return the sum of two polynomials
   // p + 0  = p, 0 + p = 0, p + (-p) = 0
	friend const Polynomial operator+(const Polynomial &left, const Polynomial &right);
   
   // outputs the polynomial to the output stream passed
   // using the variable x and ^ to represent powers
   // nothing is printed if the polynomial is zero
   friend std::ostream &operator<<(std::ostream &out, const Polynomial &p);
   
   // reads a polynomial from the input stream passed
   // first, the number of terms are required, and then
   // the coefficient and power for each term, respectively
   friend std::istream &operator>>(std::istream &in, Polynomial &p);
   
   // A helper function to recursively traverse
   // the BST in order to write each term of the 
   // polynomial in descending order
   friend std::ostream &write_term(std::ostream &out, Term *node);

private:
   
   // A recursive helper function to insert a new node with the
   // specified coefficient and degree into the BST 
   // postcondition: returns a pointer to the root of the modified BST
	Term *insert_term(Term *node, int coeff, int degree);
   
   // A helper function to remove the term with the specified
   // degree if it exists in the polynomial
   // postcondition: returns a pointer to the root of the modified BST
	void delete_by_merging(Term *&node);

   // A recursive helper function that traverses preorder
   // to evaluate all the terms at the value x
	int evaluate_term(Term *node, int x) const;

   // A recursive helper function to differentiate each term
   // using the standard power rule: d/dx x^n = nx^n-1
   // postcondition: returns a pointer to the root of the modified BST
	Term *dx(Term *node);

   // A recursive helper function to make a deep
   // copy of every term in the polynomial
   // postcondition: returns a pointer to the root of the new BST
   Term *deep_copy(Term *node);   

   // A recursive helper function to delete
   // every term in the polynomial and to
   // deallocate all the claimed memory
   void delete_all(Term *node);

   // A pointer to the root of the BST which
   // contains all the terms of the polynomial
	Term *root;
};

// A constant for the zero polynomial
const Polynomial ZERO();
