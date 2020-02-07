
#include "Conso.hpp"

#include <iostream>

Conso::Conso(int id, int howManyFruit, Panier* ptrToPanier) : id_(id), fruitToEat_(howManyFruit), PanierPtr_(ptrToPanier), isEnd_(false) {

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

		int waitingTime(rand()%2 + 1);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime*1000));

		int tookFruit(PanierPtr_->takeFruit());

		if(tookFruit < 0){
			std::cout << "Consomateur " << id_ << " : J'ai dormis " << waitingTime << " secondes, mais il n'y avait rien à manger :(" << std::endl;
		}
		else{
			--fruitToEat_;
			std::cout << "Consomateur " << id_ << " : J'ai dormis " << waitingTime << " secondes, et j'ai mangé le fruit " << tookFruit << std::endl;
			
			if(fruitToEat_ <= 0){

				PanierPtr_->popCons();

				return;

			}

		}

	}

}