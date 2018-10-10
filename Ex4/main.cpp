//Nathan Nichols
//Code for Ex. 4
//Arbitrary code that protects a common resource(myStack) using 3-4 threads

#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <unistd.h>
#include <stack>
#include "lock_guard.h"
 

std::mutex _mu;  // protects function
std::stack<int> myStack; //Stack shared by threads

//function that gets the top value from a stack
void popFromStack(std::string msg)
{

	//Instantiates guardlock and locks mutex
	myGuard::lock_guard<std::mutex> lock(_mu);
    
 	//prints what is on top for each thread
	std::cout << msg << " sees value " << myStack.top() << std::endl;

	//used to amplify the difference between using and not using lock_guard
	usleep(10);

	myStack.pop();
 
    	// _mu is automatically unlocked when lock falls out of scope
    
}
 
int main()
{

	//Push 4 values to stack.
	myStack.push(1);
	myStack.push(2);
	myStack.push(3);
	myStack.push(4);


	std::cout << "in main: " << std::endl;
 
	//start threads
	std::thread t1(popFromStack,std::string("t1"));
	std::thread t2(popFromStack,std::string("t2"));
	std::thread t3(popFromStack,std::string("t3"));

 
	//wait for threads to join back up
	t1.join();
	t2.join();
	t3.join();
 
    std::cout << "all joined" << std::endl;
}


