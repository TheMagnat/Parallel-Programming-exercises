
#include "Panier.hpp"


#include <thread>
#include <condition_variable>


class Produ{

public:
	Produ(int id, Panier* ptrToPanier, std::condition_variable* cv);

	void end();

	void join();

	void mainLoop();
	
private:

	int id_;

	std::thread theProdu_;

	Panier* PanierPtr_;

	bool isEnd_;

	std::condition_variable* cv_;

};