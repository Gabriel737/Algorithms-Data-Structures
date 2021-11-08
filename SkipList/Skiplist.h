/* 
 * This is the header file for the skip list
 * class to gain more insight into the Big-O 
 * complexity of skip list sort
 */

#pragma once

#include <iostream>
#include <cmath>

struct BottomNode 
{
	BottomNode(int v, BottomNode *n)
	{
		value = v;
		next = n;
	}
	int value;
	BottomNode *next;
};

struct TopNode
{
	TopNode(int v, BottomNode *d, TopNode *n)
	{
		value = v;
		down = d;
		next = n;
	}
	int value;
	TopNode *next;
	BottomNode *down;
};

class Skiplist
{
public:
	// Initializes a new skip list with no elements
	Skiplist();

	// Initalizes a new skip list and performs a deep copy on s
	Skiplist(const Skiplist &s);

	// Deletes the skip list and deallocates the memory
	~Skiplist();

	// Overloaded assignment operator to handle dynamic memory
	Skiplist& operator=(const Skiplist &other);
	
	// Inserts the item x into the skip list so that
	// it remains sorted in ascending order.
	// postcondition: returns the number of traversals
	// made to insert the item x into the skip list.
	// Note: This function is of order O(sqrt(n))
	int insert(int x);
	
	// Searches for an item x in the skip list 
	// postcondition: returns the number of traversals
	// made to search for the item x in the skip list
	// Note: This function is of order O(sqrt(n))
	int search(int  x) const;

private:
	// A helper function that returns true if the node should
	// be placed into the top linked list based on whether 
	// or not the n-th node is a perfect square; this 
	// method maintains sqrt(n) - 1 > topSize > sqrt(n) + 1
	// at all times
	bool shouldPromote() const;

	// A helper function to rearrange the pointers of the
	// top list so that a distance of sqrt(n) plus or minus
	// one is maintained at all times for efficient traversals
	// postcondition: returns the number of traversals made
	// Note: This function is of order O(n)
	int optimize();

	// A helper function that deallocates all the 
	// memory taken by the two linked lists
	// postcondition: all current elements are lost 
	void deleteLists();

	// A helper function that performs a deep copy
	// on both the upper and lower lists of s
	// postcondition: all current elements are lost
	void copyLists(const Skiplist &s);

	// The current number of elements in the list
	int size;
	// A pointer to the first top element
	TopNode *top;
	// A pointer to the first bottom element
	BottomNode *bottom;
};

