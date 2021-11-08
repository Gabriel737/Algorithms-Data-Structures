/* 
 * This is the driver/tester file the linked list
 * class that is implemented using dynamic arrays
 */

#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main()
{
	List l;
	// string is used in place of char to prevent input issues
	string command, choice;
	cout << "*** Availible Commands ***"<< endl;
	cout << "1.Empty? 2.Cons 3.Delete 4.Find 5.First 6.Full? 7.Print 8.Reverse 9.Dump 0.Exit" << endl << endl;

	do
	{
		cout << "--> ";
		cin >> command;

		switch(command[0])
		{
		case '1':
			cout << "Result: " << l.isEmpty() << endl;
			break;
		case '2':
			cin >> choice;
			cout << "Result: " << l.cons(choice[0]) << ", ";
			l.print();
			break;
		case '3':
			cin >> choice;
			cout << "Result: " << l.del(choice[0]) << ", ";
			l.print();
			break;
		case '4':
			cin >> choice;
			cout << "Result: " << l.search(choice[0]) << endl;
			break;
		case '5':
			cout << "Result: " << l.getFirst() << endl;
			break;
		case '6':
			cout << "Result: " << l.isFull() << endl;
			break;
		case '7': 
			cout << "Result: ";
			l.print();	
			break;
		case '8': 
			cout << "Result: ";
			l.reverse();
			l.print();
			break;
		case '9':
			l.dumpArray();
			break;
		case '0':
			break;
		default:
			cout << "Invalid command - Try again!" << endl;
		}
	} while(command[0] != '0');
   
   cout << "End of program!" << endl;
}
