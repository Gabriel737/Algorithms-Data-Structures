/* 
 * The implementation file for the bivariate polynomial  
 * class that is implemented using linked lists
 */

#include "Polynomial.h"

using std::cout;
using std::cerr;
using std::endl;

Polynomial::Polynomial()
{
	terms = nullptr;
}

Polynomial::Polynomial(Term *t)
{
	terms = t;
}

Polynomial::Polynomial(std::ifstream &file)
{
	if(!file.is_open())
	{
		cerr << "Error in Polynomial(std::ifstream&): File is not open.";
		exit(1);
	}

	int n, coeff, x, y;
	file >> n >> coeff >> x >> y;
	terms = new Term(coeff, x, y, nullptr);
	Term *current = terms;
	--n;

	while(!file.eof() && n > 0)
	{
		file >> coeff >> x >> y;
		current->next = new Term(coeff, x, y, nullptr);
		current = current->next;
		--n;
	}

	terms = mergeSort(terms);
}

Polynomial::Polynomial(const Polynomial *other)
{
	terms = copyTerms(other->terms);
}

void Polynomial::differentiateX()
{
	terms = dx(terms);
}

void Polynomial::differentiateY()
{
	terms = dy(terms);
}

Polynomial &Polynomial::operator=(const Polynomial &other)
{
	if(&other != this)
	{
		deleteTerms(terms);
		terms = copyTerms(other.terms);
	}

	return *this;
}

const Polynomial Polynomial::operator+(const Polynomial &right)
{
	return Polynomial(add(this->terms, right.terms));
}

const Polynomial Polynomial::operator*(const Polynomial &right)
{
	if(this->terms == nullptr || right.terms == nullptr)
		return Polynomial();

	Term *result = nullptr;
	Term *leftCurrent = this->terms;

	// expand out the polynomials one term at a time
	while(leftCurrent != nullptr)
	{
		Term *rightCurrent = right.terms;
		//multiply each term and merge it into our result
		while(rightCurrent != nullptr)
		{
			Term *product = new Term(leftCurrent->coeff * rightCurrent->coeff,
				leftCurrent->x + rightCurrent->x, leftCurrent->y + rightCurrent->y, nullptr);

			result = add(result, product);
			rightCurrent = rightCurrent->next;
		}
      
		leftCurrent = leftCurrent->next;
	}

	return Polynomial(result);
}

void Polynomial::print() const
{
	if(terms == nullptr)
	{
		cout << "0" << std::endl;
		return;
	}

	cout << terms->coeff << "x^" << terms->x << "y^" << terms->y;

	//format the rest of the terms properly
	Term* current = terms->next;
	while(current != nullptr)
	{
		if(current->coeff < 0)
			cout << " - " << -(current->coeff);

		else
			cout << " + " << current->coeff;
		
		cout << "x^" << current->x << "y^" << current->y;
		current = current->next;
	}

	cout << endl;
}

Term *Polynomial::dx(Term *list)
{
	if(list == nullptr)
		return nullptr;

	// Terms constant in x will vanish
	if(list->x == 0)
	{
		Term *next = list->next;
		delete list;
		return dx(next);
	}

	list->coeff *= list->x;
	--(list->x);

	list->next = dx(list->next);
	return list;
}

Term *Polynomial::dy(Term *list)
{
	if(list == nullptr)
		return nullptr;

	// Terms constant in y will vanish
	if(list->y == 0)
	{
		Term *next = list->next;
		delete list;
		return dy(next);
	}

	list->coeff *= list->y;
	--(list->y);

	list->next = dy(list->next);
	return list;
}

// I know that the if-statements are excessive,
// but believe me, the iterative version is MUCH uglier
Term *Polynomial::add(Term *left, Term* right)
{
	if(left == nullptr && right == nullptr)
		return nullptr;

	if(left == nullptr)
		return new Term(right->coeff, right->x, right->y, add(left, right->next));

	if(right == nullptr)
		return new Term(left->coeff, left->x, left->y, add(left->next, right));

	// if the terms cancel out just move on and don't add it
	if(Compare(left, right) == EQUAL && left->coeff + right->coeff == 0)
		return add(left->next, right->next); 

	if(Compare(left, right) == EQUAL)
		return new Term(left->coeff + right->coeff, left->x, left->y, add(left->next, right->next));

	if(Compare(left, right) == GREATER)
		return new Term(right->coeff, right->x, right->y, add(left, right->next));

	return new Term(left->coeff, left->x, left->y, add(left->next, right));
}

Term *Polynomial::mergeSort(Term *t)
{
	if(t == nullptr || t->next == nullptr)
		return t;

	Term *mid = middle(t);
	Term *left = t;
	Term *right = mid->next;

	// Sever the two lists
	mid->next = nullptr;

	left = mergeSort(left);
	right = mergeSort(right);
	t = merge(left, right);

	return t;
}

Term *Polynomial::merge(Term *left, Term *right)
{
	if(left == nullptr)
		return right;

	if(right == nullptr)
		return left;

	if(Compare(left, right) == 1)
	{
		right->next = merge(left, right->next);
		return right;
	}

	left->next = merge(left->next, right);
	return left;
}

Term *Polynomial::middle(Term *t)
{
	Term *before = t, *after = t->next;

	// The before pointer will go twice as slow
	// as the after pointer, so once after reaches the
	// end, before will be near the middle of the list
	while(after != nullptr)
	{
		after = after->next;

		if(after != nullptr)
		{
			after = after->next;
			before = before->next;
		}
	}

	return before;
}

Term *Polynomial::copyTerms(Term *t)
{
	if(t == nullptr)
		return nullptr;

	return new Term(t->coeff, t->x, t->y, copyTerms(t->next));
}

void Polynomial::deleteTerms(Term *t)
{
	if(t == nullptr)
		return;

	deleteTerms(t->next);
	delete t;
}
