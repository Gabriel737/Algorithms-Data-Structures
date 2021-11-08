/* 
 * This is the driver/tester file the skip list
 * class to gain more insight into the Big-O
 * complexity of skip list sort
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Skiplist.h"

using namespace std;

const int MAX_RAND = 10000;
const int NUM_SIZES = 7;
const int NUM_TRIALS = 100;
const int SIZES[] = {10, 50, 100, 500, 1000, 5000, 10000};

int main()
{
	srand(time(NULL));

   cout << "***INSERTIONS***" << endl;
	cout << "N \t\tRandom \t\tAscending \tDescending \tn*sqrt(n)" << endl;
	cout << "=========================================================================" << endl;
   
   for(int i = 0; i < NUM_SIZES; i++)
   {
      int randomTraversals = 0, ascendingTraversals = 0, descendingTraversals = 0;
      
      for(int trial = 0; trial < NUM_TRIALS; trial++)
      {
         Skiplist random, ascending, descending;

         for(int j = 0; j < SIZES[i]; j++)
         {
            randomTraversals += random.insert(rand() % MAX_RAND);
            ascendingTraversals += ascending.insert(j);
            descendingTraversals += descending.insert(SIZES[i] - j);
         }
      }
      
      cout << SIZES[i] << "\t\t" << randomTraversals / NUM_TRIALS << "\t\t" << ascendingTraversals / NUM_TRIALS << "\t\t" 
         << descendingTraversals / NUM_TRIALS << "\t\t" << static_cast<int>(SIZES[i] * sqrt(SIZES[i])) << endl << endl;
   }
   
   cout << endl << "***SEARCHES***" << endl;
	cout << "N \t\tRandom \t\t n*sqrt(n)" << endl;
	cout << "=========================================================================" << endl;
   
   for(int i = 0; i < NUM_SIZES; i++)
   {
      int traversals = 0;
      Skiplist random;
      
      for(int n = 0; n < i; n++)
      {
         random.insert(rand() % MAX_RAND);
      }
      
      for(int trial = 0; trial < NUM_TRIALS; trial++)
      {
         for(int j = 0; j < SIZES[i]; j++)
         {
            traversals += random.search(rand() % MAX_RAND);
         }
      }
      
      cout << SIZES[i] << "\t\t" << traversals / NUM_TRIALS << "\t\t" << static_cast<int>(SIZES[i] * sqrt(SIZES[i])) << endl << endl;
   }

	return 0;
}
