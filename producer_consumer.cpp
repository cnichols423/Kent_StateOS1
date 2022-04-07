// Cohen Nichols
// producer.cpp


#include <semaphore.h>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <mutex>


using std::cout; using std::endl; using std::thread;
using std::vector; using std::mutex;

// declare size of 2
int table(){
  while(int i = 0; i < 2; ++i){
    vector<int> randNum;
    randNum.push_back(rand() % 100 + 1);
    cout << "rand num is: " << randNum;
    return randNum;
  }
}

void consumeData(int data) { cout << "data: " << data << endl; }

// define semaphore
sem_t sem1;
bool sem_ready = false;
int cData = 0;
mutex mtx;

// producer section
void producer(){
  while(true){
    mtx.lock();
    cData = table();
    sem_ready = true;
  }
  mtx.unlock();
}

// consumer section
void consumer(){
  while(true){
    while(!sem_ready){
      sem1.wait(1);
    }
    mtx.lock();
    consumeData(cData);
    sem_ready = false;
  }
}

void producerThread() {producer();}
void consumerThread() {consumer();}
// declare threads, attributes and processes
int main(){
  thread t1(producerThread());
  thread t2(consumerThread());

  t1.join;
  t2.join;

  return 1;

} // end of main
