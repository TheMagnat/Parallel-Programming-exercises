#pragma once

#include "Global.hpp"

#include <condition_variable>

#include <vector>
#include <mutex>

class Panier{

public:
	Panier(size_t maxSize, std::condition_variable* cv);

	void sendSignal();

	void addFruit(int value);

	int takeFruit();

	void addCons();
	void popCons();

private:

	size_t maxSize_;

	int consNb_;

	std::vector<int> content_;

	std::mutex contentMutex_;

	std::condition_variable* cvPtr_;

};