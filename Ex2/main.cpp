//Nathan Nichols
//Code for Ex. 2
//Arbitrary code that prints values using 2-3 threads

#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include "lock_guard.h"
 

std::mutex _mu;  // protects function

//function that does something cool
void somethingCool(std::string msg)
{

	//Instantiates guardlock and locks mutex
	myGuard::lock_guard<std::mutex> lock(_mu);
    
 
	std::cout << msg << " does something cool" << std::endl;
 
    	// _mu is automatically unlocked when lock falls out of scope
    
}
 
int main()
{
	std::cout << "in main: " << std::endl;
 
	//start threads
	std::thread t1(somethingCool,std::string("t1"));
	std::thread t2(somethingCool,std::string("t2"));
	std::thread t3(somethingCool,std::string("t3"));
 
	//wait for threads to join back up
	t1.join();
	t2.join();
	t3.join();
 
    std::cout << "all joined" << std::endl;
}


