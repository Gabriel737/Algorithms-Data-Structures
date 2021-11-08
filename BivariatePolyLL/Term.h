/* 
 * The implementation file for the
 * Term object for the Polynomial class
 */

#pragma once

class Term
{
	friend class Polynomial;
	friend struct Comparator;
public:
   // This code is inlined purposely as Term is a relatively lightweight class
   // and has no other implementation except for these simple constructors
	Term() {coeff = x = y = 0; next = nullptr;}
	Term(int a, int b, int c, Term* t) {coeff = a; x = b; y = c; next = t;}
private:
   int coeff, x, y;
	Term *next;
};
