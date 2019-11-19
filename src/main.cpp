/*//////////////////////////////////////////////////////////////////////////
/C++ Data Structure Assignment.
/
/The following C++ program impliments a brick sort using threads. Main 
/for loop contains two Even/Odd loops that declare threads and compare two
/indices and swap.
/
//////////////////////////////////////////////////////////////////////////*/
#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <vector>
using namespace std;

//Function Declarations
void theSwapFunc(int* fileVector,int i);
void resizeFunc(int*& fileVector,int const SIZE);

//Global Dynamic Array.
int const SIZE = 51;
int* fileVector = new int[SIZE];


//MAIN
int main(int argc, char const *argv[])
{
	//Variables
	vector<thread> threadPool; //array of threads, i.e. a thread pool
	int maxNumOfThreads = thread::hardware_concurrency(); //retrieves max number of threads.

	//Input / Increment Variables.
	int x = 0;
	int counter = 0;

	while(cin){
		cin >> x;
		fileVector[counter] = x;
		counter++;
		if(counter >= SIZE){
			resizeFunc(fileVector,SIZE);
		}
	}

	//Verify Max Threads
	//cout << "maxNumOfThreads: " << maxNumOfThreads << endl;

	//Main Loop.
	for (int i = 0; i < counter; i++)
	{
		//Determine  which  phase  you  are in
		if(i % 2 != 0){
			
			///////////////////////	
			//ODD Phase
			///////////////////////----------------------------------------------
			for (int j =1;j <= counter-2;j+=2 )
			{
				//spawn a thread  to  compare  and/or swap  two  adjacent  items
				
				threadPool.push_back(thread(theSwapFunc,fileVector,j) );
				
				//If threads are maxed, join,clear, spawn and continue.
				if (i % maxNumOfThreads == 0){ 	
				  //wait for all the threads to finish
					for (int j = 0; j < threadPool.size(); j++){
				    threadPool[j].join();
				  }
					threadPool.clear(); 				
				}
			}
			//--------------------------------------------------------------------
			for (int j = 0; j < threadPool.size(); j++){
				threadPool[j].join();
			}
			threadPool.clear(); 	
		}
		else{
		
			///////////////////////	
			//EVEN phase
			///////////////////////-----------------------------------------------		
			for (int j = 0; j <= counter-2; j+=2)
			{
				//spawn a thread  to  compare  and/or swap  two  adjacent  items
				
				threadPool.push_back(thread(theSwapFunc,fileVector,j) );

				//If threads are maxed, join,clear, spawn and continue.
				if (i % maxNumOfThreads == 0){ 	
				  //wait for all the threads to finish
					for (int j = 0; j < threadPool.size(); j++){
				    threadPool[j].join();
				  }
				  threadPool.clear(); 
				}
			}
			//--------------------------------------------------------------------
			for (int j = 0; j < threadPool.size(); j++){
				threadPool[j].join();
			}
			threadPool.clear(); 	
		}
	}
	/////////////////////////////
	// Output  the  sorted  array
	/////////////////////////////
	
	for (int i = 0; i < counter; i++)
	{
		cout << fileVector[i] << endl;
	}
	return 0;
}

//FUNCTION IMPLIMENTATIONS
/////////////////////////////////////////////////////////////////////////////////////

//Swap values in indices if one is greater than the other.
void theSwapFunc(int* fileVector , int i){
	
	if(fileVector[i] > fileVector[i+1]){
		int temp = fileVector[i];
	    fileVector[i] = fileVector[i+1];
	    fileVector[i+1] = temp;
  }
}

//Resize global dynamic array if file > 51.
void resizeFunc(int*& fileVector, int size){

	int newSize = size*2;

	//Create new larger array
	int *temp;
	temp = new int[newSize];

	//Deep copy.
	for(int i = 0;i < newSize;i++){						
		temp[i] = fileVector[i];
	}
	if(fileVector != NULL){
		delete [] fileVector;	//dealocate old.
	}

	fileVector = temp;	//fileVector is now larger, and the old values are preserved

	temp = NULL; //For good measure.
}
