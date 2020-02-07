
#include <thread>
#include <iostream>
#include <string>
#include <mutex>


std::mutex monMutex;


void count(int start, int end, std::string const& witchThread){

	std::lock_guard<std::mutex> lock(monMutex);

	std::cout << std::endl;


	for (int i = start; i < end + 1; ++i){
		/* code */
		std::cout << "\t" << witchThread << " : " << i << " ";

	}

	std::cout << std::endl;

}


int main(int argc, char const *argv[]){
	

	count(1, 1000, "Main");


	std::cout << "\n Thread : \n" << std::endl;

	std::thread t1(count, 1, 500, "Thread");

	std::thread t2(count, 500, 1000, "Main");

	t1.join();
	t2.join();

	return 0;
}