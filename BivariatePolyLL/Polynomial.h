/* 
 * The interface file for the bivariate polynomial 
 * class that is implemented using linked lists
 */

#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Term.h"
#include "Comparator.h"

class Polynomial
{
public:
	// Creates a zero polynomial, that is, 
	// the polynomial with no terms.
	Polynomial();

	// Creates a polynomial based on a list of terms
	// precondition: t is sorted based on the Comparator.
	// postcondition: Polynomial has a shallow copy of t
	Polynomial(Term *t);

	// Creates a polynomial by reading the terms from
	// the given file. The first number should represent
	// the number of terms in the polynomial, followed by
	// each term in the format [coeff x y], one per line.
	// Precondition: the stream has already been opened.
	Polynomial(std::ifstream &file);

	// Creates a deep copy of the other polynomial
	Polynomial(const Polynomial *other);

	// Differentiates the polynomial with respect
	// to x using the standard power rule
	void differentiateX();

	// Differentiates the polynomial with respect
	// to y using the standard power rule
	void differentiateY();

	// Overloaded assignment operator to create
	// a deep copy of the other polynomial
	Polynomial &operator=(const Polynomial &other);

	// Adds the polynomials termwise via merging and
	// returns the result. The additive identity is 
	// preserved, that is, 0 + 0 = 0 and p + 0 = p.
	const Polynomial operator+(const Polynomial &right);

	// Multiplies the polynomials termwise and merges
	// the products to form a new polynomial. The
   // domination law is preserved, that is, 0 * p = 0
	const Polynomial operator*(const Polynomial &right);

	// Outputs the polynomial to the output stream
	// in a nicely formatted fashion, outputs 0
	// for the zero polynomial.
	void print() const;

	// A function object with overloaded () operators that
	// returns either -1, 0, or 1 based on whatever criteria
	// is currently implemented in the Comparable class
	Comparator Compare;

private:
	// A helper function to apply the
	// power rule to differentiate the
	// list in terms of powers of x
	Term *dx(Term *list);

	// A helper function to apply the
	// power rule to differentiate the
	// list in terms of powers of y
	Term *dy(Term *list);

	// A helper function to sum the terms
	// of left and right non-destructively
	// postcondition: returns the head of the new list
	Term *add(Term *left, Term*right);

	// A helper function to mergesort a linked list
	// of terms destructively.
	// postcondition: returns the head of the sorted list
	Term *mergeSort(Term *t);

	// A helper function to merge two already sorted
	// linked lists of polynomial terms
	// Postcondition: returns the head of the merged list.
	Term *merge(Term *left, Term *right);

	// Returns a pointer to the middle of the linked
	// list pointed too by t so that it may be split
	// postcondition: returns a pointer to the middle
	Term *middle(Term *t);

	// Creates a deep copy of the linked list t
	// postcondition: returns a pointer to the first node in the list
	Term *copyTerms(Term *t);

	// Deletes every term in the linked list t
   // postcondition: all the memory is deallocated
	void deleteTerms(Term *t);

	// A pointer to the begining of the linked list
	// that will contain the sorted terms
	Term *terms;
};

// A constant for the zero polynomial
const Polynomial ZERO;
