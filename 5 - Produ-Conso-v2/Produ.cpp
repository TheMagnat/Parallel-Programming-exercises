
#include "Produ.hpp"

#include <iostream>

Produ::Produ(int id, Panier* ptrToPanier, std::condition_variable* cv) : id_(id), PanierPtr_(ptrToPanier), isEnd_(false), cv_(cv) {

	theProdu_ = std::thread(&Produ::mainLoop, this);	

}

void Produ::end(){

	isEnd_ = true;

}

void Produ::join(){

	theProdu_.join();

}

void Produ::mainLoop(){

	while(1){

		if(isEnd_) return;

		int waitingTime(rand()%2 + 1);
		
		std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime*1000));

		//std::unique_lock<std::mutex> lock(Global::waitMutex_);

		PanierPtr_->addFruit(1);

		cv_->notify_one();

		Global::coutMutex_.lock();
		std::cout << "Producteur " << id_ << " : J'ai dormis " << waitingTime/2.0 << " secondes, et j'ai posé un fruit\n";
		Global::coutMutex_.unlock();
	}

}