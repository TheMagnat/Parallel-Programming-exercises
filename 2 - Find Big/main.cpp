
#include <thread>
#include <vector>

#include <iostream>


const int nbThread = 9;
const size_t nbNombres = 777;


std::vector<int> monTableau;

std::vector<std::thread> threadTab;

std::vector<int> best;


void findBig(size_t first, size_t end, size_t index){

	int tempoMax(0);

	for (int i = first; i < end; ++i){

		if(tempoMax < monTableau[i]) tempoMax = monTableau[i];

	}

	best[index] = tempoMax;

}



int main(int argc, char const *argv[]){
	
	srand(time(NULL));

	best.resize(nbThread);


	for (int i = 0; i < nbNombres; ++i){
		
		monTableau.emplace_back(rand()%10000);

	}

	float step(monTableau.size()/(float)nbThread);

	for (int i = 0; i < nbThread; ++i){

		threadTab.emplace_back(findBig, int(i * step), int(i * step + step), i);
		//std::cout << "debut : " << int(i*step) << " fin : " << int(i*step + step) << std::endl;

	}



	for (int i = 0; i < nbThread; ++i){

		threadTab[i].join();

	}



	for (int i = 0; i < nbThread; ++i){

		std::cout << best[i] << std::endl;

	}
	

	//std::thread t2(findBig, monTableau.size()/2, monTableau.size(), &b);

	// t1.join();
	// t2.join();

	//std::cout << "Premier : " << a << " Second : " << b << std::endl;

	//a > b ? std::cout << "Le plus grand est " << a << std::endl : std::cout << "Le plus grand est " << b << std::endl; 


	return 0;
}