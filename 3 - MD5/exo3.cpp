
#include <vector>
#include <string>
#include <list>
#include <mutex>
#include <thread>
#include <cmath>


#include "md5.hpp"
#include "Semaphore.hpp"


Semaphore maSemaphore(2);

std::string toFind_;
bool test(std::string const& toTest){

    //std::cout << toTest << std::endl;

    if(toFind_ == md5(toTest)){
        std::cout << "fini : " << toTest << std::endl;
        return true;
    }

    return false;


}


struct noeud{
    
    noeud(int profondeur, std::string const& mot) : profondeur_(profondeur), mot_(mot) {

        //std::cout << "Mot : " << mot_ << std::endl;
        fin = test(mot_);

    }

    bool fin;

    bool threadIn_;

    int profondeur_;
    std::string mot_;
    
    //std::mutex editList_;

    //bool allAdded_;
    std::vector<noeud> possibility_;


};

std::vector<char> allCara_;

//65 - 90, 97 - 122, 48 - 57





size_t allCaraSize_;
void fillAllCara(){

    //a - z
    for (char i(65); i < 91; ++i){
        allCara_.push_back(i);
    }
    //A - Z
    for (char i(97); i < 123; ++i){
        allCara_.push_back(i);
    }
    //0 - 9
    for (char i(48); i < 58; ++i){
        allCara_.push_back(i);
    }

    allCaraSize_ = allCara_.size();

}


bool allEnd_ = false;

std::string motFinal;

bool profondeur_(noeud& noeudActuel){

    size_t noeudActuelSize;
    while((noeudActuelSize = noeudActuel.possibility_.size()) < allCaraSize_){


        noeudActuel.possibility_.emplace_back(noeudActuel.profondeur_+1, noeudActuel.mot_ + allCara_[noeudActuelSize]);
        //std::cout << noeudActuel.possibility_.back().mot_ << std::endl;
        if(noeudActuel.possibility_.back().fin){


            motFinal = noeudActuel.possibility_.back().mot_;
            allEnd_ = true;
            return true;
        
        }


    }

    for (size_t i(0), count(noeudActuel.possibility_.size()); i < count; ++i){

        if(noeudActuel.profondeur_ < 3){

            //if(noeudActuel.possibility_[i].threadIn_ == false){

                //noeudActuel.possibility_[i].threadIn_ = true;
                if(profondeur_(noeudActuel.possibility_[i])){
                    return true;
                }

            //}

        }

    }

    return false;

}

void miniPasse(noeud& noeudActuel){
    profondeur_(noeudActuel);
    maSemaphore.notify();
}


void fillFirst(noeud& depart){

    size_t noeudActuelSize;
    while((noeudActuelSize = depart.possibility_.size()) < allCaraSize_){


        depart.possibility_.emplace_back(depart.profondeur_+1, depart.mot_ + allCara_[noeudActuelSize]);
        if(depart.possibility_.back().fin){


            motFinal = depart.possibility_.back().mot_;
            return;
        
        }


    }

}


void passe(noeud& depart){

    fillFirst(depart);


    for (int i(0); i < allCaraSize_; ++i){

        maSemaphore.wait();

        if(allEnd_) break;

        maSemaphore.add();

        std::thread newThread(miniPasse, std::ref(depart.possibility_[i]));

        newThread.detach();


    }

    //maSemaphore.waitAll();

}

void passe2(noeud& depart, size_t start, size_t end){

    for(size_t i(start); i < end; ++i){

        profondeur_(depart.possibility_[i]);
        if(allEnd_) return;


    }

}


const int prof = 4;
bool boucle(size_t start, size_t end){

    std::string xd;

    for(size_t i(start); i < end; ++i){

        for(size_t j(0); j < allCaraSize_; ++j){

            for(size_t k(0); k < allCaraSize_; ++k){

                for(size_t l(0); l < allCaraSize_; ++l){

                    xd = allCara_[i];
                    xd += allCara_[j];
                    xd += allCara_[k];
                    xd += allCara_[l];

                    if(test(xd)){
                        motFinal = xd;
                        allEnd_ = true;
                        return true;
                    }


                }

            }

        }

    }

    return false;

}



std::vector<std::string> allPossibility;
//size_t pointeur = 0;

std::mutex loltex;

void methodeUltime(size_t shift, std::vector<std::string> possible_){
        
    size_t pointeur(0);

    while(!allEnd_){

        for(size_t i(0); i < allCaraSize_; ++i){

            std::string newPossibility(possible_[pointeur] + allCara_[i]);

            if(test(newPossibility)){

                allEnd_ = true;

                motFinal = newPossibility;

                break;

            }

            possible_.emplace_back(std::move(newPossibility));
        }
        ++pointeur;

    }
}

//1.200

noeud lePapa(0, "");


std::vector<std::thread> allThread;
int main(int argc, char const *argv[]){
    

    //std::cout << "md5 of 'grape': " << md5("grape") << std::endl;
     
    toFind_ = md5("9999");

    //toFind_ = "45950e8a33d57cc2db70cb5f67a62d3a";

     fillAllCara();

     //std::cout << allCara_.size() << std::endl;

     ///METHODE PASSE 1

     //passe(lePapa);

     ///FIN METHODE PASSE 1


     ///Methde PASSE 2
     // fillFirst(lePapa);
     
     // for (size_t i (0); i < 2; ++i){
         
     //     allThread.emplace_back(passe2, std::ref(lePapa), (allCaraSize_/2.0f) * i, (allCaraSize_/2.0f) * (i + 1));


     // }

     // for(size_t i(0); i < allThread.size(); ++i){

     //     allThread[i].join();

     // }
     ///FIN METHODE PASSE 2


     ///Methode Boucle
     // for (size_t i (0); i < 2; ++i){
         
     //     allThread.emplace_back(boucle, (allCaraSize_/2.0f) * i, (allCaraSize_/2.0f) * (i + 1));

     // }

     // for(size_t i(0); i < allThread.size(); ++i){

     //     allThread[i].join();

     // }
     ///Fin methode Boucle

     ///Methode ultime

    const size_t nbThread = 2;
    
    allPossibility.reserve(pow(allCaraSize_, 4));


    std::vector<std::vector<std::string>> possibleMultiple;
    possibleMultiple.resize(nbThread);


    for(size_t nb(0); nb < nbThread; ++nb){
        
        possibleMultiple[nb].reserve(pow(allCaraSize_, 4)/nb);

        for(size_t i((float)nb/(float)nbThread * allCaraSize_), stop((float)(nb+1)/(float)nbThread * allCaraSize_); i < stop; ++i){

             possibleMultiple[nb].emplace_back(1, allCara_[i]);

        }

    }


     allEnd_ = false;
     

     for (size_t i (0); i < nbThread; ++i){
        
        allThread.emplace_back(methodeUltime, i, possibleMultiple[i]);

     }

     for(size_t i(0); i < allThread.size(); ++i){
         allThread[i].join();
     }
     ///Fin Methode Ultime



     if(allEnd_){
         std::cout << "Trouvé : " << motFinal << std::endl;
     }
     else{
         std::cout << "Bug\n";
     }


    return 0;
}

