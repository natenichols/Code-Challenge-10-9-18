#include<thread>
#include<iostream>
#include<mutex>
#include<condition_variable>
#include<string>
#include<unistd.h>


std::mutex _mu;
std::condition_variable _cond;
bool ready = false;
bool waiting = false;


void doWork(std::string msg)
{

	
	std::unique_lock<std::mutex> lock(_mu);

	//Threads block on condition_signal(2)
	_cond.wait(lock, []{return ready;});


	std::cout << msg << ": signaled, doing work" << std::endl;

	//work

	std::cout << msg << ": work is done, signaling next" << std::endl;
	
	
	//notify the next thread
	_cond.notify_one();

	
	
}
void loopWork(std::string msg)
{
	std::unique_lock<std::mutex> lock(_mu);
	
	//Will block on the condition variable in loop
	std::cout << msg << ": has started, is waiting" << std::endl;
	
	lock.unlock();

	while(true){
		//Implemented to let each thead reach the condition variable before it is notified again
		usleep(500);
		doWork(msg);
	}
}
int main()
{
	
	std::cout << "main: initiates threads" << std::endl;

	
	//Start all threads (1) (usleep makes sure each string has time to get to the condition variable)
	std::thread thread1(loopWork, std::string("Thread 1"));
	usleep(1);
	std::thread thread2(loopWork, std::string("Thread 2"));
	usleep(1);
	std::thread thread3(loopWork, std::string("Thread 3"));
	usleep(1);
	
	
	{
		std::unique_lock<std::mutex> lock(_mu);
		ready = true;
		std::cout << "main: signaling thread 1" << std::endl; 
	}

	//main signals waiting thread
	_cond.notify_one();

	thread1.join();
	thread2.join();
	thread3.join();
}
