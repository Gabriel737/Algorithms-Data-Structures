/* 
 * This is the implementation file for the skip list
 * class to gain more insight into the Big-O 
 * complexity of skip list sort
 */

#include "Skiplist.h"
#include <climits>
#include <cmath>

Skiplist::Skiplist()
{
	size = 0;
	// This implementation uses a dumby node
	// for both the top and bottom lists
	bottom = new BottomNode(INT_MIN, nullptr);
	top = new TopNode(INT_MIN, bottom, nullptr);
}

Skiplist::Skiplist(const Skiplist &s)
{
	copyLists(s);
}

Skiplist::~Skiplist()
{
	deleteLists();
}

Skiplist& Skiplist::operator=(const Skiplist &other)
{
	if (&other != this)
	{
		copyLists(other);
	}
	return *this;
}

int Skiplist::insert(int x)
{
	size++;
   // Account for first two pointer assigments
	int traversals = 2;

	TopNode *topCurrent = top;
	while(topCurrent->next != nullptr && topCurrent->next->value <= x)
	{
		topCurrent = topCurrent->next;
		traversals++;
	}
	
	BottomNode *bottomCurrent = topCurrent->down;
	while(bottomCurrent->next != nullptr && bottomCurrent->next->value <= x)
	{
		bottomCurrent = bottomCurrent->next;
		traversals++;
	}

	bottomCurrent->next = new BottomNode(x, bottomCurrent->next);

	if(shouldPromote() && topCurrent->value != x)
	{
		topCurrent->next = new TopNode(x, bottomCurrent->next, topCurrent->next);
		traversals += optimize();
	}
	
	return traversals;
}

int Skiplist::search(int x) const
{
   // Account for first two pointer assigments
	int traversals = 2;
   bool found = false;
   
	TopNode *topCurrent = top;
	while(topCurrent->next != nullptr && topCurrent->next->value <= x)
	{
		topCurrent = topCurrent->next;
		traversals++;
	}

	BottomNode *bottomCurrent = topCurrent->down;
	while(!found && bottomCurrent != nullptr && bottomCurrent->value <= x)
	{
		if(bottomCurrent->value == x)
		{
			// Item found - no action implemented
         found = true;
		}
		bottomCurrent = bottomCurrent->next;
		traversals++;
	}

	return traversals;
}

bool Skiplist::shouldPromote() const
{
	bool promote = false;
   
	for(int i = 1; i * i <= size; i++)
	{
		if(i * i == size)
		{
			promote = true;
		}
	}

	return promote;
}

int Skiplist::optimize()
{
	int rootSize = round(sqrt(size));
	TopNode *topCurrent = top->next;
	BottomNode *bottomCurrent = bottom->next;

   // Account for first two pointer assigments
	int traversals = 2, n = 1;
	while(topCurrent != nullptr && bottomCurrent != nullptr && n < size)
	{
		// Rearrange pointers such that they are evenly
		// spaced, ie. each node has a distance of
		// sqrt(n) from the previous and next node
		if(n % rootSize == 0)
		{
			topCurrent->down = bottomCurrent;
			topCurrent->value = bottomCurrent->value;
			topCurrent = topCurrent->next;
			traversals++;
		}
		bottomCurrent = bottomCurrent->next;
		traversals++;
		n++;
	}

	return traversals;
}

void Skiplist::deleteLists()
{
	while(top != nullptr)
	{
		TopNode *temp = top;
		top = top->next;
		delete temp;
	}

	while(bottom != nullptr)
	{
		BottomNode *temp = bottom;
		bottom = bottom->next;
		delete temp;
	}

	top = nullptr;
	bottom = nullptr;
}

void Skiplist::copyLists(const Skiplist &s)
{
	deleteLists();

   // create the dumby nodes
	this->size = s.size;
	top = new TopNode(s.top->value, s.top->down, s.top->next);
	bottom = new BottomNode(s.bottom->value, s.bottom->next);

   // copy the top list
	TopNode *currentTop = top, *otherTop = s.top->next;
	while(otherTop != nullptr)
	{
		currentTop->next = new TopNode(otherTop->value, otherTop->down, otherTop->next);
		currentTop = currentTop->next;
		otherTop = otherTop->next;
	}

   // copy the bottom list
	BottomNode *currentBottom = bottom, *otherBottom = s.bottom->next;
	while(otherBottom != nullptr)
	{
		currentBottom->next = new BottomNode(otherBottom->value, otherBottom->next);
		currentBottom = currentBottom->next;
		otherBottom = otherBottom->next;
	}
}
