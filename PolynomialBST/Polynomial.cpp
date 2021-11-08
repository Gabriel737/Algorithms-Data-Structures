/* 
 * The implementation file for the polynomial  
 * class that is implemented using a modified BST
 * in descending order, i.e. left > parent > right
 */

#include "Polynomial.h"

Polynomial::Polynomial()
{
	root = nullptr;
}

Polynomial::Polynomial(const Polynomial &p)
{
   root = deep_copy(p.root);
}

Polynomial::~Polynomial()
{
   delete_all(root);
   root = nullptr;
}

Polynomial &Polynomial::operator=(const Polynomial &other)
{
   if(&other != this)
   {
      delete_all(root);
      root = deep_copy(other.root);
   }
   return *this;
}

void Polynomial::insert(int coeff, int degree)
{
   if(coeff == 0)
      return;
	else if(coefficient_at(degree) + coeff == 0)
		remove(degree);
	else
		root = insert_term(root, coeff, degree);
}

// This code was taken as-is from page 246 of Drozek
// Modified slightly by me as to replace the NULL's and 0's
// with the C++ 11 nullptr and to clean it up a little bit
void Polynomial::remove(int degree)
{
   Term *node = root, *prev = nullptr;
   while(node != nullptr)
   {
      if(node->x == degree)
         break;
      prev = node;
      if(node->x < degree)
         node = node->left;
      else
         node = node->right;
   }
   
   if(node != nullptr && node->x == degree)
   {
      if(node == root)
         delete_by_merging(root);
      else if(prev->left == node)
         delete_by_merging(prev->left);
      else 
         delete_by_merging(prev->right);
   }
}

bool Polynomial::is_zero() const
{
	return (root == nullptr);
}

int Polynomial::evaluate(int x) const
{
	return evaluate_term(root, x);
}

int Polynomial::coefficient_at(int degree) const
{
	Term *current = root;
	while(current != nullptr)
	{
		if(current->x == degree)
			return current->coeff;
		else if(current->x < degree)
			current = current->left;
		else
			current = current->right;
	}
	return 0;
}

// Note: this implementation is ideal when the left
// and right operands are both balanced trees
// operator+ runs in O(min(x*logy, y*logx)) time but
// produces extremely deformed BST's in the "sparse" case
// A potential improvement is to "rebalance" the tree 
// at the end of the call, but we haven't learned that yet
const Polynomial operator+(const Polynomial &left, const Polynomial &right)
{
   // make sure that the left is the bigger polynomial
   if(left.degree() < right.degree())
      return operator+(right, left);
   // make a deep copy of the bigger polynomial
   Polynomial sum(left);
   // insert all the terms of the smaller polynomial into our sum
   for(int d = 0; d <= right.degree(); d++)
      sum.insert(right.coefficient_at(d), d);
   return sum;
}

std::ostream &write_term(std::ostream &out, Term *node)
{
   if(node == nullptr)
      return out;
   // inorder BST traversal 
   write_term(out, node->left);
   if(node->coeff >= 0)
      out << "+" << node->coeff << "x^" << node->x << " ";
   else
      out << "-" << -(node->coeff) << "x^" << node->x << " ";
   write_term(out, node->right);
   return out;
}

std::ostream &operator<<(std::ostream &out, const Polynomial &p)
{
   return write_term(out, p.root);
}

int Polynomial::degree() const
{
	if(root == nullptr)
      return 0;
	Term *current = root;
   while(current->left != nullptr)
      current = current->left;
	return current->x;
}

std::istream &operator>>(std::istream &in, Polynomial &p)
{
   int coefficient, x, n;
   in >> n;
   for(int i = 0; i < n; i++)
   {
      in >> coefficient >> x;
      p.insert(coefficient, x);
   }
   
   return in;
}

void Polynomial::differentiate_x()
{
	root = dx(root);
}

Term *Polynomial::insert_term(Term *node, int coeff, int degree)
{
   if(coeff == 0)
      return node;
	if(node == nullptr)
		node = new Term{coeff, degree, nullptr, nullptr};
	else if(node->x == degree)
		node->coeff += coeff;
	else if(node->x < degree)
		node->left = insert_term(node->left, coeff, degree);
	else // node->x > degree
      node->right = insert_term(node->right, coeff, degree);
	return node;
}

// This code was taken as-is from page 245 of Drozek
// Modified slightly by me as to replace the NULL's and 0's
// with the C++ 11 nullptr and to clean it up a little bit
void Polynomial::delete_by_merging(Term *&node)
{
   if (node == nullptr) 
      return;
   Term *tmp = node;
   if (node->right == nullptr)
      node = node->left;
   else if (node->left == nullptr)
      node = node->right;
   else 
   { 
      tmp = node->left;
      while (tmp->right != nullptr)
         tmp = tmp->right;
      tmp->right = node->right;
      tmp = node;
      node = node->left;
   }
   delete tmp;
}

int Polynomial::evaluate_term(Term *node, int x) const
{
	if(node == nullptr)
		return 0;
   // preorder BST traversal
	return node->coeff * pow(x, node->x)  
		+ evaluate_term(node->left, x) + evaluate_term(node->right, x);
}

Term *Polynomial::dx(Term *node)
{
	if(node == nullptr || node->x == 0)
		return nullptr;
	return new Term{node->coeff * node->x, node->x - 1, dx(node->left), dx(node->right)};
}

Term *Polynomial::deep_copy(Term *node)
{
   if(node == nullptr)
      return nullptr;
   return new Term{node->coeff, node->x, deep_copy(node->left), deep_copy(node->right)};
}

void Polynomial::delete_all(Term *node)
{
   if(node == nullptr)
      return;
   delete_all(node->left);
   delete_all(node->right);
   delete node;
}

