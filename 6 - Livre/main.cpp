#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <vector>

#include <unordered_map>
#include <mutex>

#define NB_THREAD 1

static std::unordered_map<std::string, size_t> dictionary;
static std::ifstream file;
static std::mutex readMutex;
static std::mutex writeMutex;

void threadRead(){

   std::string mot;

   while(file.good()){

      {
         
         std::lock_guard<std::mutex> lock(readMutex);
         file >> mot;
      
      }

      {

         std::lock_guard<std::mutex> lock(writeMutex);
         ++dictionary[mot];

      }


   }


}

int main(){

   file.open("livre.txt", std::ifstream::in);

   auto avant = std::chrono::system_clock::now();

   std::vector<std::thread> allThread;

   allThread.reserve(NB_THREAD);

   for(size_t i (0); i < NB_THREAD; ++i){
      allThread.emplace_back(threadRead);
   }

   for(size_t i (0); i < NB_THREAD; ++i){
      allThread[i].join();
   }
   

   file.close();


   for(auto& hey : dictionary){
      std::cout << "Mot : " << hey.first << " Nb : " << hey.second << std::endl;
   }

   std::cout << std::endl << "Longueur : " << dictionary.size() << std::endl;

   auto apres = std::chrono::system_clock::now();
   auto duree = apres - avant;
   std::cout << "Temps " << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(duree).count() << "ms" << '\n';

   return 0;

}