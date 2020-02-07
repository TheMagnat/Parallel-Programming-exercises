#include <mutex>
#include <condition_variable>
#include <iostream>

class Semaphore {
public:
    Semaphore (int count_ = 0)
        : count(count_), maxCount(count_) {}

    inline void notify()
    {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);

        while(count == 0){
            cv.wait(lock);
        }
    }

    inline void add()
    {
        --count;
    }

    inline void waitAll()
    {
        std::unique_lock<std::mutex> lock(mtx);

        while(count < maxCount){
            cv.wait(lock);
        }
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

    int maxCount;
};