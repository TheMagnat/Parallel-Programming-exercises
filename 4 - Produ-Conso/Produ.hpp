
#include "Panier.hpp"


#include <thread>
#include <condition_variable>


class Produ{

public:
	Produ(int id, Panier* ptrToPanier);

	void end();

	void join();

	void mainLoop();
	
private:

	int id_;

	std::thread theProdu_;

	Panier* PanierPtr_;

	bool isEnd_;

};