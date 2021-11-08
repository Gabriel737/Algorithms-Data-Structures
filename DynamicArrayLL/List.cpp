/* 
 * This is the implemenation file for a linked list
 * class that is implemented using dynamic arrays
 */

#include "List.h"
#include <iostream>

List::List()
{
	size = INITIAL_SIZE;
	list = new Node[size];
	head = LIST_NULL;
	free = 0;
	// null each item and build the free linked list
	for(int i = 0; i < size - 1; i++)
	{
		list[i].next = i + 1;
	}
	list[size - 1].next = -1;
}

List::List(const List &other)
{
	copyList(other);
}

List::~List()
{
	delete [] list;
}

const List& List::operator=(const List &other)
{
	if(&other != this)
	{
		copyList(other);
	}

	return *this;
}

bool List::isEmpty() const
{
	return (head == LIST_NULL);
}

bool List::cons(ListType x)
{
	if(free == LIST_NULL)
	{
		resize();
	}

	int insertionIndex = free;
	free = list[free].next;
	list[insertionIndex].item = x;
	list[insertionIndex].next = head;
	head = insertionIndex;

	return true;
}

bool List::del(ListType x)
{
	if(isEmpty())
	{
		return false;
	}

	// if item is the head of list then remove it and move the head forward
	if(list[head].item == x)
	{
		int freeIndex = free;
		free = head;
		head = list[free].next;
		list[free].next = freeIndex;
		
		return true;
	}
	
	for(int current = head; list[current].next != LIST_NULL; current = list[current].next)
	{
		if(list[list[current].next].item == x)
		{
			int freeIndex = free;
			free = list[current].next;
			list[current].next = list[list[current].next].next;
			list[free].next = freeIndex;

			return true;
		}
	}
	
	return false;
}

bool List::search(ListType x) const
{
	for(int current = head; current != LIST_NULL; current = list[current].next)
	{
		if(list[current].item == x)
		{
			return true;
		}
	}

	return false;
}

ListType List::getFirst() const 
{
	if(isEmpty())
	{
		return '\0';
	}

	return list[head].item;
}

bool List::isFull() const
{
	return false;
}

void List::print() const
{
	std::cout << "List = [ ";

	for(int current = head; current != LIST_NULL; current = list[current].next)
	{
		std::cout << list[current].item << " ";
	}

	std::cout << "]" << std::endl;
}

void List::reverse()
{
	// This algorithm was given to us in class
	if(isEmpty() || list[head].next == LIST_NULL)
	{
		return;
	}

	int after, current = list[head].next;
	list[head].next = LIST_NULL;

	while(current != LIST_NULL)
	{
		after = list[current].next;
		list[current].next = head;
		head = current;
		current = after;
	}
}

void List::dumpArray() const
{
	std::cout << "Result: head = " << head << ", free = " << free << std::endl;
	std::cout << "index \t" << "value \t" << "next \t" << std::endl;

	for(int i = 0; i <size; i++)
	{
		std::cout << i << "\t" << list[i].item << "\t" << list[i].next << "\t" << std::endl;
	}
}

void List::copyList(const List &other)
{
	delete [] list;
	size = other.size;
	head = other.head;
	free = other.free;
	list = new Node[size];

	for(int i = 0; i < size; i++)
	{
		list[i] = other.list[i];
	}
}

void List::resize()
{
	int newSize = 2 * size + 1;
	Node *newList = new Node[newSize];

	for(int i = 0; i < size; i++)
	{
		newList[i] = list[i];
	}

	for(int i = size; i < newSize - 1; i++)
	{
		newList[i].next = i + 1;
	}
	//properly terminate the end of the list
	newList[newSize - 1].next = LIST_NULL;

	delete [] list;
	free = size;
	size = newSize;
	list = newList;
}
