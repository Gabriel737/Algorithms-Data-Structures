/* 
 * A tester program for the 
 * bivariate polynomial and term class
 */

#include "Polynomial.h"

using std::cout;
using std::endl;
using std::ifstream;

int main()
{
	ifstream myfile;
	myfile.open("input.txt");

	cout << "*** Constructor Testing ***" << endl;
	Polynomial p(myfile);
	cout << "p = ";
	p.print();

	Polynomial q(myfile);
	cout << "q = ";
	q.print();

	Polynomial r(myfile);
	cout << "r = ";
	r.print();

	Polynomial s(myfile);
	cout << "s = ";
	s.print();
	
	// the zero polynomial
	Polynomial t;
	cout << "t = ";
	t.print();

	cout << "\n*** Addition Testing ***" << endl;

	cout << "p + q = ";
	(p + q).print();

	cout << "q + r = ";
	(q + r).print();

	cout << "r + s = ";
	(r + s).print();

	cout << "s + t = ";
	(s + t).print();

	cout << "t + p = ";
	(t + p).print();

	cout << "\n*** Multiplication Testing ***" << endl;

	cout << "p * q = ";
	(p * q).print();

	cout << "q * r = ";
	(q * r).print();

	cout << "r * s = ";
	(r * s).print();

	cout << "s * t = ";
	(s * t).print();

	cout << "t * p = ";
	(t * p).print();

	cout << "\n*** Differentiation Testing ***" << endl;

	cout << "d/dx(p) = ";
	p.differentiateX();
	p.print();

	cout << "d/dy(q) = ";
	q.differentiateY();
	q.print();

	cout << "d/dx(r) = ";
	r.differentiateX();
	r.print();

	cout << "d/dy(s) = ";
	s.differentiateY();
	s.print();

	cout << "d/dx(t) = ";
	t.differentiateX();
	t.print();

	cout << "\n*** Big Three Testing ***" << endl;

	Polynomial newP(p), newQ(q), newR(r), newS(s), newT(t);
	cout << "newP = ";
	newP.print();
	cout << "newQ = ";
	newQ.print();
	cout << "newR = ";
	newR.print();
	cout << "newS = ";
	newS.print();
	cout << "newT = ";
	newT.print();
   
	cout << "p = q = ";
	(p = q).print();

	cout << "p = r = ";
	(p = r).print();

	cout << "p = s = ";
	(p = s).print();

	cout << "p = t = ";
	(p = t).print();

	myfile.close();
	return 0;
}
