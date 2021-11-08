/* 
 * A function object that compares the
 * individual terms of the polynomial
 */

#pragma once

#include "Term.h"

const int LESS = -1;
const int EQUAL = 0;
const int GREATER = 1;

struct Comparator
{
	// The overloaded () operator the compares two terms
	// Returns 1 if left < right, 0 if left = right
	// and -1 if right < left
	int operator()(Term *left, Term *right)
	{
		int value;

		if(left->x == right->x)
		{
			if(left->y == right->y)
				value = EQUAL;
			else
				value = (left->y < right->y) ? GREATER : LESS;
		}

		else
			value = (left->x < right->x) ? GREATER : LESS;

		return value;
	}
};
