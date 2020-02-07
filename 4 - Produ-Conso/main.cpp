
#include <condition_variable>
#include <mutex>
#include <iostream>

#include "Panier.hpp"
#include "Produ.hpp"
#include "Conso.hpp"




int main(int argc, char const *argv[]){
	
	srand(time(NULL));

	std::condition_variable cv;
	std::mutex m;

	Panier monPanier(10, &cv);

	Produ monProdu(1, &monPanier);
	//Conso monConso(1, 5, &monPanier);

	std::vector<Conso> allConso;
	allConso.reserve(4);

	allConso.emplace_back(1, 5, &monPanier);
	allConso.emplace_back(2, 5, &monPanier);
	allConso.emplace_back(3, 5, &monPanier);
	allConso.emplace_back(4, 5, &monPanier);

	
	{
		std::unique_lock<std::mutex> lock(m);
		cv.wait(lock);

	}

	monProdu.end();

	for(size_t i(0); i < allConso.size(); ++i){
		
		allConso[i].end();
	
	}

	monProdu.join();

	for(size_t i(0); i < allConso.size(); ++i){
		
		allConso[i].join();
	
	}

	std::cout << "Fini \n";


	return 0;
}