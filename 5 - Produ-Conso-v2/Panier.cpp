
#include "Panier.hpp"

#include <iostream>

Panier::Panier(size_t maxSize, std::condition_variable* cv) : maxSize_(maxSize), consNb_(0), cvPtr_(cv) {

	for(size_t i = 0; i < maxSize/2; ++i) content_.push_back(1);

}

void Panier::sendSignal(){

	cvPtr_->notify_all();

}

void Panier::addFruit(int value){

	std::lock_guard<std::mutex> lock(contentMutex_);

	if(content_.size() == maxSize_){
		return;
	}
	
	content_.push_back(value);

}

int Panier::takeFruit(){

	std::lock_guard<std::mutex> lock(contentMutex_);

	if(content_.size() == 0){
		return -1;
	}


	int fruit(content_.back());

	content_.pop_back();

	return fruit;

}

void Panier::addCons(){

	++consNb_;

}

void Panier::popCons(){

	--consNb_;

	std::cout << "\nUn consommateur à fini. Nb de consommateur restant : " << consNb_ << std::endl << std::endl;

	if(consNb_ == 0) sendSignal();

}