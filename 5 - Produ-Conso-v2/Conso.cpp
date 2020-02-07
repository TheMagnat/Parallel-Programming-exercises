
#include "Conso.hpp"

#include <iostream>

Conso::Conso(int id, int howManyFruit, Panier* ptrToPanier, std::condition_variable* cv) : id_(id), fruitToEat_(howManyFruit), PanierPtr_(ptrToPanier), isEnd_(false), cv_(cv) {

	theConso_ = std::thread(&Conso::mainLoop, this);

	PanierPtr_->addCons();

}

void Conso::end(){

	isEnd_ = true;
	
}

void Conso::join(){

	theConso_.join();

}

void Conso::mainLoop(){

	while(1){

		if(isEnd_) return;

		//int waitingTime(rand()%2 + 1);
		
		//std::this_thread::sleep_for(std::chrono::milliseconds(3000));

		std::unique_lock<std::mutex> lock(Global::waitMutex_);

		cv_->wait(lock);

		int tookFruit(PanierPtr_->takeFruit());

		if(tookFruit < 0){
			Global::coutMutex_.lock();
			std::cout << "Consomateur " << id_ << " : Il n'y avait rien à manger :(" << std::endl;
			Global::coutMutex_.unlock();
		}
		else{
			--fruitToEat_;
			Global::coutMutex_.lock();
			std::cout << "Consomateur " << id_ << " : J'ai mangé le fruit " << tookFruit << std::endl;
			Global::coutMutex_.unlock();

			if(fruitToEat_ <= 0){

				PanierPtr_->popCons();

				return;

			}

		}

	}

}