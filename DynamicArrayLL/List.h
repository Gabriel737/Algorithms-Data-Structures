/*
 * This is the header file for a linked list
 * class that is implemented using dynamic arrays
 */

#pragma once

// This list can support any primitive data type, to 
// change the type, simply alter the statement below
typedef char ListType;

struct Node
{
	// The item that is stored in this node
	ListType item;
	// An integer >= 0 that contains the index of the next Node
	int next;
};

class List
{
public:
	// The initial size of the list when first constructed
	const static int INITIAL_SIZE = 5;

	// This constant will be used to denote "null" in the list
	const static int LIST_NULL = -1;

	// Creates a new linked list with all free nodes
	List();

	// Initializes a list to the same state as another one
	List(const List &other);

	// Deallocates all the memory used by the list
	~List();

	// Overloaded assignment operator to handle dynamic memory
	const List& operator=(const List &other);

	// Determines whether or not the linked list is empty
	// postcondition: returns true if and only if the list is empty
	// ie. no elements are present, and false otherwise
	bool isEmpty() const;

	// Attempts to insert a character x into the linked list
	// the function will insert x into the begining of the list
	// provided that the list is not already full
	// postcondition: Returns true if the insertion was successful
	// The insertion will always be successful since this 
	// list was implemented with resizeable dynamic arrays
	bool cons(ListType x);

	// Attempts to remove the first character x from the linked list
	// postcondition: Returns true if the item was removed and
	// false if the item was not there to begin with
	bool del(ListType x);

	// An O(n) search to find the character x in the linked list
	// postcondition: Returns true if the item exists in the
	// linked list and false otherwise
	bool search(ListType x) const;

	// postcondition: Returns the value of the first node if it exists
	// and the null character '\0' if the list is currently empty
	ListType getFirst() const;

	// postcondition: returns true if the linked list is full
	// This function will always return false since
	// the list is implemented using dynamic arrays
	bool isFull() const;

	// postcondition: prints onto standard output the 
	// items currently in the linked list
	void print() const;

	// postcondition: The linked list is reversed
	void reverse();

	// This is a debugging function for the linked list class
	// postcondition: prints onto standard output the internal
	// structure of the data type
	void dumpArray() const;

private:
	// This method is to be used by the constructor and assignment operator
	// postcondition: This list is brought into the same state as the other list
	void copyList(const List &other);

	// This method should be called when trying to insert into a full list
	// postcondition: Increases the size of the dynamic array by 2 * size + 1
	void resize();

	// The current size of the array, this will be changed incrementally
	int size;

	// head contains the index of the first item of the list
	// free contains the index of the first free item of the list
	int head, free;
	Node *list;
};
