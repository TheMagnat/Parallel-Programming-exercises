
#include "Global.hpp"

#include "Panier.hpp"

#include <thread>
#include <condition_variable>

class Conso{

public:
	Conso(int id, int howManyFruit, Panier* ptrToPanier, std::condition_variable* cv);

	void end();

	void join();

	void mainLoop();
	
private:

	int id_;

	int fruitToEat_;

	std::thread theConso_;

	Panier* PanierPtr_;

	bool isEnd_;

	std::condition_variable* cv_;
	
};